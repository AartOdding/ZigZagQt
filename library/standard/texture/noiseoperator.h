#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"

#include "texturedata.h"
#include "textureview.h"



class NoiseOperator : public BaseOperator,
                      public QOpenGLFunctions_3_3_Core
{

public:

    NoiseOperator();

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create();

    static const OperatorDescription description;

private:

    EnumDefinition BoolEnum { "BoolEnum", { "False", "True" } };

    Float4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Float4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };

    Float2Par translation{ this, "Translate", { 0, 0 } };
    FloatPar rotation{ this, "Rotate", 0 };
    Float2Par scale{ this, "Scale", { 1, 1 } };

    EnumPar use_z_value{ this, "Use Z Value", BoolEnum, 0 };
    FloatPar z_value{ this, "Z Value", 0 };

    TextureData output_texture{ this, "Texture" };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
