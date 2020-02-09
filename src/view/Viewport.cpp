#include <QWheelEvent>
#include <QOpenGLWidget>

#include <cmath>

#include "Viewport.hpp"




Viewport::Viewport(QWidget* parent)
    : QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setRenderHint(QPainter::Antialiasing);

    viewport()->setCursor(Qt::ArrowCursor);

    m_zoomInAction.setAutoRepeat(false);
    m_zoomOutAction.setAutoRepeat(false);
    m_resetZoomAction.setAutoRepeat(false);

    m_zoomInAction.setShortcuts({ QKeySequence(Qt::CTRL | Qt::Key_Plus),
                                  QKeySequence(Qt::CTRL | Qt::Key_Equal) });
    m_zoomOutAction.setShortcuts({ QKeySequence(Qt::CTRL | Qt::Key_Minus),
                                   QKeySequence(Qt::CTRL | Qt::Key_Underscore) });
    m_resetZoomAction.setShortcuts({ QKeySequence(Qt::CTRL | Qt::Key_0),
                                     QKeySequence(Qt::CTRL | Qt::Key_BracketRight) });

    connect(&m_zoomInAction, &QAction::triggered, this, &Viewport::zoomIn);
    connect(&m_zoomOutAction, &QAction::triggered, this, &Viewport::zoomOut);
    connect(&m_resetZoomAction, &QAction::triggered, this, &Viewport::resetZoom);

    insertAction(nullptr, &m_zoomInAction);
    insertAction(nullptr, &m_zoomOutAction);
    insertAction(nullptr, &m_resetZoomAction);
}


void Viewport::zoomIn()
{
    double newZoomLevel = m_currentZoomLevel * m_zoomFactor;

    if (newZoomLevel >= m_zoomOutLimit && newZoomLevel <= m_zoomInLimit)
    {
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        scale(m_zoomFactor, m_zoomFactor);
        m_currentZoomLevel = newZoomLevel;
    }
}


void Viewport::zoomOut()
{
    double newZoomLevel = m_currentZoomLevel * (1.0 / m_zoomFactor);

    if (newZoomLevel >= m_zoomOutLimit && newZoomLevel <= m_zoomInLimit)
    {
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        scale((1.0 / m_zoomFactor), (1.0 / m_zoomFactor));
        m_currentZoomLevel = newZoomLevel;
    }
}


void Viewport::resetZoom()
{
    resetTransform();
    centerOn(0, 0);
    m_currentZoomLevel = 1;
}


void Viewport::zoomDegrees(int degrees)
{
    if (m_zoomInverted)
    {
        degrees *= -1;
    }
    double zoomFactor = std::pow(m_zoomFactorDegree, degrees);
    double newZoomLevel = m_currentZoomLevel * zoomFactor;

    if (newZoomLevel >= m_zoomOutLimit && newZoomLevel <= m_zoomInLimit)
    {
        if (m_zoomTowardsMouse)
        {
            setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        }
        else
        {
            setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        }
        scale(zoomFactor, zoomFactor);
        m_currentZoomLevel = newZoomLevel;
    }
}


void Viewport::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::wheelEvent(QWheelEvent *event)
{
    zoomDegrees(event->angleDelta().y() / 8);
}

