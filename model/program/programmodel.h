#pragma once

#include <QMap>
#include <QObject>
#include <QUndoStack>

#include "model/namemanager.h"


class BaseOperator;



class ProgramModel : public QObject
{
    Q_OBJECT

    friend class AddCommand;
    friend class RemoveCommand;
    friend class MoveCommand;
    friend class ConnectCommand;
    friend class DisconnectCommand;

public:

    ProgramModel();

    QList<BaseOperator*> get_entry_nodes();

    QList<BaseOperator*> get_all_nodes();

    NameManager name_manager;


public slots:

    void redo();

    void undo();


    void add_operator_undoable(const QString& operator_class, int x, int y);

    void remove_operator_undoable(QPointer<BaseOperator> operator_);

    void move_operator_undoable(qint64 id, int x, int y);

    void connect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input);

    void disconnect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input);




signals:

    void operator_added(BaseOperator* pointer, qint64 id);

    // only use id not pointer, cause the actual operator will already be deleted
    void operator_deleted(qint64 id);



private:
    /*
     * These functions are all provided with id's instead of pointers, because they are meant for
     * usage by commands. Commands cannot store pointers, because a remove command could
     * potentially change memory addresses.
     */
    void add_operator(const QString& operator_class, int x, int y, qint64 id);
    void delete_operator(qint64 id);
    void move_operator(qint64 id, int to_x, int to_y);
    void connect_operators(qint64 id_op_a, qint64 id_op_b, int op_b_input);
    void disconnect_operators(qint64 id_op_a, qint64 id_op_b, int op_b_input);

    QUndoStack undo_stack;

    QMap<qint64, BaseOperator*> operators;


};
