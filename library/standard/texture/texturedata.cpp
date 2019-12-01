#include "texturedata.h"
#include "application.h"
#include <iostream>
#include <QOpenGLContext>
#include <QOpenGLFunctions>


TextureData::TextureData(BaseOperator* parent_op, const char * name, bool has_fbo_)
    : BaseDataType(parent_op, name, Type), has_fbo(has_fbo_)
{
    initializeOpenGLFunctions();
}


TextureData::~TextureData()
{
    Q_ASSERT(!currently_allocated);
}


void TextureData::parameter_changed(BaseParameterOld*)
{
    needs_reallocation = true;
}


void TextureData::acquire_resources()
{
    glGenTextures(1, &texture_handle);
    currently_allocated = true;
    reallocate();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (has_fbo)
    {
        glGenFramebuffers(1, &fbo_handle);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_handle, 0);
    }
}


void TextureData::release_resources()
{
    if (has_fbo)
    {
        glDeleteFramebuffers(1, &fbo_handle);
    }
    glDeleteTextures(1, &texture_handle);

    currently_allocated = false;
}


void TextureData::upload_data(PixelNumChannelsEnum num_channels, PixelDataFormatEnum format, const void * pixel_data)
{
    Q_ASSERT(!has_fbo);

    static constexpr std::array channel_types{ GL_RED, GL_RG, GL_RGB, GL_RGBA };
    static constexpr std::array format_types{ 0, 0, GL_UNSIGNED_BYTE, GL_BYTE,
                                              0, 0, GL_UNSIGNED_SHORT, GL_SHORT,
                                              GL_UNSIGNED_INT, GL_INT, 0, GL_FLOAT };

    auto channel_type = channel_types[static_cast<int>(num_channels)];
    auto format_type = format_types[static_cast<int>(format)];

    //Q_ASSERT(channel_type == GL_RED);
    //Q_ASSERT(format_type == GL_UNSIGNED_SHORT);

    if (format_type != 0)
    {
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, resolution.x(), resolution.y(), channel_type, format_type, pixel_data);
    }
}


