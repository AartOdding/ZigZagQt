#include <QResizeEvent>
#include <QtOpenGL>

#include "ExecutionEngineWindow.hpp"

#include <iostream>


ExecutionEngineWindow::ExecutionEngineWindow()
    : QGLWidget()
{
    //setAttribute(Qt::WA_PaintOutsidePaintEvent);
    setAutoBufferSwap(false);
}


void ExecutionEngineWindow::resizeEvent(QResizeEvent *event)
{
    emit resized(event->size());
}


void ExecutionEngineWindow::paintEvent(QPaintEvent *event)
{
    std::cout << "paint event in execution widnow" << std::endl;
    // do nothing
}


QSize ExecutionEngineWindow::sizeHint() const
{
    return QSize(640, 480);
}
