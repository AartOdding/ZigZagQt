#include "sinewaveoperator.h"

#include <QMatrix>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <iostream>


bool SineWaveOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram SineWaveOperator::shader;
GLuint SineWaveOperator::vao;
GLuint SineWaveOperator::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };



SineWaveOperator::SineWaveOperator()
    : BaseOperator(Type)
{
    initializeOpenGLFunctions();
    should_update = true;
}


void SineWaveOperator::run()
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/basic.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/sine_wave.frag");
        auto success = shader.link();
        Q_ASSERT(success);

        glUseProgram(shader.programId());
        shader.setUniformValue(shader.uniformLocation("output_range_x"), -10.0f, 10.0f);
        shader.setUniformValue(shader.uniformLocation("output_range_y"), -10.0f, 10.0f);

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

    if (should_update)
    {
        output_texture.bind_as_framebuffer();

        glUseProgram(shader.programId());
        glBindVertexArray(vao);

        shader.setUniformValue(shader.uniformLocation("color_a"), color_a.x(), color_a.y(), color_a.z(), color_a.w());
        shader.setUniformValue(shader.uniformLocation("color_b"), color_b.x(), color_b.y(), color_b.z(), color_b.w());

        auto scaled = glm::scale(glm::mat3(1), glm::vec2(scale.x(), scale.y()));
        auto rotated = glm::rotate(scaled, static_cast<float>(rotation.get()));
        auto translated = glm::translate(rotated, glm::vec2(translation.x(), translation.y()));

        glUniformMatrix3fv(shader.uniformLocation("transformation"), 1, GL_FALSE, (float*)(&translated));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        should_update = false;
        update_view();
    }
}


void SineWaveOperator::parameter_changed(BaseParameter* parameter)
{
    should_update = true;
}
