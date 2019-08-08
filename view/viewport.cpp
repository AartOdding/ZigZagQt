#include "viewport.h"


#include <QWheelEvent>



Viewport::Viewport(QWidget* parent)
    : QGraphicsView(parent), parameter_editor(this)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);

    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::set_view(ProjectScopeView* view_mdl /* , ProgramScope scope */)
{
    view_model = view_mdl;
    setScene(view_model);
    parameter_editor.set_scene(view_model);

    //connect(view_model, &ProjectSurface::focus_operator_changed,
           // &parameter_editor, &ParameterEditor::on_focus_operator_changed);
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
    event->setAccepted(false);

    QGraphicsView::mousePressEvent(event);

    if (!event->isAccepted())
    {
        view_model->set_focus_operator(nullptr);
    }

    viewport()->setCursor(Qt::ArrowCursor);
}


void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);

    if (view_model && view_model->is_making_connection())
    {
        view_model->mouse_movement(mapToScene(event->pos()));
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
        else if (event->key() == Qt::Key_P)
        {
            parameter_editor.setVisible(!parameter_editor.isVisible());
        }
    }
}


void Viewport::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsView::keyReleaseEvent(event);
}


void Viewport::resizeEvent(QResizeEvent *event)
{
    parameter_editor.setGeometry(width() - 401, 1, 400, 400);
    QGraphicsView::resizeEvent(event);
}
