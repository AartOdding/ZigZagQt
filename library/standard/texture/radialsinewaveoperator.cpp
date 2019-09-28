#include "radialsinewaveoperator.h"

#include <QMatrix>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <iostream>


bool RadialSineWaveOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram RadialSineWaveOperator::radial_shader;
GLuint RadialSineWaveOperator::vao;
GLuint RadialSineWaveOperator::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };



RadialSineWaveOperator::RadialSineWaveOperator()
    : BaseOperator(Type)
{
    initializeOpenGLFunctions();
    should_update = true;
}


void RadialSineWaveOperator::run()
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        radial_shader.create();
        radial_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/basic.vert");
        radial_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/radial_square_wave.frag");
        auto success = radial_shader.link();
        Q_ASSERT(success);

        glUseProgram(radial_shader.programId());
        radial_shader.setUniformValue(radial_shader.uniformLocation("output_range_x"), -10.0f, 10.0f);
        radial_shader.setUniformValue(radial_shader.uniformLocation("output_range_y"), -10.0f, 10.0f);

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

        glUseProgram(radial_shader.programId());
        glBindVertexArray(vao);

        radial_shader.setUniformValue(radial_shader.uniformLocation("frequency"), static_cast<float>(frequency.get()));
        radial_shader.setUniformValue(radial_shader.uniformLocation("color_a"), color_a.x(), color_a.y(), color_a.z(), color_a.w());
        radial_shader.setUniformValue(radial_shader.uniformLocation("color_b"), color_b.x(), color_b.y(), color_b.z(), color_b.w());

        auto translated = glm::translate(glm::mat3(1), glm::vec2(translation.x(), translation.y()));
        auto scaled = glm::scale(translated, glm::vec2(scale.x(), scale.y()));
        auto rotated = glm::rotate(scaled, static_cast<float>(rotation.get()));
        //auto translated = glm::translate(rotated, glm::vec2(translation.x(), translation.y()));

        glUniformMatrix3fv(radial_shader.uniformLocation("transformation"), 1, GL_FALSE, (float*)(&rotated));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        should_update = false;
        update_view();
    }
}


void RadialSineWaveOperator::parameter_changed(BaseParameter* parameter)
{
    should_update = true;
}
