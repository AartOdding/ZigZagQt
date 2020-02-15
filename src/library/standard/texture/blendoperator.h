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

    BlendOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator* create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    EnumParameter m_blendMode{ this, QStringLiteral("Blend Mode"), {
          QStringLiteral("Over"), QStringLiteral("Add"), QStringLiteral("Subtract"),
          QStringLiteral("Multiply"), QStringLiteral("Divide"), QStringLiteral("Average"),
          QStringLiteral("Difference"), }, 0 };

    DataInput m_textureA{ this, QStringLiteral("Texture 0"), TextureData::description };
    DataInput m_textureB{ this, QStringLiteral("Texture 1"), TextureData::description };

    TextureData m_outputTexture{ this, "Output Texture" };
    //TextureView m_outputView{ this, &m_outputTexture };

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
