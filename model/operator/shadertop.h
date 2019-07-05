#pragma once

#include "model/operator/baseoperator.h"


#include <QOpenGLFunctions_3_2_Core>

class ProgramModel;



class ShaderTOP : public BaseOperator,
                  protected QOpenGLFunctions_3_2_Core
{

public:


    ShaderTOP(ProgramModel& model);

    ShaderTOP(ProgramModel& model, int num_inputs, const QString& source);

    ~ShaderTOP() override;


    void render() override;

    // Whether the TOP is in any state to render: Shaders compiled succesfully,
    // Proper inputs connected etc.
    bool can_render() override;


public slots:

    void recompile();


private:

    QString fragment_shader_source;

    GLuint shader_program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    GLuint vao;
    GLuint vbo;

};
