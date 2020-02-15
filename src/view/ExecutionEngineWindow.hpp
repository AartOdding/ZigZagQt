#pragma once

#include <QGLWidget>


class ExecutionEngineWindow : public QGLWidget
{
    Q_OBJECT

public:

    ExecutionEngineWindow();

protected:

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *event);

    QSize sizeHint() const;

signals:

    void resized(QSize size);

};

