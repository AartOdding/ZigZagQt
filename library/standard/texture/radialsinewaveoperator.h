#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"

#include "texturedata.h"
#include "textureview.h"



class RadialSineWaveOperator : public BaseOperator,
                               public QOpenGLFunctions_3_3_Core
{

public:

    RadialSineWaveOperator();

    void run() override;

    static BaseOperator * create() { return new RadialSineWaveOperator(); }

    void parameter_changed(BaseParameter* parameter) override;


    static const inline OperatorTypeInfo Type { "Radial Sine Wave", "Video Synthesis", {  },
                                              { &TextureData::Type }, &TextureView::Type, &create };

private:

    Double4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Double4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };
    DoublePar frequency{ this, "Frequency", 6, 0.5, 1000000 };

    Double2Par translation{ this, "Translate", { 0, 0 } };
    DoublePar rotation{ this, "Rotate", 0 };
    Double2Par scale{ this, "Scale", { 1, 1 } };

    TextureData output_texture{ this, "Texture" };

    bool should_update = false;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
