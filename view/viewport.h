#pragma once

#include <QAction>
#include <QGraphicsView>

#include "view/parameter/parametereditor.h"


class QOpenGLWidget;
class ProjectScopeView;
struct OperatorDescription;


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

    void wheelEvent(QWheelEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent* event) override;

public slots:

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void zoomDegrees(int degrees);

    void on_operator_requested(const OperatorDescription* op_type, const QPointF& where);


private:

    /* actions */

    QAction m_zoomInAction{ "Zoom In", this };
    QAction m_zoomOutAction{ "Zoom Out", this };
    QAction m_resetZoomAction{ "Reset Zoom", this };

    /* configuration */

    bool m_zoomInverted = false;
    bool m_zoomTowardsMouse = true;

    double m_zoomFactor = 1.2;
    double m_zoomFactorDegree = 1.012;

    double m_zoomInLimit = 10.0;
    double m_zoomOutLimit = 0.10;

    /* member variables */

    ProjectScopeView* view_model;

    ParameterEditor parameter_editor;

    double m_currentZoomLevel = 1.0;

};
