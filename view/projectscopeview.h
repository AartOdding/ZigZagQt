#pragma once

#include <QHash>
#include <QObject>
#include <QGraphicsScene>

#include "connectionmanager.h"
#include "model/projectmodel.h"


class BaseOperator;
class BaseDataType;
class DataInput;
class OperatorView;
class DataBlockConnector;
class DataBlockCable;



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


protected:

    void mousePressEvent(QGraphicsSceneMouseEvent  *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *mouseEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void keyPressEvent(QKeyEvent *keyEvent) override;
    void keyReleaseEvent(QKeyEvent *keyEvent) override;


private:

    ProjectModel* data_model;
    // need to have a separate scene for every scope, we can then switch scenes, when viewing different scopes
    // HashMap<Scope, Scene> scenes
    QHash<BaseOperator*, OperatorView*> operator_views;

    QHash<DataBlockConnector*, DataBlockCable*> cable_views;


signals:

    void redo_signal();

    void undo_signal();


};

