#pragma once

#include <QHash>
#include <QObject>
#include <QGraphicsScene>

#include "ConnectionManager.hpp"
#include "model/projectmodel.h"


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


class ProjectScopeView : public QGraphicsScene,
                         public ConnectionManager
{
    Q_OBJECT

public:

    ProjectScopeView(QObject *parent = nullptr);

    void set_model(ProjectModel* program);

    void bring_to_front(OperatorView* op);


public slots:

    void on_operator_added(BaseOperator* operator_ptr);
    void on_operator_deleted(BaseOperator* operator_ptr);

    void on_input_connected(BaseDataType* output, DataInput* input);
    void on_input_disconnected(BaseDataType* output, DataInput* input);

    void on_parameters_connected(BaseComponent * exporter, BaseComponent * importer);
    void on_parameter_disconnected(BaseComponent * exporter, BaseComponent * importer);


protected:

    void keyPressEvent(QKeyEvent *keyEvent) override;
    void keyReleaseEvent(QKeyEvent *keyEvent) override;


private:

    ProjectModel* data_model;
    // need to have a separate scene for every scope, we can then switch scenes, when viewing different scopes
    // HashMap<Scope, Scene> scenes
    QHash<BaseOperator*, OperatorView*> operator_views;

    // Key is the input connector // TODO: maybe use both connectors as key like in parameters
    QHash<DataConnector*, Cable*> data_cables;
    QHash<std::pair<ParameterConnector*, ParameterConnector*>, std::pair<Cable*, int>> parameter_cables;



signals:

    void redo_signal();

    void undo_signal();


};

