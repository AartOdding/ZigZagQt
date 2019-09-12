#include "texturedata.h"
#include "application.h"
#include <iostream>


TextureData::TextureData(BaseOperator* parent_operator, const char * name)
    : BaseDataType(parent_operator, Type, name)
{
    initializeOpenGLFunctions();

    resolution.set_minimal_updates(true);

    //connect(&resolution_y, &IntPar::value_changed, this, &TextureData::reallocate_texture);
}


TextureData::~TextureData()
{
    Q_ASSERT(!currently_allocated);
}


void TextureData::acquire_resources()
{
    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, resolution.x(), resolution.y(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenFramebuffers(1, &fbo_handle);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_handle, 0);

    currently_allocated = true;
}


void TextureData::release_resources()
{
    glDeleteFramebuffers(1, &fbo_handle);
    glDeleteTextures(1, &texture_handle);

    currently_allocated = false;
}


void TextureData::bind_as_framebuffer()
{
    if (currently_allocated)
    {
        if (parameters_changed())
        {
            reallocate();
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


void TextureData::reallocate()
{
    std::cout << "realloc texture\n";
    if (currently_allocated)
    {
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, gl_format_for(pixel_format, pixel_channels), resolution.x(), resolution.y(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }
}



GLenum TextureData::gl_format_for(const EnumPar& format, const EnumPar& num_channels)
{
    switch (static_cast<int>(format))
    {
    case 0:
        switch (static_cast<int>(num_channels)) // 8 Bit Unsigned Norm
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
        switch (static_cast<int>(num_channels)) // 8 Bit Signed Norm
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
        switch (static_cast<int>(num_channels)) // 8 Bit Unsigned Int
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
        switch (static_cast<int>(num_channels)) // 8 Bit Signed Int
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
        switch (static_cast<int>(num_channels)) // 16 Bit Unsigned Norm
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
        switch (static_cast<int>(num_channels)) // 16 Bit Signed Norm
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
        switch (static_cast<int>(num_channels)) // 16 Bit Unsigned Int
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
        switch (static_cast<int>(num_channels)) // 16 Bit Signed Int
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
        switch (static_cast<int>(num_channels)) // 32 Bit Unsigned Int
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
        switch (static_cast<int>(num_channels)) // 32 Bit Signed Int
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
        switch (static_cast<int>(num_channels)) // 16 Bit Float
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
        switch (static_cast<int>(num_channels)) // 32 Bit Float
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
