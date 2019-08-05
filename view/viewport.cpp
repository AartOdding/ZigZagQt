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

    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::set_view(ProjectScopeView* view_model /* , ProgramScope scope */)
{
    setScene(view_model);
}


void Viewport::zoom_in()
{
    current_zoom *= zoom_exponent;
    scale(zoom_exponent, zoom_exponent);
}


void Viewport::zoom_out()
{
    double exponent = 1.0 / zoom_exponent;

    if (current_zoom * exponent > zoom_limit)
    {
        current_zoom *= exponent;
        scale(exponent, exponent);
    }
}


void Viewport::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double inversion = zoom_inverted ? -1.0 : 1.0;

    if (inversion * event->delta() > 0)
    {
        zoom_in();
    }
    else
    {
        zoom_out();
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

    auto surface = qobject_cast<ProjectSurface*>(scene());

    if (surface && surface->is_making_connection())
    {
        surface->mouse_movement(mapToScene(event->pos()));
    }
}


void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);

    auto in = QKeySequence(Qt::CTRL + Qt::Key_Equal);


    if (!event->isAccepted())
    {
        if (event->modifiers() & Qt::ControlModifier
                && (event->key() == Qt::Key_Plus ||event->key() == Qt::Key_Equal))
        {
            setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            zoom_in();
        }
        else if (event->matches(QKeySequence::ZoomOut))
        {
            setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            zoom_out();
        }
        else if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_0)
        {
            setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            setTransform(QTransform());
            current_zoom = 1;
            centerOn(0, 0);  // TODO: center on avarage operator position;
        }
    }
}


void Viewport::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsView::keyReleaseEvent(event);

    if (!event->isAccepted())
    {

        std::cout << "view key rel\n";
    }
}
