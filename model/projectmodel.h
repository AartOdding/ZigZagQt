#pragma once

#include <QMap>
#include <QObject>
#include <QUndoStack>

#include "model/librarymodel.h"


class ProjectModel;
class BaseOperator;



class ProjectModel : public QObject
{
    Q_OBJECT

    friend class AddCommand;
    friend class RemoveCommand;

public:

    ProjectModel(LibraryModel& operator_library);

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

    void add_operator_to_model(BaseOperator * operator_ptr);
    void remove_operator_from_model(BaseOperator * operator_ptr);


    QUndoStack undo_stack;

    LibraryModel& operator_library;
    QMap<qint64, BaseOperator*> operators;


};
