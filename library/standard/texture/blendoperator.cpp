#include "blendoperator.h"


#include <iostream>

bool BlendOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram BlendOperator::shader;
GLuint BlendOperator::vao;
GLuint BlendOperator::vbo;

// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };



const EnumDefinition BlendOperator::BlendMode
{
    "BlendMode",
    {
        "Over",
        "Add",
        "Subtract",
        "Multiply",
        "Divide",
        "Average",
        "Difference",
    }
};



const OperatorDescription BlendOperator::description {
    "Blend",
    "Video Edit",
    &create,
    { &TextureData::Type, &TextureData::Type },
    { &TextureData::Type },
    &TextureView::Type
};



BaseOperator* BlendOperator::create(BaseZigZagObject* parent)
{
    return new BlendOperator(parent);
}



BlendOperator::BlendOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    initializeOpenGLFunctions();
}


void BlendOperator::run()
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/vert/basic.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/frag/blend.frag");
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

    auto a = static_cast<const TextureData*>(texture_a.get_connection());
    auto b = static_cast<const TextureData*>(texture_b.get_connection());

    if (a && b)
    {
        output_texture.bind_as_framebuffer();
        glUseProgram(shader.programId());
        glBindVertexArray(vao);
        shader.setUniformValue(shader.uniformLocation("blend_mode"), blend_mode.getIndex());
        a->bind_as_texture(0);
        b->bind_as_texture(1);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    else
    {
        output_texture.bind_as_framebuffer();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    update_view();

}


void BlendOperator::parameterChangeEvent(const BaseParameter* parameter)
{

}


