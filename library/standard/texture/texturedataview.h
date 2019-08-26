#pragma once

#include "view/opengldataview.h"
#include "texturedata.h"

#include <QOpenGLShaderProgram>


class OperatorView;


class TextureDataView : public OpenGLDataView
{

public:

    TextureDataView(const BaseDataType* data);

    void paint_opengl(int res_x, int res_y) override;

    static BaseDataView* create(const BaseDataType* data);

    static const inline DataViewTypeInfo Type { "Texture View", "Standard/Texture",
        &TextureData::Type, DataViewGraphicsApi::OpenGL, &create };

private:

    const TextureData* viewed_data;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
