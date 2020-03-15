#include "texturedata.h"
#include "app.h"
#include <iostream>
#include <QOpenGLContext>
#include <QOpenGLFunctions>


const std::vector<QString> TextureData::pixelFormatStrings
{
    QStringLiteral("8 Bit"),
    QStringLiteral("8 Bit (Signed)"),
    QStringLiteral("16 Bit"),
    QStringLiteral("16 Bit (Signed)"),
    QStringLiteral("16 Bit (Float)"),
    QStringLiteral("32 Bit (Float)")
};

const std::vector<QString> TextureData::numChannelsStrings
{
    QStringLiteral("1 Channel"),
    QStringLiteral("2 Channels"),
    QStringLiteral("3 Channels"),
    QStringLiteral("4 Channels")
};



TextureData::TextureData(BaseOperator* parent, const QString& name, bool createFbo)
    : BaseDataType(parent, name, description),
      m_hasFbo(createFbo)
{
    initializeOpenGLFunctions();
}


TextureData::~TextureData()
{
    if (m_isAllocated)
    {
        releaseResources();
    }
}


void TextureData::parameterChangeEvent(const BaseParameter*)
{
    m_needsReallocation = true;
}


void TextureData::acquireResources()
{
    glGenTextures(1, &m_textureHandle);
    m_isAllocated = true;
    reallocate();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (m_hasFbo)
    {
        glGenFramebuffers(1, &m_fboHandle);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fboHandle);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureHandle, 0);
    }
}


void TextureData::releaseResources()
{
    if (m_hasFbo)
    {
        glDeleteFramebuffers(1, &m_fboHandle);
    }
    glDeleteTextures(1, &m_textureHandle);

    m_isAllocated = false;
}


void TextureData::uploadPixels(NumChannels numChannels, PixelFormat format, const void * pixel_data)
{
    Q_ASSERT(!m_hasFbo);

    static constexpr std::array channel_types{ GL_RED, GL_RG, GL_RGB, GL_RGBA };
    static constexpr std::array format_types{ GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, 0, GL_FLOAT };

    auto channelType = channel_types[numChannels];
    auto formatType = format_types[format];

    if (formatType != 0)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureHandle);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_resolution.x(), m_resolution.y(), channelType, formatType, pixel_data);
    }
}


void TextureData::bindFramebuffer()
{
    Q_ASSERT(m_hasFbo);
    if (m_isAllocated)
    {
        if (m_needsReallocation)
        {
            reallocate();
            m_needsReallocation = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, m_fboHandle);
        glViewport(0, 0, m_resolution.x(), m_resolution.y());
    }
}


void TextureData::bindTexture(int texture_index) const
{
    auto this2 = const_cast<TextureData*>(this);
    if (m_isAllocated)
    {
        this2->glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + texture_index));
        this2->glBindTexture(GL_TEXTURE_2D, m_textureHandle);
    }
}


void TextureData::bind_empty_texture(int texture_index)
{
    static bool first_time = true;
    static std::array<unsigned char, 4> fill { 0, 0, 0, 1 };
    static GLuint static_texture_handle = 0;

    auto f = QOpenGLContext::currentContext()->functions();
    f->glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + texture_index));

    if (first_time)
    {
        f->glGenTextures(1, &static_texture_handle);
        f->glBindTexture(GL_TEXTURE_2D, static_texture_handle);
        f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0,  GL_RGBA, GL_UNSIGNED_BYTE, fill.data());
        first_time = false;
    }
    else
    {
        f->glBindTexture(GL_TEXTURE_2D, static_texture_handle);
    }
}


void TextureData::setResolution(int x, int y)
{
    m_resolution.set(x, y);
}


void TextureData::setNumChannels(NumChannels num)
{
    m_numChannels.set(static_cast<int>(num));
}


void TextureData::setPixelFormat(PixelFormat format)
{
    m_pixelFormat.set(static_cast<int>(format));
}


int TextureData::getWidth() const
{
    return m_resolution.x();
}


int TextureData::getHeight() const
{
    return m_resolution.y();
}


TextureData::NumChannels TextureData::getNumChannels() const
{
    return static_cast<NumChannels>(m_numChannels.getIndex());
}


TextureData::PixelFormat TextureData::getPixelFormat() const
{
    return static_cast<PixelFormat>(m_pixelFormat.getIndex());
}


void TextureData::reallocate()
{
    if (m_isAllocated)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, openGLPixelFormat(), m_resolution.x(), m_resolution.y(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }
}


GLenum TextureData::openGLPixelFormat() const
{
    switch (m_pixelFormat.getIndex())
    {
        case Normalized8Bit:
            switch (m_numChannels.getIndex())
            {
                case OneChannel:    return GL_R8;
                case TwoChannels:   return GL_RG8;
                case ThreeChannels: return GL_RGB8;
                case FourChannels:  return GL_RGBA8;
            }

        case Normalized8BitSigned:
            switch (m_numChannels.getIndex())
            {
                case OneChannel:    return GL_R8_SNORM;
                case TwoChannels:   return GL_RG8_SNORM;
                case ThreeChannels: return GL_RGB8_SNORM;
                case FourChannels:  return GL_RGBA8_SNORM;
            }

        case Normalized16Bit:
            switch (m_numChannels.getIndex())
            {
                case OneChannel:    return GL_R16;
                case TwoChannels:   return GL_RG16;
                case ThreeChannels: return GL_RGB16;
                case FourChannels:  return GL_RGBA16;
            }

        case Normalized16BitSigned:
            switch (m_numChannels.getIndex())
            {
                case OneChannel:    return GL_R16_SNORM;
                case TwoChannels:   return GL_RG16_SNORM;
                case ThreeChannels: return GL_RGB16_SNORM;
                case FourChannels:  return GL_RGBA16_SNORM;
            }

        case Float16Bit:
            switch (m_numChannels.getIndex())
            {
                case OneChannel:    return GL_R16F;
                case TwoChannels:   return GL_RG16F;
                case ThreeChannels: return GL_RGB16F;
                case FourChannels:  return GL_RGBA16F;
            }

        case Float32Bit:
            switch (m_numChannels.getIndex())
            {
                case OneChannel:    return GL_R32F;
                case TwoChannels:   return GL_RG32F;
                case ThreeChannels: return GL_RGB32F;
                case FourChannels:  return GL_RGBA32F;
            }
    }
    return GL_RGBA8; // Default
}
