#pragma once

#include "view/opengldataview.h"
#include "testdata.h"

#include <QOpenGLShaderProgram>


class TestDataView : public OpenGLDataView
{

public:

    TestDataView(BaseOperator* parent_operator);

    void paint_opengl(int res_x, int res_y) override;

    static BaseDataView* create(BaseOperator* parent_operator);

    static const inline DataViewTypeInfo Type { "Test View", "Test", DataViewGraphicsApi::OpenGL, &create };


private:

    const BaseDataType* viewed_data;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};



