#pragma once

#include <vector>

#include <QColor>
#include <QObject>

#include "model/parameter/parameterowner.h"

class BaseOperator;
class BaseParameter;
class DataInput;



struct DataTypeInfo
{
    std::string name;
    QColor gui_color;
    // Description
    // Version
    // Author
    // License
    // Etc
};



class BaseDataType : public ParameterOwner
{
    Q_OBJECT

public:

    BaseDataType(BaseOperator* parent_operator, const DataTypeInfo& type_info);

    virtual ~BaseDataType();


    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }


    bool is_connected() const;

    bool is_connected_to(const DataInput* data_input) const;


    const std::vector<DataInput*>& get_connections() const;


    const DataTypeInfo * type() const;


    BaseOperator* const parent_operator;


public slots:

    // Undoable action
    void connect_to(DataInput* data_input);

    // Undoable action
    void disconnect_from(DataInput* data_input);

    // Undoable action
    void disconnect_all();


signals:

    void connected_to(DataInput* data_block);

    void disconnected_from(DataInput* data_block);


private:

    friend class ConnectCommand;
    friend class DisconnectCommand;


    // Non action version of connect_to
    bool add_connection(DataInput* data_input);

    // Non action version of connect_to
    bool remove_connection(DataInput* data_input);


    const DataTypeInfo * type_info;

    std::vector<DataInput*> connections;


};
