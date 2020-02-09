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


OperatorNetworkView::~OperatorNetworkView()
{
    for (auto v : m_operatorViews)
    {
        delete v;
    }
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

    connect(m_network, &OperatorNetwork::operatorAdded,   this, &OperatorNetworkView::onOperatorAdded,   Qt::QueuedConnection);
    connect(m_network, &OperatorNetwork::operatorRemoved, this, &OperatorNetworkView::onOperatorRemoved, Qt::QueuedConnection);
}


void OperatorNetworkView::bringToFront(OperatorView* operatorView)
{
    for (auto& op : m_operatorViews)
    {
        if (op->operatorView != operatorView)
        {
            op->operatorView->setZValue(0.1);
        }
    }
    operatorView->setZValue(1);
}


void OperatorNetworkView::selectAllOperators()
{
    for (auto& op : m_operatorViews)
    {
        op->operatorView->setSelected(true);
    }
}


void OperatorNetworkView::deleteSelectedOperators()
{
    auto selected = selectedItems();
    QList<BaseOperator*> selectedOperators;
    selectedOperators.reserve(selected.size());

    for (auto item : selected)
    {
        auto operatorView = dynamic_cast<OperatorView*>(item);

        if (operatorView)
        {
            auto operatorModel = operatorView->getOperatorModel();

            selectedOperators.push_back(operatorModel);
        }
    }
    if (!selected.empty())
    {
        QMetaObject::invokeMethod(m_network, "removeOperators", Qt::QueuedConnection, Q_ARG(QList<BaseOperator*>, selectedOperators));
    }
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


void OperatorNetworkView::onOperatorAdded(QPointer<BaseOperator> operatorPtr, std::shared_ptr<std::mutex> operatorMutex)
{
    if (operatorMutex)
    {
        std::lock_guard<std::mutex> mutexLock(*operatorMutex);

        if (operatorPtr)
        {
            OperatorView* operatorView = new OperatorView(operatorPtr);
            ViewedOperator * viewedOperator = new ViewedOperator();
            viewedOperator->mutex = operatorMutex;
            viewedOperator->operatorPtr = operatorPtr;
            viewedOperator->operatorView = operatorView;

            m_operatorViews.insert(operatorPtr, viewedOperator);

            connect(operatorPtr, &BaseOperator::dataConnected, this, &OperatorNetworkView::onOperatorsConnected);
            connect(operatorPtr, &BaseOperator::dataDisconnected, this, &OperatorNetworkView::onOperatorsDisconnected);
            connect(operatorPtr, &BaseOperator::parameterConnected, this, &OperatorNetworkView::onParametersConnected);
            connect(operatorPtr, &BaseOperator::parameterDisconnected, this, &OperatorNetworkView::onParametersDisconnected);

            addItem(operatorView);
        }
    }
}


void OperatorNetworkView::onOperatorRemoved(BaseOperator* operatorPtr)
{
    if (m_operatorViews.contains(operatorPtr))
    {
        ViewedOperator* viewedOperator = m_operatorViews[operatorPtr];
        std::shared_ptr<std::mutex> mutex = viewedOperator->mutex;

        { // start new scope so mutex will only be destroyed after it is released.
            std::lock_guard<std::mutex> mutexLock(*mutex);

            removeItem(m_operatorViews[operatorPtr]->operatorView);
            delete m_operatorViews[operatorPtr]->operatorView;
            delete m_operatorViews[operatorPtr];
            m_operatorViews.remove(operatorPtr);
        }
    }
}


void OperatorNetworkView::onOperatorsConnected(BaseOperator* outputOperator, BaseDataType* outputData, BaseOperator* inputOperator, DataInput* dataInput)
{
    if (m_operatorViews.contains(outputOperator) && m_operatorViews.contains(inputOperator))
    {
        auto outputConnector = m_operatorViews[outputOperator]->operatorView->getDataOutput(outputData);
        auto inputConnector = m_operatorViews[inputOperator]->operatorView->getDataInput(dataInput);

        if (outputConnector && inputConnector)
        {
            auto cable = new Cable(this, outputConnector, inputConnector);
            m_dataCables.insert(inputConnector, cable);
            addItem(cable);
        }
    }
}


void OperatorNetworkView::onOperatorsDisconnected(BaseOperator* /*outputOperator*/, BaseDataType* /*outputData*/, BaseOperator* inputOperator, DataInput* dataInput)
{
    if (m_operatorViews.contains(inputOperator))
    {
        auto inputConnector = m_operatorViews[inputOperator]->operatorView->getDataInput(dataInput);

        if (inputConnector)
        {
            auto cable = m_dataCables[inputConnector];

            if (cable)
            {
                m_dataCables.remove(inputConnector);
                removeItem(cable);
                delete cable;
            }
        }
    }
}


void OperatorNetworkView::onParametersConnected(BaseOperator* exportingOperator, BaseComponent * /*exporter*/, BaseOperator* importingOperator, BaseComponent * /*importer*/)
{
    if (m_operatorViews.contains(exportingOperator) && m_operatorViews.contains(importingOperator))
    {
        auto exportConnector = m_operatorViews[exportingOperator]->operatorView->getParameterOutput();
        auto importConnector = m_operatorViews[importingOperator]->operatorView->getParameterInput();

        if (exportConnector && importConnector)
        {
            if (!m_parameterCables.contains( { exportingOperator, importingOperator } ))
            {
                auto cable = new Cable(this, exportConnector, importConnector);
                m_parameterCables.insert( { exportingOperator, importingOperator } , { cable, 1} );
                addItem(cable);
            }
            else
            {
                m_parameterCables[ { exportingOperator, importingOperator } ].second += 1;
            }
        }
    }
}


void OperatorNetworkView::onParametersDisconnected(BaseOperator* exportingOperator, BaseComponent * /*exporter*/, BaseOperator* importingOperator, BaseComponent * /*importer*/)
{
    if (m_operatorViews.contains(exportingOperator) && m_operatorViews.contains(importingOperator))
    {
        auto exportConnector = m_operatorViews[exportingOperator]->operatorView->getParameterOutput();
        auto importConnector = m_operatorViews[importingOperator]->operatorView->getParameterInput();

        if (exportConnector && importConnector)
        {
            auto cable = m_parameterCables.find( { exportingOperator, importingOperator } );

            if (cable != m_parameterCables.end())
            {
                cable->second -= 1;

                if (cable->second < 1)
                {
                    removeItem(cable->first);
                    delete cable->first;
                    m_parameterCables.erase(cable);
                }
            }
        }
    }
}
