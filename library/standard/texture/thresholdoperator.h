#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"


class ThresholdOperator : public BaseOperator,
                          public QOpenGLFunctions_3_3_Core
{

public:

    ThresholdOperator();

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator* create();

    static const OperatorDescription description;

private:

    DataInput texture_in{ this, "Input", TextureData::Type };

    TextureData output_texture{ this, "Output Texture" };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
