#include "testdataview.h"

bool TestDataView::gpu_resources_initialized = false;
QOpenGLShaderProgram TestDataView::shader;
GLuint TestDataView::vao;
GLuint TestDataView::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };



TestDataView::TestDataView(const BaseDataType* data)
    : viewed_data(data)
{

}


void TestDataView::paint_opengl(int res_x, int res_y)
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/minimal.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/test_pattern.frag");
        auto success = shader.link();
        Q_ASSERT(success);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        //unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    //std::cout << QOpenGLContext::currentContext() << "test init context\n";

    glUseProgram(shader.programId());
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    //auto vertex_location = shader.attributeLocation("vertex");
    //shader.enableAttributeArray(vertex_location);
   // shader.setAttributeArray(vertex_location, vertices, 2);




    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


BaseDataView* TestDataView::create(const BaseDataType* data)
{
    return new TestDataView(data);
}
