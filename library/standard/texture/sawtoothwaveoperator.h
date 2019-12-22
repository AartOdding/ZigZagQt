#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"

#include "texturedata.h"
#include "textureview.h"



class SawtoothWaveOperator : public BaseOperator,
                             public QOpenGLFunctions_3_3_Core
{

public:

    SawtoothWaveOperator();

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create();

    static const OperatorDescription description;

    static const EnumDefinition WaveType;

private:


    ColorPar color_a{ this, "High Color", Qt::white };
    ColorPar color_b{ this, "Low Color", Qt::black };

    EnumPar wave_type{ this, "Wave Type", WaveType };
    FloatPar peak_position{ this, "Peak Position", 0.5, 0, 1 };
    FloatPar frequency{ this, "Frequency", 6, 0.5, 1000000 };
    FloatPar phase{ this, "Phase", 0 };

    Float2Par translation{ this, "Translate", { 0, 0 } };
    FloatPar rotation{ this, "Rotate", 0 };
    Float2Par scale{ this, "Scale", { 1, 1 } };

    TextureData output_texture{ this, "Texture" };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram flat_shader;
    static QOpenGLShaderProgram radial_shader;
    static QOpenGLShaderProgram concentric_shader;
    static std::array<QOpenGLShaderProgram*, 3> shaders;
    static GLuint vao;
    static GLuint vbo;

};
