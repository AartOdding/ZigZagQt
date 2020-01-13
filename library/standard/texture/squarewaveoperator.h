#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"

#include "texturedata.h"
#include "textureview.h"



class SquareWaveOperator : public BaseOperator,
                           public QOpenGLFunctions_3_3_Core
{

public:

    SquareWaveOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    EnumDefinition WaveType { "Wave Type", { "Flat", "Radial", "Concentric" } };

    ColorPar color_a{ this, "High Color", Qt::white };
    ColorPar color_b{ this, "Low Color", Qt::black };

    EnumParameter wave_type{ this, "Wave Type", WaveType };
    FloatPar duty_cyce{ this, "Duty Cycle", 0.5, -1, 1 };
    FloatPar frequency{ this, "Frequency", 6, 0.5, 1000000 };
    FloatPar phase{ this, "Phase", 0 };

    Float2Par translation{ this, "Translate", { 0, 0 } };
    FloatPar rotation{ this, "Rotate", 0 };
    Float2Par scale{ this, "Scale", { 1, 1 } };

    TextureData output_texture{ this, "Texture" };
    TextureView outputView{ this, &output_texture };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram flat_shader;
    static QOpenGLShaderProgram radial_shader;
    static QOpenGLShaderProgram concentric_shader;
    static std::array<QOpenGLShaderProgram*, 3> shaders;
    static GLuint vao;
    static GLuint vbo;

};
