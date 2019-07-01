#include "model/operator/shadertop.h"
#include "model/programmodel.h"

#include <iostream>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


static float corners[8] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f };

static const char vertex_shader_source[] = R"(
#version 330
layout(location = 0)in vec2 vert;
void main()
{
    gl_Position = vec4(vert, 0, 1);
}
)";

static const char default_fragment_shader_source[] = R"(
#version 330
layout(location = 0) out vec4 color_out;
void main()
{
    color_out = vec4(0, 0, 1, 1);
}
)";



ShaderTOP::ShaderTOP(ProgramModel& model)
    : ShaderTOP(model, 0, default_fragment_shader_source)
{ }


ShaderTOP::ShaderTOP(ProgramModel& model, int num_inputs, const QString& source)
    : BaseOperator(model), fragment_shader_source(source)
{
    //set_num_inputs(num_inputs);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(corners), corners, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    char const * vertex_source_ptr = vertex_shader_source;
    glShaderSource(vertex_shader, 1, &vertex_source_ptr, nullptr);
    glCompileShader(vertex_shader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
    }


    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string std_frag_src = fragment_shader_source.toStdString();
    char const * fragment_source_ptr = std_frag_src.c_str();
    glShaderSource(fragment_shader, 1, &fragment_source_ptr, nullptr);
    glCompileShader(fragment_shader);


    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
    }
}


ShaderTOP::~ShaderTOP()
{
    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(shader_program);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}


void ShaderTOP::render()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //std::cout << "render\n";
}


bool ShaderTOP::can_render()
{
    return true;
}


void ShaderTOP::recompile()
{
    auto new_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char const * fragment_source_ptr = fragment_shader_source.toStdString().c_str();
    glShaderSource(new_fragment_shader, 1, &fragment_source_ptr, nullptr);
    glCompileShader(new_fragment_shader);

    auto new_shader_program = glCreateProgram();
    glAttachShader(new_shader_program, vertex_shader);
    glAttachShader(new_shader_program, new_fragment_shader);

    glLinkProgram(new_shader_program);

    auto old_fragment_shader = fragment_shader;
    auto old_shader_program = shader_program;

    fragment_shader = new_fragment_shader;
    shader_program = new_shader_program;

    glDetachShader(old_shader_program, vertex_shader);
    glDetachShader(old_shader_program, old_fragment_shader);

    glDeleteShader(old_fragment_shader);
    glDeleteProgram(old_shader_program);
}
