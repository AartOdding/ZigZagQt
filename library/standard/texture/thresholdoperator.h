#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"


class ThresholdOperator : public BaseOperator,
                          public QOpenGLFunctions_3_3_Core
{

public:

    ThresholdOperator();

    void run() override;

    void parameter_changed(BaseParameter* parameter) override;


    static BaseOperator* create() { return new ThresholdOperator(); }

    static const inline OperatorTypeInfo Type { "Threshold", "Texture",
        { &TextureData::Type }, { &TextureData::Type }, &TextureView::Type, &create };

private:

    DataInput texture_in{ this, "Input", TextureData::Type };

    TextureData output_texture{ this, "Output Texture" };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