void TextureData::bind_as_framebuffer()
{
    Q_ASSERT(has_fbo);
    if (currently_allocated)
    {
        if (needs_reallocation)
        {
            reallocate();
            needs_reallocation = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
        glViewport(0, 0, resolution.x(), resolution.y());
    }
}


void TextureData::bind_as_texture(int texture_index) const
{
    auto this2 = const_cast<TextureData*>(this);
    if (currently_allocated)
    {
        this2->glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + texture_index));
        this2->glBindTexture(GL_TEXTURE_2D, texture_handle);
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


void TextureData::set_resolution(int x, int y)
{
    resolution.set(x, y);
}


void TextureData::set_num_channels(PixelNumChannelsEnum num)
{
    pixel_channels.set(static_cast<int>(num));
}


void TextureData::set_format(PixelDataFormatEnum format)
{
    pixel_format.set(static_cast<int>(format));
}


int TextureData::get_resolution_x() const
{
    return resolution.x();
}


int TextureData::get_resolution_y() const
{
    return resolution.y();
}


PixelNumChannelsEnum TextureData::get_num_channels() const
{
    return static_cast<PixelNumChannelsEnum>(pixel_channels.get_index());
}


PixelDataFormatEnum TextureData::get_format() const
{
    return static_cast<PixelDataFormatEnum>(pixel_format.get_index());
}


void TextureData::reallocate()
{
    if (currently_allocated)
    {
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, gl_format_for(pixel_format, pixel_channels), resolution.x(), resolution.y(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }
}


GLenum TextureData::gl_format_for(const EnumPar& format, const EnumPar& num_channels)
{
    switch (format.get_index())
    {
    case 0:
        switch (num_channels.get_index()) // 8 Bit Unsigned Norm
        {
        case 0:
            return GL_R8; // 1 Channel
        case 1:
            return GL_RG8; // 2 Channels
        case 2:
            return GL_RGB8; // 3 Channels
        case 3:
            return GL_RGBA8; // 4 Channels
        }
    case 1:
        switch (num_channels.get_index()) // 8 Bit Signed Norm
        {
        case 0:
            return GL_R8_SNORM; // 1 Channel
        case 1:
            return GL_RG8_SNORM; // 2 Channels
        case 2:
            return GL_RGB8_SNORM; // 3 Channels
        case 3:
            return GL_RGBA8_SNORM; // 4 Channels
        }
    case 2:
        switch (num_channels.get_index()) // 8 Bit Unsigned Int
        {
        case 0:
            return GL_R8UI; // 1 Channel
        case 1:
            return GL_RG8UI; // 2 Channels
        case 2:
            return GL_RGB8UI; // 3 Channels
        case 3:
            return GL_RGBA8UI; // 4 Channels
        }
    case 3:
        switch (num_channels.get_index()) // 8 Bit Signed Int
        {
        case 0:
            return GL_R8I; // 1 Channel
        case 1:
            return GL_RG8I; // 2 Channels
        case 2:
            return GL_RGB8I; // 3 Channels
        case 3:
            return GL_RGBA8I; // 4 Channels
        }
    case 4:
        switch (num_channels.get_index()) // 16 Bit Unsigned Norm
        {
        case 0:
            return GL_R16; // 1 Channel
        case 1:
            return GL_RG16; // 2 Channels
        case 2:
            return GL_RGB16; // 3 Channels
        case 3:
            return GL_RGBA16; // 4 Channels
        }
    case 5:
        switch (num_channels.get_index()) // 16 Bit Signed Norm
        {
        case 0:
            return GL_R16_SNORM; // 1 Channel
        case 1:
            return GL_RG16_SNORM; // 2 Channels
        case 2:
            return GL_RGB16_SNORM; // 3 Channels
        case 3:
            return GL_RGBA16_SNORM; // 4 Channels
        }
    case 6:
        switch (num_channels.get_index()) // 16 Bit Unsigned Int
        {
        case 0:
            return GL_R16UI; // 1 Channel
        case 1:
            return GL_RG16UI; // 2 Channels
        case 2:
            return GL_RGB16UI; // 3 Channels
        case 3:
            return GL_RGBA16UI; // 4 Channels
        }
    case 7:
        switch (num_channels.get_index()) // 16 Bit Signed Int
        {
        case 0:
            return GL_R16I; // 1 Channel
        case 1:
            return GL_RG16I; // 2 Channels
        case 2:
            return GL_RGB16I; // 3 Channels
        case 3:
            return GL_RGBA16I; // 4 Channels
        }
    case 8:
        switch (num_channels.get_index()) // 32 Bit Unsigned Int
        {
        case 0:
            return GL_R32UI; // 1 Channel
        case 1:
            return GL_RG32UI; // 2 Channels
        case 2:
            return GL_RGB32UI; // 3 Channels
        case 3:
            return GL_RGBA32UI; // 4 Channels
        }
    case 9:
        switch (num_channels.get_index()) // 32 Bit Signed Int
        {
        case 0:
            return GL_R32I; // 1 Channel
        case 1:
            return GL_RG32I; // 2 Channels
        case 2:
            return GL_RGB32I; // 3 Channels
        case 3:
            return GL_RGBA32I; // 4 Channels
        }
    case 10:
        switch (num_channels.get_index()) // 16 Bit Float
        {
        case 0:
            return GL_R16F ; // 1 Channel
        case 1:
            return GL_RG16F; // 2 Channels
        case 2:
            return GL_RGB16F; // 3 Channels
        case 3:
            return GL_RGBA16F; // 4 Channels
        }
    case 11:
        switch (num_channels.get_index()) // 32 Bit Float
        {
        case 0:
            return GL_R32F; // 1 Channel
        case 1:
            return GL_RG32F; // 2 Channels
        case 2:
            return GL_RGB32F; // 3 Channels
        case 3:
            return GL_RGBA32F; // 4 Channels
        }
    }
    return GL_RGBA8; // In case something went wrong return common type.
}
