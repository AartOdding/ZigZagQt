#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"


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

    void parameter_changed(BaseParameter* parameter) override;


    static const inline OperatorTypeInfo Type { "Blend", "Texture",
        { &TextureData::Type, &TextureData::Type },
        { &TextureData::Type }, &TextureView::Type, &create };

private:

    EnumPar blend_mode{ this, "Blend Mode", BlendMode, 0 };

    DataInput texture_a{ this, "Texture in 0", TextureData::Type };
    DataInput texture_b{ this, "Texture in 1", TextureData::Type };

    TextureData output_texture{ this, "Output Texture" };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
