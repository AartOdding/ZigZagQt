#include "OperatorNetworkView.hpp"
#include "application.h"

#include "view/BaseConnector.hpp"
#include "view/operatorview.h"
#include "view/cable.h"
#include "view/DataConnector.hpp"
#include "view/ParameterConnector.hpp"
#include "model/BaseOperator.hpp"
#include "model/datainput.h"
#include "model/parameter/BaseComponent.hpp"
#include "view/OperatorSelectorDialog.hpp"

#include <QMetaObject>
#include <QPointer>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include <iostream>

OperatorNetworkView::OperatorNetworkView(QObject *parent)
    : QGraphicsScene(-20000, -20000, 40000, 40000)
{
    setBackgroundBrush(QBrush(QColor(55, 55, 55)));

    m_deleteAction.setAutoRepeat(false);
    m_selectAllAction.setAutoRepeat(false);
    m_undoAction.setAutoRepeat(false);
    m_redoAction.setAutoRepeat(false);

    m_deleteAction.setShortcuts(   { QKeySequence(Qt::Key_Delete),
                                     QKeySequence(Qt::Key_Backspace)                });
    m_selectAllAction.setShortcuts({ QKeySequence(Qt::Key_A | Qt::CTRL)             });
    m_undoAction.setShortcuts(     { QKeySequence(Qt::Key_Z | Qt::CTRL)             });
    m_redoAction.setShortcuts(     { QKeySequence(Qt::Key_Y | Qt::CTRL),
                                     QKeySequence(Qt::Key_Z | Qt::CTRL | Qt::SHIFT) });
}


QList<QAction*> OperatorNetworkView::getActions()
{
    return
    {
        &m_deleteAction,
        &m_selectAllAction,
        &m_undoAction,
        &m_redoAction
    };
}


void OperatorNetworkView::setNetwork(OperatorNetwork *model)
{
    m_network = model;

    connect(&m_redoAction,      SIGNAL(triggered()), m_network, SLOT(redo()),                    Qt::QueuedConnection);
    connect(&m_undoAction,      SIGNAL(triggered()), m_network, SLOT(undo()),                    Qt::QueuedConnection);
    connect(&m_selectAllAction, SIGNAL(triggered()), this,      SLOT(selectAllOperators()),      Qt::DirectConnection);
    connect(&m_deleteAction,    SIGNAL(triggered()), this,      SLOT(deleteSelectedOperators()), Qt::DirectConnection);

    connect(m_network, &OperatorNetwork::operatorAdded, this, &OperatorNetworkView::onOperatorAdded, Qt::QueuedConnection);
}


void OperatorNetworkView::selectAllOperators()
{
    for (auto op : m_operatorViews)
    {
        op->setSelected(true);
    }
}


void OperatorNetworkView::deleteSelectedOperators()
{
    std::cout << "delete" <<std::endl;
    auto selected = selectedItems();
    QList<BaseOperator*> selectedOperators;
    selectedOperators.reserve(selected.size());

    for (auto item : selected)
    {
        auto operatorView = dynamic_cast<OperatorView*>(item);
        auto operatorModel = &operatorView->operator_model;

        if (operatorModel)
        {
            selectedOperators.push_back(operatorModel);
        }

        if (operatorView && operatorModel && m_operatorViews.contains(operatorModel))
        {
            for (auto input : operatorModel->dataInputs())
            {
                if (input)
                {
                    disconnect(input, &DataInput::has_connected, this, &OperatorNetworkView::on_input_connected);
                    disconnect(input, &DataInput::has_disconnected, this, &OperatorNetworkView::on_input_disconnected);
                }
            }
            disconnect(operatorModel, &BaseOperator::parameter_started_importing, this, &OperatorNetworkView::on_parameters_connected);
            disconnect(operatorModel, &BaseOperator::parameter_stopped_importing, this, &OperatorNetworkView::on_parameter_disconnected);

            m_operatorViews.remove(operatorModel);
            removeItem(operatorView);
            delete operatorView;
        }
    }
    QMetaObject::invokeMethod(m_network, "removeOperators", Qt::QueuedConnection, Q_ARG(QList<BaseOperator*>, selectedOperators));
}


void OperatorNetworkView::bringToFront(OperatorView* op)
{
    for (auto o : m_operatorViews)
    {
        if (o != op)
        {
            o->setZValue(0.1);
        }
    }
    op->setZValue(1);
}


