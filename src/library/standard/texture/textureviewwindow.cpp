#include "textureviewwindow.h"
#include "textureview.h"

#include <QOpenGLContext>


#include <iostream>



TextureViewWindow::TextureViewWindow(TextureView* view)
    : belonging_view(view)
{
    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    initializeOpenGLFunctions();
}


TextureViewWindow::~TextureViewWindow()
{
}


void TextureViewWindow::initializeGL()
{
    std::cout << context()->shareGroup()->shares().size();

    if (!vao_inited)
    {
        vao_inited = true;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, TextureView::vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
    }
}


void TextureViewWindow::paintGL()
{

    if (belonging_view)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(belonging_view->shader.programId());
        glBindVertexArray(vao);
        belonging_view->m_viewedTexture->bindTexture(0);
        belonging_view->shader.setUniformValue(belonging_view->shader.uniformLocation("framebuffer_resolution"), QPointF(256, 256));
        belonging_view->shader.setUniformValue(belonging_view->shader.uniformLocation("color"), 0.5f, 0.0f, 0.3f);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glUseProgram(0);

        glFlush();

        fps.frame();

        if (fps.frame_count() % 500 == 0)
        {
            std::cout << fps.fps() << " fps in texture view window.\n";
        }
    }
}

void TextureViewWindow::resizeGL(int w, int h)
{
    std::cout << "resized window " << w << ", " << h << "\n";
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}


void TextureViewWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    if (is_fullscreen)
    {
        setWindowState(Qt::WindowNoState);
    }
    else
    {
        setWindowState(Qt::WindowFullScreen);
    }
    is_fullscreen = !is_fullscreen;
}

