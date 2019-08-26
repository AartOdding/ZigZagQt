#include "texturedataview.h"


bool TextureDataView::gpu_resources_initialized = false;
QOpenGLShaderProgram TextureDataView::shader;
GLuint TextureDataView::vao;
GLuint TextureDataView::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };




TextureDataView::TextureDataView(const BaseDataType* data)
    : viewed_data(dynamic_cast<const TextureData*>(data))
{

}


void TextureDataView::paint_opengl(int res_x, int res_y)
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/minimal.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/view_texture.frag");
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

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.programId());
    glBindVertexArray(vao);
    viewed_data->bind_as_texture(0);
    shader.setUniformValue(shader.uniformLocation("framebuffer_resolution"), QPointF(256, 256));
    shader.setUniformValue(shader.uniformLocation("color"), 0.5f, 0.0f, 0.3f);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
      std::cout << "oepngl error\n";
    }
}


BaseDataView* TextureDataView::create(const BaseDataType* data)
{
    return new TextureDataView(data);
}
