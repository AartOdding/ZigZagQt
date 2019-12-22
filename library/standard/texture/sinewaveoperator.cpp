#include "sinewaveoperator.h"

#include <QMatrix>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <iostream>


bool SineWaveOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram SineWaveOperator::flat_shader;
QOpenGLShaderProgram SineWaveOperator::radial_shader;
QOpenGLShaderProgram SineWaveOperator::concentric_shader;
std::array<QOpenGLShaderProgram*, 3> SineWaveOperator::shaders { &flat_shader, &radial_shader, &concentric_shader };
GLuint SineWaveOperator::vao;
GLuint SineWaveOperator::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };




BaseOperator * SineWaveOperator::create()
{
    return new SineWaveOperator();
}


const OperatorDescription SineWaveOperator::description
{
    "Sine Wave",
    "Video Synthesis",
    &create,
    { },
    { &TextureData::Type },
    &TextureView::Type,
};


SineWaveOperator::SineWaveOperator()
    : BaseOperator(description)
{
    initializeOpenGLFunctions();
    should_update = true;
}


void SineWaveOperator::run()
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;

        // Flat Sine wave shader
        flat_shader.create();
        flat_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/basic.vert");
        flat_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/sine_wave.frag");
        auto success = flat_shader.link();
        Q_ASSERT(success);

        glUseProgram(flat_shader.programId());
        flat_shader.setUniformValue(flat_shader.uniformLocation("output_range_x"), -10.0f, 10.0f);
        flat_shader.setUniformValue(flat_shader.uniformLocation("output_range_y"), -10.0f, 10.0f);

        // Radial sine wave shader
        radial_shader.create();
        radial_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/basic.vert");
        radial_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/radial_sine_wave.frag");
        success = radial_shader.link();
        Q_ASSERT(success);

        glUseProgram(radial_shader.programId());
        radial_shader.setUniformValue(radial_shader.uniformLocation("output_range_x"), -10.0f, 10.0f);
        radial_shader.setUniformValue(radial_shader.uniformLocation("output_range_y"), -10.0f, 10.0f);

        // Concentric sine wave shader
        concentric_shader.create();
        concentric_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/basic.vert");
        concentric_shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/concentric_sine_wave.frag");
        success = concentric_shader.link();
        Q_ASSERT(success);

        glUseProgram(concentric_shader.programId());
        concentric_shader.setUniformValue(concentric_shader.uniformLocation("output_range_x"), -10.0f, 10.0f);
        concentric_shader.setUniformValue(concentric_shader.uniformLocation("output_range_y"), -10.0f, 10.0f);



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
        auto shader = shaders[wave_type.getIndex()];

        output_texture.bind_as_framebuffer();

        glUseProgram(shader->programId());
        glBindVertexArray(vao);

        shader->setUniformValue(shader->uniformLocation("color_a"), color_a.get());
        shader->setUniformValue(shader->uniformLocation("color_b"), color_b.get());

        auto translated = glm::translate(glm::mat3(1), glm::vec2(translation.x(), translation.y()));
        auto scaled = glm::scale(translated, glm::vec2(scale.x(), scale.y()));
        auto rotated = glm::rotate(scaled, static_cast<float>(rotation.get()));
        glUniformMatrix3fv(shader->uniformLocation("transformation"), 1, GL_FALSE, (float*)(&rotated));

        if (wave_type.getIndex()  == 1) // Radial
        {
            radial_shader.setUniformValue(radial_shader.uniformLocation("frequency"), static_cast<float>(frequency.get()));
        }
        else if (wave_type.getIndex() == 2) // Conncentric
        {
            concentric_shader.setUniformValue(concentric_shader.uniformLocation("phase"), static_cast<float>(phase.get()));
        }

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        update_view();
        should_update = false;
    }
}


void SineWaveOperator::parameterChangeEvent(const BaseParameter* parameter)
{
    should_update = true;
}
