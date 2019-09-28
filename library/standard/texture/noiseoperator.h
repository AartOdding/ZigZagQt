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

    static BaseOperator * create() { return new NoiseOperator(); }

    void parameter_changed(BaseParameter* parameter) override;


    static const inline OperatorTypeInfo Type { "Noise", "Video Synthesis", {  },
                                              { &TextureData::Type }, &TextureView::Type, &create };

private:

    EnumDefinition BoolEnum { "BoolEnum", { "False", "True" } };

    Double4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Double4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };

    Double2Par translation{ this, "Translate", { 0, 0 } };
    DoublePar rotation{ this, "Rotate", 0 };
    Double2Par scale{ this, "Scale", { 1, 1 } };

    EnumPar use_z_value{ this, "Use Z Value", BoolEnum, 0 };
    DoublePar z_value{ this, "Z Value", 0 };

    TextureData output_texture{ this, "Texture" };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
