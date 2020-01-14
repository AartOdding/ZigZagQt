#include <QMoveEvent>
#include <QWheelEvent>

#include <iostream>
#include <cmath>

#include "application.h"
#include "model/BaseOperator.hpp"
#include "model/projectmodel.h"
#include "projectscopeview.h"
#include "operatorselectordialog.h"
#include "viewport.h"





Viewport::Viewport(QOpenGLWidget* gl, QWidget* parent)
    : QGraphicsView(parent),
      parameter_editor(this)
{
    //setViewport(&gl_widget);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setViewport(gl);
    setRenderHint(QPainter::Antialiasing);

    parameter_editor.move(width() - 260, 100);
    parameter_editor.resize(250, 300);

    parameter_editor.move(width() - 560, 400);
    parameter_editor.resize(250, 300);

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


void Viewport::set_view(ProjectScopeView* view_mdl /* , ProgramScope scope */)
{
    view_model = view_mdl;
    setScene(view_model);
    parameter_editor.setScene(view_model);

    //connect(view_model, &ProjectSurface::focus_operator_changed,
           // &parameter_editor, &ParameterEditor::on_focus_operator_changed);
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


void Viewport::wheelEvent(QWheelEvent *event)
{
    zoomDegrees(event->angleDelta().y() / 8);
}


void Viewport::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
    auto dialog = new OperatorSelectorDialog{ this, mapToScene(event->pos()) };
    auto x = event->screenPos().x() - dialog->size().width() / 2;
    auto y = event->screenPos().y() - 100;
    dialog->move(x, y);
    connect(dialog, &OperatorSelectorDialog::operator_requested, this, &Viewport::on_operator_requested);
    dialog->show();
}



void Viewport::on_operator_requested(const OperatorDescription* op_type, const QPointF& where)
{
    std::cout << "succes: " << op_type->name.toStdString() << "\n";
    std::cout << application::project_model() << "\n";
    application::project_model()->add_operator(*op_type, where.x(), where.y());
}


void Viewport::mousePressEvent(QMouseEvent *event)
{
    event->setAccepted(false);

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


void Viewport::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}


void Viewport::moveEvent(QMoveEvent* event)
{
    auto movement = event->pos() - event->oldPos();
    parameter_editor.move(parameter_editor.pos() + movement);
}
