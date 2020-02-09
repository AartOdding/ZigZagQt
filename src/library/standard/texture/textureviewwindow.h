#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include "utility/FrameRateMonitor.hpp"


class TextureView;

class TextureViewWindow : public QOpenGLWidget,
                          public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:

    TextureViewWindow(TextureView* belonging_view);

    ~TextureViewWindow() override;

    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int w, int h) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;


private:

    TextureView* belonging_view = nullptr;

    int width, height;

    bool is_fullscreen = false;

    bool vao_inited = false;
    GLuint vao;

    FrameRateMonitor fps{ std::chrono::milliseconds(500) };

};

