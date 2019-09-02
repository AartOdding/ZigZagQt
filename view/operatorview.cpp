#include <QPainter>
#include <QFocusEvent>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>

#include "application.h"

#include "basedataview.h"
#include "operatorview.h"
#include "projectscopeview.h"
#include "datablockconnector.h"
#include "parameterconnector.h"

#include "model/datainput.h"
#include "model/projectmodel.h"
#include "model/baseoperator.h"
#include "model/basedatatype.h"


#include <iostream>


OperatorView::OperatorView(BaseOperator& op)
    : operator_model(op), name_tag("Test operator number x", this)
{
    setZValue(1);
    setPos(op.get_position_x(), op.get_position_y());

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    connect(&operator_model, &BaseOperator::position_changed, this, &OperatorView::on_operator_moved);

    auto h_width = width / 2.0;
    auto h_height = height / 2.0;

    name_tag.setPos(-h_width, -h_height - 33);

    selection_rect.setRect(0, 0, width + 50, height + 46);
    selection_rect.setPos(- h_width - 25, -h_height - 35);
    selection_rect.setPen(QPen(QBrush(QColor(51, 153, 255)), 2));
    selection_rect.setBrush(QColor(51, 153, 255, 30));
    selection_rect.setFlag(QGraphicsItem::ItemStacksBehindParent);

    inputs_panel.setFlag(ItemHasNoContents);
    outputs_panel.setFlag(ItemHasNoContents);
    inputs_panel.setGeometry(-h_width - 25, -h_height, 25, height);
    outputs_panel.setGeometry(h_width, -h_height, 25, height);
    inputs_panel.setLayout(new QGraphicsLinearLayout(Qt::Vertical));
    outputs_panel.setLayout(new QGraphicsLinearLayout(Qt::Vertical));
    inputs_panel.layout()->setContentsMargins(0, 0, 0, 0);
    outputs_panel.layout()->setContentsMargins(0, 0, 0, 0);
    static_cast<QGraphicsLinearLayout*>(inputs_panel.layout())->setSpacing(0);
    static_cast<QGraphicsLinearLayout*>(outputs_panel.layout())->setSpacing(0);

    // add parameter connector first.
    for (auto i : op.data_inputs())
    {
        auto connector = new DataBlockConnector(*this, *i);
        inputs[i] = connector;
        static_cast<QGraphicsLinearLayout*>(inputs_panel.layout())->addItem(connector);
    }
    for (auto o : op.data_outputs())
    {
        auto connector = new DataBlockConnector(*this, *o);
        outputs[o] = connector;
        static_cast<QGraphicsLinearLayout*>(outputs_panel.layout())->addItem(connector);
    }

    static_cast<QGraphicsLinearLayout*>(inputs_panel.layout())->addItem(new ParameterConnector(*this, true));
    static_cast<QGraphicsLinearLayout*>(outputs_panel.layout())->addItem(new ParameterConnector(*this, false));

    auto library = application::library_model();

    for (auto output : operator_model.data_outputs())
    {
        if (library->contains_view_for(*output->type()))
        {
            auto data_view_type = library->data_views().at(output->type());
            data_view = data_view_type->construct(output);
            data_view->set_bounds(-h_width + 7, -h_height + 7, width - 14, height - 14);
            data_view->setParentItem(this);
            return;
        }
    }
}


ProjectScopeView* OperatorView::scope_view()
{
    return dynamic_cast<ProjectScopeView*>(scene());
}


QRectF OperatorView::boundingRect() const
{
    return QRectF(-width / 2, -height / 2, width, height);
}


void OperatorView::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    selection_rect.setVisible(isSelected());

    painter->setRenderHint(QPainter::Antialiasing);
    auto brush = QBrush(QColor(55, 55, 55));
    auto pen = QPen(QBrush(QColor(255, 255, 255)), 2);

    painter->fillRect(-width / 2, -height / 2, width, height, brush);
    painter->setPen(pen);
    painter->drawRoundedRect(-width / 2 + 1, -height / 2 + 1, width -2, height -2, 4, 4);
}


DataBlockConnector* OperatorView::get_view_of(const DataInput* input)
{
    return inputs[input];
}


DataBlockConnector* OperatorView::get_view_of(const BaseDataType* output)
{
    return outputs[output];
}


void OperatorView::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    scope_view()->bring_to_front(this);
    QGraphicsItem::mousePressEvent(event);
}


void OperatorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        auto p = event->scenePos() - event->buttonDownPos(Qt::LeftButton);
        position_x = static_cast<int>(p.x());
        position_y = static_cast<int>(p.y());
        setPos(position_x, position_y);
        emit has_moved();
        was_dragged = true;
    }

    QGraphicsItem::mouseMoveEvent(event);
}


void OperatorView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (was_dragged)
    {
        operator_model.move_to(position_x, position_y);
        //model.move_operator_undoable(&operator_, position_x, position_y);
    }
    was_dragged = false;

    QGraphicsItem::mouseReleaseEvent(event);
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
    if (to_x != position_x || to_y != position_y)
    {
        position_x = to_x;
        position_y = to_y;
        setPos(position_x, position_y);
        emit has_moved();
    }
}
