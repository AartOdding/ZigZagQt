#pragma once

#include <vector>
#include <functional>

#include <QObject>

#include "model/parameter/parameterowner.h"


struct DataTypeInfo;
class BaseOperator;
class BaseDataType;
class BaseParameter;
class DataInput;


struct OperatorTypeInfo
{
    std::string name;
    std::string library;
    std::vector<const DataTypeInfo*> input_data_types;
    std::vector<const DataTypeInfo*> output_data_types;
    bool use_opengl;
    std::function<BaseOperator*()> construct;
    // Library
    // Image
    // Version
    // Description
    // Author
    // License
    // Etc
};


class BaseOperator : public parameter::ParameterOwner
{
    Q_OBJECT

    friend class MoveCommand;
    friend class ProjectModel;

public:

    BaseOperator(const OperatorTypeInfo& type);

    virtual ~BaseOperator();

    virtual void run() = 0;


    int get_position_x() const;
    int get_position_y() const;

    const OperatorTypeInfo * type() const;


    const std::vector<DataInput*>& data_inputs() const;
    const std::vector<BaseDataType*>& data_outputs() const;

    std::vector<DataInput*> used_data_inputs() const;
    std::vector<BaseDataType*> used_data_outputs() const;

    int count_used_data_inputs() const;

    void register_data_input(DataInput* input);
    void register_data_output(BaseDataType* output);


public slots:

    // Undoable action.
    void remove();

    // Undoable action.
    void move_to(int x, int y);


signals:

    void position_changed(int pos_x, int pos_y);

    void data_input_added(DataInput * new_data_input);
    void data_output_added(BaseDataType * new_data_output);


protected:

    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }


private:

    // Direct version of move_to (non-undoable)
    void set_position(int pos_x, int pos_y);


    std::vector<DataInput*> inputs;
    std::vector<BaseDataType*> outputs;

    int position_x = 0;
    int position_y = 0;

    const OperatorTypeInfo * type_info;

};
