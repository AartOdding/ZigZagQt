#include "viewport.h"

#include <iostream>

#include <QWheelEvent>



Viewport::Viewport(QWidget* parent)
    : QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
}


void Viewport::set_view(ProgramView* view_model /* , ProgramScope scope */)
{
    setScene(view_model);
}


void Viewport::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double inversion = zoom_inverted ? -1.0 : 1.0;
    bool zoom_in = inversion * event->delta() > 0;
    double zoom_multiplier = zoom_in ? zoom_exponent : 1.0 / zoom_exponent;

    if (current_zoom * zoom_multiplier > zoom_limit)
    {
        current_zoom *= zoom_multiplier;
        scale(zoom_multiplier, zoom_multiplier);
    }

    std::cout << current_zoom << "\n";
}


void Viewport::enterEvent(QEvent *event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
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
