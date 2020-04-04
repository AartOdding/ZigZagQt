#include "displacementoperator.h"


#include <iostream>
#include <cmath>

bool DisplacementOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram DisplacementOperator::shader;
GLuint DisplacementOperator::vao;
GLuint DisplacementOperator::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };




BaseOperator* DisplacementOperator::create(BaseZigZagObject* parent)
{
    return new DisplacementOperator(parent);
}


const OperatorDescription DisplacementOperator::Type
{
    "Displace",
    "Video Edit",
    &create,
    { &TextureData::description, &TextureData::description },
    { &TextureData::description },
    &TextureView::Type
};


DisplacementOperator::DisplacementOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, Type)
{
    initializeOpenGLFunctions();
}


void DisplacementOperator::run()
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;

        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/vert/basic.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/frag/displace.frag");
        auto success = shader.link();
        Q_ASSERT(success);

        glUseProgram(shader.programId());
        shader.setUniformValue(shader.uniformLocation("output_range_x"), 0.0f, 1.0f);
        shader.setUniformValue(shader.uniformLocation("output_range_y"), 0.0f, 1.0f);
        shader.setUniformValue(shader.uniformLocation("inputTexture"), 0);
        shader.setUniformValue(shader.uniformLocation("displaceTexture"), 1);


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

    const TextureData* input_tex = dynamic_cast<const TextureData*>(input_texture.get_connection());
    const TextureData* displace_tex = dynamic_cast<const TextureData*>(displace_texture.get_connection());

    output_texture.bindFramebuffer();

    glUseProgram(shader.programId());
    glBindVertexArray(vao);

    shader.setUniformValue(shader.uniformLocation("strength"),  (float)strength.get() / 100.0f);
    shader.setUniformValue(shader.uniformLocation("direction"), (float)direction.get());
    shader.setUniformValue(shader.uniformLocation("offset"),    (float)offset.get());
    shader.setUniformValue(shader.uniformLocation("channel"),   (int)channel.getIndex());


    if (input_tex)
    {
        input_tex->bindTexture(0);
    }
    else
    {
        TextureData::bind_empty_texture(0);
    }

    if (displace_tex)
    {
        displace_tex->bindTexture(1);
    }
    else
    {
        TextureData::bind_empty_texture(1);
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    updateView();
}


void DisplacementOperator::parameterChangedEvent(const BaseParameter* parameter)
{

}


