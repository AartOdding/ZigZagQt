#pragma once

#include <QAction>
#include <QHash>
#include <QObject>
#include <QPointer>
#include <QGraphicsScene>

#include <memory>
#include <mutex>

#include "ConnectionManager.hpp"
#include "model/OperatorNetwork.hpp"


class BaseOperator;
class BaseParameter;
class BaseDataType;
class DataInput;
class OperatorView;
class DataConnector;
class ParameterConnector;
class Cable;
class ParameterOwner;
class BaseComponent;



/*
 * TODO: add notes on multi threading
 *  - no calls towards model without locking operator
 */
class OperatorNetworkView : public QGraphicsScene,
                            public ConnectionManager
{
    Q_OBJECT

public:

    OperatorNetworkView(QObject *parent = nullptr);

    ~OperatorNetworkView();

    void setNetwork(OperatorNetwork* netwok);

    void bringToFront(OperatorView* op);

    /*
     * QGraphicsScene does not support actions out of the box.
     * Because of this it is easiest to query the actions, and just
     * add them to the Viewport.
     */
    QList<QAction*> getActions();


public slots:

    void selectAllOperators();

    void deleteSelectedOperators();


    void onOperatorAdded(QPointer<BaseOperator> operatorPtr, std::shared_ptr<std::mutex> mutex);

    void onOperatorRemoved(BaseOperator* operatorPtr);


    void onOperatorsConnected(BaseOperator* outputOperator, BaseDataType* outputData,
                              BaseOperator* inputOperator, DataInput* dataInput);

    void onOperatorsDisconnected(BaseOperator* outputOperator, BaseDataType* outputData,
                                 BaseOperator* inputOperator, DataInput* dataInput);

    void onParametersConnected(BaseOperator* exportingOperator, BaseComponent * exporter,
                               BaseOperator* importingOperator, BaseComponent * importer);

    void onParametersDisconnected(BaseOperator* exportingOperator, BaseComponent * exporter,
                                  BaseOperator* importingOperator, BaseComponent * importer);

protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


private:

    QAction m_deleteAction{ "Delete Selection", this };
    QAction m_selectAllAction{ "Select All", this };
    QAction m_undoAction{ "Undo", this };
    QAction m_redoAction{ "Redo", this };

    OperatorNetwork* m_network;

    struct ViewedOperator
    {
        QPointer<BaseOperator> operatorPtr;
        std::shared_ptr<std::mutex> mutex;
        OperatorView* operatorView = nullptr;
    };

    QHash<BaseOperator*, ViewedOperator*> m_operatorViews;

    // The data connector is the input connector.
    QHash<DataConnector*, Cable*> m_dataCables;

    // Stores a cable and a reference count, for each combination of operators
    QHash<std::pair<BaseOperator*, BaseOperator*>, std::pair<Cable*, int>> m_parameterCables;

};

