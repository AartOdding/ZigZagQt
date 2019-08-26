#include "texturedata.h"
#include "application.h"
#include <iostream>


TextureData::TextureData(BaseOperator* parent_operator)
    : BaseDataType(parent_operator, Type)
{
    initializeOpenGLFunctions();

    resolution.set_update_mode(parameter::UpdateMode::NecessaryUpdates);
    resolution_y.set_update_mode(parameter::UpdateMode::NecessaryUpdates);

    connect(&resolution, &parameter::Int::value_changed, this, &TextureData::reallocate_texture);
    connect(&resolution_y, &parameter::Int::value_changed, this, &TextureData::reallocate_texture);
}


TextureData::~TextureData()
{
    Q_ASSERT(!currently_allocated);
}


void TextureData::acquire_resources()
{
    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, resolution.get<0>(), resolution.get<0>(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

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
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);
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


void TextureData::reallocate_texture()
{
    if (currently_allocated)
    {
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, resolution.get<0>(), resolution.get<1>(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }
}
