#pragma once

#include <QMap>
#include <QObject>
#include <QUndoStack>

#include "model/namemanager.h"
#include "model/operatorlibrary.h"



class BaseOperator;


// Implemented in main.cpp
ProgramModel * get_main_model();



class ProgramModel : public QObject
{
    Q_OBJECT

    friend class AddCommand;
    friend class RemoveCommand;

public:

    ProgramModel(OperatorLibrary& operator_library);

    QUndoStack* get_undo_stack();

    QList<BaseOperator*> get_entry_nodes();

    QList<BaseOperator*> get_all_nodes();


public slots:

    void redo();

    void undo();

    // Undoable action
    void add_operator(const char* operator_class, int x, int y);

    // Undoable action
    void remove_operator(BaseOperator* operator_ptr);


    //void move_operator_undoable(BaseOperator* operator_ptr, int x, int y);
    //void connect_data_undoable(BaseDataBlock* output, DataBlockInput* input);
    //void disconnect_data_undoable(BaseDataBlock* output, DataBlockInput* input);


signals:

    void operator_added(BaseOperator* operator_ptr);

    void operator_removed(BaseOperator* operator_ptr);



private:


    BaseOperator* create_operator(const char* operator_class, int x, int y);

    void add_operator_to_model(BaseOperator * operator_ptr);
    void remove_operator_from_model(BaseOperator * operator_ptr);


    QUndoStack undo_stack;

    OperatorLibrary& operator_library;
    QMap<qint64, BaseOperator*> operators;


};
