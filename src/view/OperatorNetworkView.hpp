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



class OperatorNetworkView : public QGraphicsScene,
                            public ConnectionManager
{
    Q_OBJECT

public:

    OperatorNetworkView(QObject *parent = nullptr);

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

    // TODO: look at alternatives
    void on_input_connected(BaseDataType* output, DataInput* input);
    void on_input_disconnected(BaseDataType* output, DataInput* input);

    // TODO: look at alternatives
    void on_parameters_connected(BaseComponent * exporter, BaseComponent * importer);
    void on_parameter_disconnected(BaseComponent * exporter, BaseComponent * importer);

protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


private:

    QAction m_deleteAction{ "Delete Selection", this };
    QAction m_selectAllAction{ "Select All", this };
    QAction m_undoAction{ "Undo", this };
    QAction m_redoAction{ "Redo", this };

    OperatorNetwork* m_network;

    QHash<BaseOperator*, OperatorView*> m_operatorViews;

    // TODO: look at alternatives
    QHash<DataConnector*, Cable*> m_dataCables;
    QHash<std::pair<ParameterConnector*, ParameterConnector*>, std::pair<Cable*, int>> m_parameterCables;

};