void OperatorNetworkView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto dialog = new OperatorSelectorDialog(nullptr, event->scenePos().x(), event->scenePos().y());

    connect(dialog, SIGNAL(operatorRequested(const OperatorDescription*, int, int)), m_network, SLOT(addOperator(const OperatorDescription*, int, int)), Qt::QueuedConnection);

    auto x = event->screenPos().x() - dialog->size().width() / 2;
    auto y = event->screenPos().y() - 100;
    auto screen = QGuiApplication::screenAt(event->screenPos());

    if (screen)
    {
        // make sure always fits in screen
    }
    dialog->move(x, y);
    dialog->show();
}


void OperatorNetworkView::onOperatorAdded(QPointer<BaseOperator> operatorPtr, std::shared_ptr<std::mutex> mutex)
{
    if (mutex)
    {
        std::lock_guard<std::mutex> lock(*mutex);


    }
    OperatorView* op_view = new OperatorView(*operator_ptr);
    m_operatorViews.insert(operator_ptr, op_view);

    for (auto i : operator_ptr->dataInputs())
    {
        if (i)
        {
            connect(i, &DataInput::has_connected, this, &OperatorNetworkView::on_input_connected);
            connect(i, &DataInput::has_disconnected, this, &OperatorNetworkView::on_input_disconnected);
        }
    }
    connect(operator_ptr, &BaseOperator::parameter_started_importing, this, &OperatorNetworkView::on_parameters_connected);
    connect(operator_ptr, &BaseOperator::parameter_stopped_importing, this, &OperatorNetworkView::on_parameter_disconnected);

    addItem(op_view);
}


void OperatorNetworkView::on_input_connected(BaseDataType* output, DataInput* input)
{
    auto input_op = m_operatorViews[input->get_operator()];
    auto output_op = m_operatorViews[output->getOperator()];

    if (input_op && output_op)
    {
        auto input_view = input_op->data_connector_in(input);
        auto output_view = output_op->data_connector_out(output);

        if (input_view && output_view)
        {
            auto cable = new Cable(this, output_view, input_view);
            m_dataCables.insert(input_view, cable);
            addItem(cable);
        }
    }
}


void OperatorNetworkView::on_input_disconnected(BaseDataType* output, DataInput* input)
{
    auto input_op = m_operatorViews[input->get_operator()];

    if (input_op)
    {
        auto input_view = input_op->data_connector_in(input);

        if (input_view)
        {
            auto cable = m_dataCables[input_view];
            m_dataCables.remove(input_view);
            removeItem(cable);
            delete cable;
        }
    }
}


void OperatorNetworkView::on_parameters_connected(BaseComponent * exporter, BaseComponent * importer)
{
    OperatorView* export_op = m_operatorViews[exporter->getParameter()->findParent<BaseOperator*>()];
    OperatorView* import_op = m_operatorViews[importer->getParameter()->findParent<BaseOperator*>()];

    if (export_op && import_op)
    {
        auto export_connector = export_op->parameter_connector_out();
        auto import_connector = import_op->parameter_connector_in();

        if (export_connector && import_connector)
        {
            if (!m_parameterCables.contains({ export_connector, import_connector }))
            {
                auto cable = new Cable(this, export_connector, import_connector);
                m_parameterCables.insert({ export_connector, import_connector }, { cable, 1} );
                addItem(cable);
            }
            else
            {
                m_parameterCables[{export_connector, import_connector}].second += 1;
            }
        }
    }
}


void OperatorNetworkView::on_parameter_disconnected(BaseComponent * exporter, BaseComponent * importer)
{
    OperatorView* export_op = m_operatorViews[exporter->getParameter()->findParent<BaseOperator*>()];
    OperatorView* import_op = m_operatorViews[importer->getParameter()->findParent<BaseOperator*>()];

    if (export_op && import_op)
    {
        auto export_connector = export_op->parameter_connector_out();
        auto import_connector = import_op->parameter_connector_in();

        if (export_connector && import_connector)
        {
            auto key = std::pair(export_connector, import_connector);
            Q_ASSERT(m_parameterCables.contains(key));

            m_parameterCables[key].second -= 1;
            if (m_parameterCables[key].second < 1)
            {
                removeItem(m_parameterCables[key].first);
                delete m_parameterCables[key].first;
                m_parameterCables.remove(key);
            }
        }
    }
}
