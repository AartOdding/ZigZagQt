#pragma once

#include <array>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "model/BaseOperator.hpp"
#include "model/datainput.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"



class FadeOperator : public BaseOperator,
                     public QOpenGLFunctions_3_3_Core
{

public:

    FadeOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator* create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    FloatParameter position{ this, "Fade Position", 0, 0, 4 };

    DataInput texture_0{ this, "Input 0", TextureData::Type };
    DataInput texture_1{ this, "Input 1", TextureData::Type };
    DataInput texture_2{ this, "Input 2", TextureData::Type };
    DataInput texture_3{ this, "Input 3", TextureData::Type };
    DataInput texture_4{ this, "Input 4", TextureData::Type };

    std::array<DataInput*, 5> textures = { &texture_0, &texture_1, &texture_2, &texture_3, &texture_4 };

    TextureData output_texture{ this, "Result" };
    TextureView outputView{ this, &output_texture };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
