#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"

#include "texturedata.h"
#include "textureview.h"



class ConcentricSawtoothWaveOperator : public BaseOperator,
                                       public QOpenGLFunctions_3_3_Core
{

public:

    ConcentricSawtoothWaveOperator();

    void run() override;

    static BaseOperator * create() { return new ConcentricSawtoothWaveOperator(); }

    void parameter_changed(BaseParameter* parameter) override;


    static const inline OperatorTypeInfo Type { "Concentric Sawtooth Wave", "Video Synthesis", {  },
                                              { &TextureData::Type }, &TextureView::Type, &create };

private:

    Float4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Float4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };

    FloatPar phase{ this, "Phase", 0 };
    FloatPar peak_position{ this, "Peak Position", 0.5, 0, 1 };

    Float2Par translation{ this, "Translate", { 0, 0 } };
    FloatPar rotation{ this, "Rotate", 0 };
    Float2Par scale{ this, "Scale", { 1, 1 } };

    TextureData output_texture{ this, "Texture" };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
