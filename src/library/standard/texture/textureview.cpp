#include "textureview.h"
#include "library/standard/texture/texturedata.h"
#include "model/BaseOperator.hpp"

#include <iostream>


bool TextureView::gpu_resources_initialized = false;
QOpenGLShaderProgram TextureView::shader;
GLuint TextureView::vao;
GLuint TextureView::vbo;


// Draws the whole screen with GL_TRIANGLE_STRIP
static GLfloat const vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };




TextureView::TextureView(BaseOperator* parentOperator, TextureData* viewedTexture)
    : OpenGLDataView(parentOperator, &Type),
      m_parentOperator(parentOperator),
      m_viewedTexture(viewedTexture)
{
    if (parentOperator && viewedTexture)
    {
        connect(parentOperator, &BaseOperator::update_view_requested, this, &TextureView::update_view);
    }
}


TextureView::~TextureView()
{
    if (window)
    {
        delete window.data();
    }
}


void TextureView::paint_opengl(int res_x, int res_y)
{
    if (!gpu_resources_initialized)
    {
        gpu_resources_initialized = true;
        shader.create();
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/vert/minimal.vert");
        shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/frag/view_texture.frag");
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

    if (m_viewedTexture)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader.programId());
        glBindVertexArray(vao);
        m_viewedTexture->bindTexture(0);
        shader.setUniformValue(shader.uniformLocation("framebuffer_resolution"), QPointF(256, 256));
        shader.setUniformValue(shader.uniformLocation("color"), 0.5f, 0.0f, 0.3f);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glUseProgram(0);
    }

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
      std::cout << "opengl error\t" << err << "\n";
    }
}


void TextureView::update_view()
{
    update();
}


void TextureView::parameterChangedEvent(const BaseParameter* parameter)
{
    if (parameter == &open_window_button)
    {
        if (!window)
        {
            window = new TextureViewWindow(this);
            window->setAttribute(Qt::WA_DeleteOnClose, true);
            connect(m_parentOperator, &BaseOperator::update_view_requested, window.data(), qOverload<>(&QOpenGLWidget::update), Qt::QueuedConnection);
            window->show();
        }
    }
}


BaseDataView* TextureView::create(BaseOperator* parent_operator)
{
    return new TextureView(parent_operator, nullptr);
}
