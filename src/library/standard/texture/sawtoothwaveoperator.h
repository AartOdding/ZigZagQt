#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"

#include "texturedata.h"
#include "textureview.h"



class SawtoothWaveOperator : public BaseOperator,
                             public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:

    SawtoothWaveOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;


    Q_INVOKABLE void storeState(QVariantMap* state) const
    {
        state->insert(QStringLiteral("test int"), QVariant(43));
        state->insert(QStringLiteral("operator"), QVariant(QStringLiteral("Sawtooth")));
    }

private:


    ColorPar color_a{ this, "High Color", Qt::white };
    ColorPar color_b{ this, "Low Color", Qt::black };

    EnumParameter wave_type{ this, "Wave Type", { "Flat", "Radial", "Concentric" } };
    FloatParameter peak_position{ this, "Peak Position", 0.5, 0, 1 };
    FloatParameter frequency{ this, "Frequency", 6, 0.5, 1000000 };
    FloatParameter phase{ this, "Phase", 0 };

    Float2Parameter translation{ this, "Translate", { 0, 0 } };
    FloatParameter rotation{ this, "Rotate", 0 };
    Float2Parameter scale{ this, "Scale", { 1, 1 } };

    TextureData output_texture{ this, "Texture" };
    //TextureView outputView{ this, &output_texture };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram flat_shader;
    static QOpenGLShaderProgram radial_shader;
    static QOpenGLShaderProgram concentric_shader;
    static std::array<QOpenGLShaderProgram*, 3> shaders;
    static GLuint vao;
    static GLuint vbo;

};
