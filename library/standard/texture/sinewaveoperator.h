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

    static BaseOperator * create() { return new SineWaveOperator(); }

    void parameter_changed(BaseParameter* parameter) override;


    static const inline OperatorTypeInfo Type { "Flat Sine Wave", "Video Synthesis", {  },
                                              { &TextureData::Type }, &TextureView::Type, &create };

private:

    EnumDefinition WaveType { "Wave Type", { "Flat", "Radial", "Concentric" } };

    Double4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Double4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };

    EnumPar wave_type{ this, "Wave Type", WaveType };
    DoublePar frequency{ this, "Frequency", 6, 0.5, 1000000 };
    DoublePar phase{ this, "Phase", 0 };


    Double2Par translation{ this, "Translate", { 0, 0 } };
    DoublePar rotation{ this, "Rotate", 0 };
    Double2Par scale{ this, "Scale", { 1, 1 } };

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
