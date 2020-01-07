#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"





class BlendOperator : public BaseOperator,
                      public QOpenGLFunctions_3_3_Core
{

public:

    BlendOperator();

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator* create();

    static const OperatorDescription description;

    static const EnumDefinition BlendMode;

private:

    EnumParameter blend_mode{ this, "Blend Mode", BlendMode, 0 };

    DataInput texture_a{ this, "Texture in 0", TextureData::Type };
    DataInput texture_b{ this, "Texture in 1", TextureData::Type };

    TextureData output_texture{ this, "Output Texture" };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
