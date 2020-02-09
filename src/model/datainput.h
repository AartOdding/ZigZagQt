#pragma once

#include <QObject>

#include "model/BaseZigZagObject.hpp"
#include "BaseDataType.hpp"

class BaseOperator;



class DataInput : public BaseZigZagObject
{
    Q_OBJECT

public:

    DataInput(BaseOperator* parent_operator, const QString& name, const DataTypeDescription& type_info);

    virtual ~DataInput();

    virtual bool compatible_with(const BaseDataType* data) const;

    bool is_connected() const;
    bool is_connected_to(const BaseDataType* data_block) const;
    const BaseDataType* get_connection() const;

    const DataTypeDescription * type() const;


    BaseOperator* get_operator() const;

public slots:

    // Undoable action
    void connect_to(BaseDataType* data_block);

    // Undoable action
    void disconnect();


private:

    friend class BaseOperator;
    friend class ConnectCommand;
    friend class DisconnectCommand;

    // Non action version of connect_to and disconnect_from
    bool set_connection(BaseDataType* data_block);

    BaseDataType* connection = nullptr;

    BaseOperator* m_parent_operator;

    const DataTypeDescription * data_type;

};
