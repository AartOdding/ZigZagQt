#include <QPainter>
#include <QFocusEvent>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>

#include "application.h"

#include "basedataview.h"
#include "operatorview.h"
#include "projectscopeview.h"
#include "DataConnector.hpp"
#include "ParameterConnector.hpp"

#include "model/datainput.h"
#include "model/projectmodel.h"
#include "model/BaseOperator.hpp"
#include "model/BaseDataType.hpp"


#include <iostream>


OperatorView::OperatorView(BaseOperator& op)
    : operator_model(op), name_tag(op.description()->name, this)
{
    setZValue(1);
    m_posX = op.positionX();
    m_posY = op.positionY();
    setPos(m_posX - 0.5 * width, m_posY - 0.5 * height);
    resize(width, height);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    connect(&operator_model, &BaseOperator::position_changed, this, &OperatorView::on_operator_moved);

    name_tag.setPos(0, -33);

    selection_rect.setRect(0, 0, width + 50, height + 46);
    selection_rect.setPos(-25, -35);
    selection_rect.setPen(QPen(QBrush(QColor(51, 153, 255)), 2));
    selection_rect.setBrush(QColor(51, 153, 255, 30));
    selection_rect.setFlag(QGraphicsItem::ItemStacksBehindParent);

    inputs_panel.setFlag(ItemHasNoContents);
    outputs_panel.setFlag(ItemHasNoContents);
    inputs_panel.setGeometry(-25, 0, 25, height);
    outputs_panel.setGeometry(width, 0, 25, height);
    inputs_panel.setLayout(new QGraphicsLinearLayout(Qt::Vertical));
    outputs_panel.setLayout(new QGraphicsLinearLayout(Qt::Vertical));
    inputs_panel.layout()->setContentsMargins(0, 0, 0, 0);
    outputs_panel.layout()->setContentsMargins(0, 0, 0, 0);
    static_cast<QGraphicsLinearLayout*>(inputs_panel.layout())->setSpacing(0);
    static_cast<QGraphicsLinearLayout*>(outputs_panel.layout())->setSpacing(0);

    // add parameter connector first.
    for (auto i : op.dataInputs())
    {
        auto connector = new DataConnector(*this, *i);
        inputs[i] = connector;
        static_cast<QGraphicsLinearLayout*>(inputs_panel.layout())->addItem(connector);
    }
    for (auto o : op.dataOutputs())
    {
        auto connector = new DataConnector(*this, *o);
        outputs[o] = connector;
        static_cast<QGraphicsLinearLayout*>(outputs_panel.layout())->addItem(connector);
    }

    static_cast<QGraphicsLinearLayout*>(inputs_panel.layout())->addItem(new ParameterConnector(*this, true));
    static_cast<QGraphicsLinearLayout*>(outputs_panel.layout())->addItem(new ParameterConnector(*this, false));

    /*
    dataViews = operator_model.findChildren<BaseDataView*>(QString(), Qt::FindDirectChildrenOnly);

    if (dataViews.size() > 0)
    {
        for (auto view : dataViews)
        {
            view->setParentItem(this);
            view->set_bounds(7, 7, width - 14, height - 14);
        }
    }*/
}


OperatorView::~OperatorView()
{
    /*
    for (auto view : dataViews)
    {
        view->setParentItem(nullptr);
        scene()->removeItem(view);
    }*/
}


ProjectScopeView* OperatorView::scope_view()
{
    return dynamic_cast<ProjectScopeView*>(scene());
}


void OperatorView::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    selection_rect.setVisible(isSelected());

    painter->setRenderHint(QPainter::Antialiasing);
    auto brush = QBrush(QColor(55, 55, 55));
    auto pen = QPen(QBrush(QColor(255, 255, 255)), 2);

    painter->fillRect(0, 0, width, height, brush);
    painter->setPen(pen);
    painter->drawRoundedRect(1, 1, width - 2, height - 2, 4, 4);
}


DataConnector* OperatorView::data_connector_in(const DataInput* input)
{
    return inputs[input];
}


DataConnector* OperatorView::data_connector_out(const BaseDataType* output)
{
    return outputs[output];
}


ParameterConnector* OperatorView::parameter_connector_in() const
{
    return static_cast<ParameterConnector*>(inputs_panel.layout()->itemAt(inputs_panel.layout()->count() - 1));
}


ParameterConnector* OperatorView::parameter_connector_out() const
{
    return static_cast<ParameterConnector*>(outputs_panel.layout()->itemAt(outputs_panel.layout()->count() - 1));
}


void OperatorView::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    scope_view()->bring_to_front(this);
    QGraphicsWidget::mousePressEvent(event);
}


void OperatorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        auto p = event->scenePos() - event->buttonDownPos(Qt::LeftButton);
        m_posX = static_cast<int>(p.x());
        m_posY = static_cast<int>(p.y());
        setPos(m_posX, m_posY);
        emit has_moved();
        was_dragged = true;
    }

    QGraphicsWidget::mouseMoveEvent(event);
}


void OperatorView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (was_dragged)
    {
        operator_model.move_to(m_posX, m_posY);
    }
    was_dragged = false;

    QGraphicsWidget::mouseReleaseEvent(event);
}


void OperatorView::keyPressEvent(QKeyEvent *event)
{
    event->setAccepted(false);
}


void OperatorView::keyReleaseEvent(QKeyEvent *event)
{
    event->setAccepted(false);
}


void OperatorView::on_operator_moved(int to_x, int to_y)
{
    if (to_x != m_posX || to_y != m_posY)
    {
        m_posX = to_x;
        m_posY = to_y;
        setPos(m_posX - 0.5 * width, m_posY - 0.5 * height);
        emit has_moved();
    }
}
