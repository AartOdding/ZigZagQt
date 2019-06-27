#pragma once

#include <QMap>
#include <QObject>
#include <QGraphicsScene>

#include "programmodel.h"


class BaseTOP;
class OperatorView;


class ProgramView : public QGraphicsScene
{
    Q_OBJECT

public:

    explicit ProgramView(QObject *parent = nullptr);

    void set_model(ProgramModel* program);


public slots:

    void on_operator_added(BaseTOP* pointer, qint64 id);

    void on_operator_deleted(qint64 id);


protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void keyReleaseEvent(QKeyEvent *keyEvent) override;

private:

    ProgramModel* data_model;
    // need to have a separate scene for every scope, we can then switch scenes, when viewing different scopes
    // HashMap<Scope, Scene> scenes
    QMap<qint64, OperatorView*> operator_views;


signals:

    void redo_signal();

    void undo_signal();


};

