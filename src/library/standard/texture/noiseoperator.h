#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"

#include "texturedata.h"
#include "textureview.h"



class NoiseOperator : public BaseOperator,
                      public QOpenGLFunctions_3_3_Core
{

public:

    NoiseOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangedEvent(const BaseParameter* parameter) override;


    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    ColorParameter m_highColor{ this, "High Color" };
    ColorParameter m_lowColor{ this, "Low Color" };
    // color_a{ this, "High Color", { 1, 1, 1, 1 }, 0, 1 };
    //Float4Par color_b{ this, "Low Color", { 0, 0, 0, 1 }, 0, 1 };

    Float2Parameter translation{ this, "Translate", { 0, 0 } };
    FloatParameter rotation{ this, "Rotate", 0 };
    Float2Parameter scale{ this, "Scale", { 1, 1 } };

    EnumParameter use_z_value{ this, "Use Z Value", { "False", "True" }, 0 };
    FloatParameter z_value{ this, "Z Value", 0 };

    TextureData output_texture{ this, "Texture" };
    //TextureView outputView{ this, &output_texture };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
