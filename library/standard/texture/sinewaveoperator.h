#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"

#include "texturedata.h"



class SineWaveOperator : public BaseOperator,
                         public QOpenGLFunctions_3_3_Core
{

public:

    SineWaveOperator();

    void run() override;

    static BaseOperator * create() { return new SineWaveOperator(); }

    static const inline OperatorTypeInfo Type { "Sine Wave", "Standard/Texture", { },
                                                { &TextureData::Type }, true, &create };


private:

    TextureData output_texture{ this, "Output Texture" };

    Float4Par color_a{ this, "Color A", { 1, 1, 1, 1 }, 0, 1 };
    Float4Par color_b{ this, "Color B", { 0, 0, 0, 1 }, 0, 1 };

    Float2Par translation{ this, "Translate", 0 };
    FloatPar rotation{ this, "Rotate", 0 };
    Float2Par scale{ this, "Scale", 1 };


    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
