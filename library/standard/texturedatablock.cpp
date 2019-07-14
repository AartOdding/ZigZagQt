#include "texturedatablock.h"




TextureDataBlock::TextureDataBlock()
    : BaseDataBlock("texture")
{
    initializeOpenGLFunctions();

    connect(&resolution_x, &IntegerParameter::has_changed, this, &TextureDataBlock::reallocate_texture);
    connect(&resolution_y, &IntegerParameter::has_changed, this, &TextureDataBlock::reallocate_texture);
}


TextureDataBlock::~TextureDataBlock()
{

}


void TextureDataBlock::acquire_resources()
{
    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, pixel_type.get_ordinal(), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenFramebuffers(1, &fbo_handle);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_handle, 0);

    currently_allocated = true;
}

void TextureDataBlock::release_resources()
{
    glDeleteFramebuffers(1, &fbo_handle);
    glDeleteTextures(1, &texture_handle);

    currently_allocated = false;
}


void TextureDataBlock::bind_as_framebuffer()
{
    if (currently_allocated)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
    }
}


void TextureDataBlock::bind_as_texture(int texture_index)
{
    if (currently_allocated)
    {
        glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + texture_index));
        glBindTexture(GL_TEXTURE_2D, texture_handle);
    }
}


void TextureDataBlock::reallocate_texture()
{
    if (currently_allocated)
    {
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, pixel_type.get_ordinal(), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }
}
