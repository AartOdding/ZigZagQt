#pragma once

#include "view/opengldataview.h"
#include "testdata.h"

#include <QOpenGLShaderProgram>


class TestDataView : public OpenGLDataView
{

public:

    TestDataView(const BaseDataType* data);

    void paint_opengl(int res_x, int res_y) override;

    static BaseDataView* create(const BaseDataType* data);

    static const inline DataViewTypeInfo Type { "Test View", "Standard/Test",
        &TestData::Type, DataViewGraphicsApi::OpenGL, &create };


private:

    const BaseDataType* viewed_data;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};



