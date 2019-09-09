#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"


const inline EnumDefinition BlendMode
{
    "BlendMode",
    {
        "Over",
        "Add",
        "Subtract",
        "Multiply",
        "Divide",
        "Average",
        "Difference",
    }
};


class BlendOperator : public BaseOperator,
                      public QOpenGLFunctions_3_3_Core
{

public:

    BlendOperator();


    void run() override;


    static BaseOperator* create() { return new BlendOperator(); }

    static const inline OperatorTypeInfo Type { "Blend", "Standard/Texture",
        { &TextureData::Type, &TextureData::Type },
        { &TextureData::Type }, true, &create };

private:

    EnumPar blend_mode{ this, BlendMode, "Blend Mode", 0 };

    DataInput texture_a{ this, TextureData::Type };
    DataInput texture_b{ this, TextureData::Type };

    TextureData output_texture{ this };


    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
