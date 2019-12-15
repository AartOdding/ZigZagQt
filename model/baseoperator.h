#pragma once

#include <QObject>

#include <vector>
#include <functional>

#include "model/parameter/intparameter.h"
#include "model/parameter/floatparameter.h"
#include "model/parameter/enumparameter.h"
#include "model/parameter/buttonparameter.h"


struct DataTypeInfo;
struct DataViewTypeInfo;
class BaseOperator;
class BaseDataType;
class DataInput;


struct OperatorDescription
{
    OperatorDescription() = delete;

    OperatorDescription(const std::string& name,
                        const std::string& package,
                        std::function<BaseOperator*()> construct,
                        const std::vector<const DataTypeInfo*>& inputs = {},
                        const std::vector<const DataTypeInfo*>& outputs = {},
                        const DataViewTypeInfo * view = nullptr);

    std::string name;
    std::string package;
    std::function<BaseOperator*()> construct;
    std::vector<const DataTypeInfo*> inputs;
    std::vector<const DataTypeInfo*> outputs;
    const DataViewTypeInfo * view;

    // USe OpenGL
    // Library
    // Image
    // Version
    // Description
    // Author
    // License
    // Etc
};


inline bool operator<(const OperatorDescription& t1, const OperatorDescription& t2)
{
    return t1.name < t2.name;
}



class BaseOperator : public BaseZigZagObject
{
    Q_OBJECT

    friend class MoveCommand;
    friend class ProjectModel;

public:

    BaseOperator(const OperatorDescription& type);

    virtual ~BaseOperator();

    virtual void prepare() { }
    virtual void run() = 0;

    int get_position_x() const;
    int get_position_y() const;

    void update_view();

    const OperatorDescription * type() const;


    const std::vector<DataInput*>& data_inputs() const;
    const std::vector<BaseDataType*>& data_outputs() const;

    std::vector<DataInput*> used_data_inputs() const;
    std::vector<BaseDataType*> used_data_outputs() const;

    int count_used_data_inputs() const;

    void register_data_input(DataInput* input);
    void register_data_output(BaseDataType* output);

    const std::vector<BaseComponent*>& importing_parameters() const;
    const std::vector<BaseComponent*>& exporting_parameters() const;

    virtual void set_from_xml(QXmlStreamReader& xml);
    virtual void write_to_xml(XmlSerializer& xml);

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

    void parameter_started_importing(BaseComponent* exporter, BaseComponent* importer);
    void parameter_stopped_importing(BaseComponent* exporter, BaseComponent* importer);


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

    std::vector<DataInput*> inputs;
    std::vector<BaseDataType*> outputs;

    std::vector<BaseComponent*> m_importing_parameters;
    std::vector<BaseComponent*> m_exporting_parameters;

    const OperatorDescription * type_info;

};
