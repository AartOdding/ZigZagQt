#include "fadeoperator.h"


#include <iostream>
#include <cmath>



bool FadeOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram FadeOperator::shader;
GLuint FadeOperator::vao;
GLuint FadeOperator::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };



BaseOperator* FadeOperator::create(BaseZigZagObject* parent)
{
    return new FadeOperator(parent);
}


const OperatorDescription FadeOperator::description
{
    "Fade",
    "Video Edit",
    &create,
    { &TextureData::description, &TextureData::description },
    { &TextureData::description },
    &TextureView::Type
};




FadeOperator::FadeOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    initializeOpenGLFunctions();
}


void FadeOperator::run()
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/vert/basic.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/frag/fade.frag");
        auto success = shader.link();
        Q_ASSERT(success);

        glUseProgram(shader.programId());
        shader.setUniformValue(shader.uniformLocation("output_range_x"), 0.0f, 1.0f);
        shader.setUniformValue(shader.uniformLocation("output_range_y"), 0.0f, 1.0f);
        shader.setUniformValue(shader.uniformLocation("input_a"), 0);
        shader.setUniformValue(shader.uniformLocation("input_b"), 1);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        //unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    int index_a = std::floor(position.get());
    int index_b = std::ceil(position.get());
    double whole;
    float fract = modf(position.get(), &whole);


    const TextureData* tex_a = static_cast<const TextureData*>(textures[index_a]->getConnectedData());
    const TextureData* tex_b = static_cast<const TextureData*>(textures[index_b]->getConnectedData());

    output_texture.bindFramebuffer();
    glUseProgram(shader.programId());
    glBindVertexArray(vao);
    shader.setUniformValue(shader.uniformLocation("fade_position"), fract);

    if (tex_a)
    {
        tex_a->bindTexture(0);
    }
    else
    {
        TextureData::bind_empty_texture(0);
    }

    if (tex_b)
    {
        tex_b->bindTexture(1);
    }
    else
    {
        TextureData::bind_empty_texture(1);
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    updateView();
}


void FadeOperator::parameterChangeEvent(const BaseParameter* parameter)
{

}


