#pragma once

#include <QMap>
#include <QObject>
#include <QUndoStack>

#include "model/operatorlibrary.h"


class ProjectModel;
class BaseOperator;



class ProjectModel : public QObject
{
    Q_OBJECT

    friend class AddCommand;
    friend class RemoveCommand;

public:

    ProjectModel();

    QUndoStack* get_undo_stack();

    const std::vector<BaseOperator*>& all_operators() const;


public slots:

    void redo();

    void undo();

    // Undoable action
    void add_operator(const OperatorDescription& op_type, int x, int y);

    // Undoable action
    void remove_operator(BaseOperator* operator_ptr);


    void save_to_file(const QString& path);

    void load_from_file(const QString& path);


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

    std::vector<BaseOperator*> operators;


};
