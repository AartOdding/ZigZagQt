#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/baseoperator.h"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"



class DisplacementOperator : public BaseOperator,
                             public QOpenGLFunctions_3_3_Core
{

public:

    DisplacementOperator();

    void run() override;

    static BaseOperator* create() { return new DisplacementOperator(); }

    void parameter_changed(BaseParameter* parameter) override;


    static const inline OperatorTypeInfo Type { "Displace", "Video Edit",
        { &TextureData::Type, &TextureData::Type },
        { &TextureData::Type }, &TextureView::Type, &create };

private:

    FloatPar direction{ this, "Direction", 0 };
    FloatPar amount{ this, "Amount", 0 };

    DataInput input_texture{ this, "Input", TextureData::Type };
    TextureData output_texture{ this, "Result" };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
