#pragma once

#include <QAction>
#include <QGraphicsView>


class QOpenGLWidget;
class OperatorNetworkView;



class Viewport : public QGraphicsView
{
    Q_OBJECT

public:

    Viewport(QWidget* parent = nullptr);

    QWindow* getWindow();

protected:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void zoomDegrees(int degrees);

private:

    QAction m_zoomInAction{ "Zoom In", this };
    QAction m_zoomOutAction{ "Zoom Out", this };
    QAction m_resetZoomAction{ "Reset Zoom", this };

    double m_currentZoomLevel = 1.0;

    // Behaviour configuration:
    double m_zoomFactor = 1.2;
    double m_zoomFactorDegree = 1.012;

    double m_zoomInLimit = 10.0;
    double m_zoomOutLimit = 0.10;

    bool m_zoomInverted = false;
    bool m_zoomTowardsMouse = true;

};
