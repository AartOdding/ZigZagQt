#pragma once

#include <QMap>
#include <QObject>
#include <QGraphicsScene>

#include "model/program/programmodel.h"


class BaseOperator;
class OperatorView;


class ProgramView : public QGraphicsScene
{
    Q_OBJECT

public:

    explicit ProgramView(QObject *parent = nullptr);

    void set_model(ProgramModel* program);


public slots:

    void on_operator_added(BaseOperator* operator_ptr);

    void on_operator_deleted(BaseOperator* operator_ptr);


protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void keyReleaseEvent(QKeyEvent *keyEvent) override;

private:

    ProgramModel* data_model;
    // need to have a separate scene for every scope, we can then switch scenes, when viewing different scopes
    // HashMap<Scope, Scene> scenes
    QMap<BaseOperator*, OperatorView*> operator_views;


signals:

    void redo_signal();

    void undo_signal();


};

