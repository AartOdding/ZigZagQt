#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QOpenGLWidget>

#include "view/projectscopeview.h"
#include "view/parameter/parametereditor.h"



class Viewport : public QGraphicsView
{
    Q_OBJECT

public:

    Viewport(QOpenGLWidget* gl, QWidget* parent = nullptr);

    void set_view(ProjectScopeView* view_model /* , ProgramScope scope */);

protected:

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;


public slots:

    void on_operator_requested(const OperatorTypeInfo* op_type, const QPointF& where);


private:

    void zoom_in();

    void zoom_out();

    double zoom_exponent = 1.2;
    bool zoom_inverted = false;

    double current_zoom = 1.0;
    double zoom_limit = 0.12;

    ProjectScopeView* view_model;

    ParameterEditor parameter_editor;

    //QOpenGLWidget gl_widget;

};
