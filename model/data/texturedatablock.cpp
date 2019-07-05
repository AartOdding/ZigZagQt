#include "model/data/texturedatablock.h"

const QString TextureDataBlock::data_type_name{ "texture" };



TextureDataBlock::TextureDataBlock()
    : BaseDataBlock(data_type_name)
{
    initializeOpenGLFunctions();

    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(pixel_type), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenFramebuffers(1, &fbo_handle);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_handle, 0);

    connect(&resolution_x, &IntegerParameter::has_changed, this, &TextureDataBlock::reallocate_texture);
    connect(&resolution_y, &IntegerParameter::has_changed, this, &TextureDataBlock::reallocate_texture);
}


TextureDataBlock::~TextureDataBlock()
{
    glDeleteFramebuffers(1, &fbo_handle);
    glDeleteTextures(1, &texture_handle);
}


std::vector<BaseParameter*> TextureDataBlock::get_parameters()
{
    return { &resolution_x, &resolution_y };
}


void TextureDataBlock::bind_as_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
}


void TextureDataBlock::bind_as_texture(int texture_index)
{
    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + texture_index));
    glBindTexture(GL_TEXTURE_2D, texture_handle);
}


void TextureDataBlock::reallocate_texture()
{
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(pixel_type), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
}
