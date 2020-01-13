#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"



class DisplacementOperator : public BaseOperator,
                             public QOpenGLFunctions_3_3_Core
{

public:

    DisplacementOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator* create(BaseZigZagObject* parent);

    static const OperatorDescription Type;

private:

    FloatPar direction{ this, "Direction", 0 };
    FloatPar amount{ this, "Amount", 0 };

    DataInput input_texture{ this, "Input", TextureData::Type };
    TextureData output_texture{ this, "Result" };
    TextureView outputView{ this, &output_texture };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
