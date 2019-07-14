#pragma once

#include <QMap>
#include <QObject>
#include <QUndoStack>

#include "model/namemanager.h"
#include "model/operatorlibrary.h"



class BaseOperator;



class ProgramModel : public QObject
{
    Q_OBJECT

    friend class AddCommand;
    friend class RemoveCommand;
    friend class ConnectCommand;
    friend class DisconnectCommand;

public:

    ProgramModel(OperatorLibrary& operator_library);

    QList<BaseOperator*> get_entry_nodes();

    QList<BaseOperator*> get_all_nodes();

    NameManager name_manager;


public slots:

    void redo();

    void undo();


    void add_operator_undoable(const char* operator_class, int x, int y);

    void remove_operator_undoable(BaseOperator* operator_ptr);

    void move_operator_undoable(BaseOperator* operator_ptr, int x, int y);


    void connect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input);

    void disconnect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input);




signals:

    void operator_added(BaseOperator* operator_ptr);

    void operator_removed(BaseOperator* operator_ptr);



private:


    BaseOperator* create_operator(const char* operator_class, int x, int y);

    void add_operator(BaseOperator * operator_ptr);
    void remove_operator(BaseOperator * operator_ptr);


    void connect_operators(qint64 id_op_a, qint64 id_op_b, int op_b_input);
    void disconnect_operators(qint64 id_op_a, qint64 id_op_b, int op_b_input);

    QUndoStack undo_stack;

    OperatorLibrary& operator_library;
    QMap<qint64, BaseOperator*> operators;


};
