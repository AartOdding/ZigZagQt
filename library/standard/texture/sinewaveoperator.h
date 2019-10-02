#pragma once

#include <array>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"

#include "texturedata.h"
#include "textureview.h"



class SineWaveOperator : public BaseOperator,
                         public QOpenGLFunctions_3_3_Core
{

public:

    SineWaveOperator();

    void run() override;

    void parameter_changed(BaseParameter* parameter) override;


    static BaseOperator * create() { return new SineWaveOperator(); }

    static const inline OperatorTypeInfo Type { "Sine Wave", "Video Synthesis", {  },
                                              { &TextureData::Type }, &TextureView::Type, &create };

private:

    EnumDefinition WaveType { "Wave Type", { "Flat", "Radial", "Concentric" } };

    Float4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Float4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };

    EnumPar wave_type{ this, "Wave Type", WaveType };
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
