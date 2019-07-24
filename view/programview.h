#pragma once

#include <QHash>
#include <QObject>
#include <QGraphicsScene>

#include "model/programmodel.h"


class BaseOperator;
class DataBlockInput;
class OperatorView;
class DataConnectorView;
class DataCableView;




class ProgramView : public QGraphicsScene
{
    Q_OBJECT

public:

    explicit ProgramView(QObject *parent = nullptr);

    void set_model(ProgramModel* program);

    void bring_to_front(OperatorView* op);


public slots:

    void on_operator_added(BaseOperator* operator_ptr);

    void on_operator_deleted(BaseOperator* operator_ptr);


    void on_input_connected(BaseDataBlock* output, DataBlockInput* input);

    void on_input_disconnected(BaseDataBlock* output, DataBlockInput* input);


protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void keyPressEvent(QKeyEvent *keyEvent) override;

    void keyReleaseEvent(QKeyEvent *keyEvent) override;


private:

    ProgramModel* data_model;
    // need to have a separate scene for every scope, we can then switch scenes, when viewing different scopes
    // HashMap<Scope, Scene> scenes
    QHash<BaseOperator*, OperatorView*> operator_views;

    QHash<DataConnectorView*, DataCableView*> cable_views;


signals:

    void redo_signal();

    void undo_signal();


};

