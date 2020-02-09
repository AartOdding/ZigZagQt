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

    ThresholdOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator* create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    DataInput texture_in{ this, "Input", TextureData::description };

    TextureData output_texture{ this, "Output Texture" };
    //TextureView outputView{ this, &output_texture };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
