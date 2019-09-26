#pragma once

#include <QObject>

#include <vector>
#include <functional>

#include "model/parameter/int64parameter.h"
#include "model/parameter/doubleparameter.h"
#include "model/parameter/enumparameter.h"
#include "model/parameter/buttonparameter.h"
#include "model/parameter/parameterowner.h"


struct DataTypeInfo;
struct DataViewTypeInfo;
class BaseOperator;
class BaseDataType;
class DataInput;


struct OperatorTypeInfo
{
    std::string name;
    std::string library;
    std::vector<const DataTypeInfo*> input_data_types;
    std::vector<const DataTypeInfo*> output_data_types;
    const DataViewTypeInfo * view_type;
    std::function<BaseOperator*()> construct;
    // USe OpenGL
    // Library
    // Image
    // Version
    // Description
    // Author
    // License
    // Etc
};


inline bool operator<(const OperatorTypeInfo& t1, const OperatorTypeInfo& t2)
{
    return t1.name < t2.name;
}



class BaseOperator : public QObject,
                     public ParameterOwner
{
    Q_OBJECT

    friend class MoveCommand;
    friend class ProjectModel;

public:

    BaseOperator(const OperatorTypeInfo& type);

    virtual ~BaseOperator();

    virtual void prepare() { }
    virtual void run() = 0;

    int get_position_x() const;
    int get_position_y() const;

    void update_view();

    const OperatorTypeInfo * type() const;


    const std::vector<DataInput*>& data_inputs() const;
    const std::vector<BaseDataType*>& data_outputs() const;

    std::vector<DataInput*> used_data_inputs() const;
    std::vector<BaseDataType*> used_data_outputs() const;

    int count_used_data_inputs() const;

    void register_data_input(DataInput* input);
    void register_data_output(BaseDataType* output);

    const std::vector<ParameterComponent*>& importing_parameters() const;
    const std::vector<ParameterComponent*>& exporting_parameters() const;


public slots:

    // Undoable action.
    void remove();

    // Undoable action.
    void move_to(int x, int y);


signals:

    void update_view_requested();

    void position_changed(int pos_x, int pos_y);

    void data_input_added(DataInput * new_data_input);
    void data_output_added(BaseDataType * new_data_output);

    void parameter_started_importing(ParameterComponent* exporter, ParameterComponent* importer);
    void parameter_stopped_importing(ParameterComponent* exporter, ParameterComponent* importer);


protected:

    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    // Direct version of move_to (non-undoable)
    void set_position(int pos_x, int pos_y);


    int position_x = 0;
    int position_y = 0;

    bool input_has_changed = false;

    std::vector<DataInput*> inputs;
    std::vector<BaseDataType*> outputs;

    std::vector<ParameterComponent*> m_importing_parameters;
    std::vector<ParameterComponent*> m_exporting_parameters;

    const OperatorTypeInfo * type_info;

};
