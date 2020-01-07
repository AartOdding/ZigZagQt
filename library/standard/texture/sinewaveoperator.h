#pragma once

#include <array>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"

#include "texturedata.h"
#include "textureview.h"



class SineWaveOperator : public BaseOperator,
                         public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:

    SineWaveOperator();

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create();

    static const OperatorDescription description;


    virtual QVariantMap storeState() const override;

    virtual void loadState(const QVariantMap& state) override;

private:

    EnumDefinition WaveType { "Wave Type", { "Flat", "Radial", "Concentric" } };

    ColorPar color_a{ this, "High Color", Qt::white };
    ColorPar color_b{ this, "Low Color", Qt::black };

    EnumParameter wave_type{ this, "Wave Type", WaveType };
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
