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

    SineWaveOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorKind description;


    virtual QVariantMap storeState() const override;

    virtual void loadState(const QVariantMap& state) override;

private:

    ColorPar color_a{ this, "High Color", Qt::white };
    ColorPar color_b{ this, "Low Color", Qt::black };

    EnumParameter wave_type{ this, "Wave Type", { "Flat", "Radial", "Concentric" } };
    FloatParameter frequency{ this, "Frequency", 6, 0.5, 1000000 };
    FloatParameter phase{ this, "Phase", 0 };

    Float2Parameter translation{ this, "Translate", { 0, 0 } };
    FloatParameter rotation{ this, "Rotate", 0 };
    Float2Parameter scale{ this, "Scale", { 1, 1 } };

    Transform2DParameter transformation{ this, "Transformation" };

    TextureData output_texture{ this, "Texture" };
    TextureView outputView{ this, &output_texture };

    bool should_update = false;

    QOpenGLShaderProgram flat_shader;
    QOpenGLShaderProgram radial_shader;
    QOpenGLShaderProgram concentric_shader;
    std::array<QOpenGLShaderProgram*, 3> shaders{ &flat_shader, &radial_shader, &concentric_shader };
    GLuint vao;
    GLuint vbo;

};
