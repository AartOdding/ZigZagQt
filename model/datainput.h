#pragma once

#include <QObject>

#include "model/parameter/baseparameter.h"
#include "basedatatype.h"

class BaseOperator;



class DataInput : public QObject,
                  public BaseParameter
{
    Q_OBJECT

public:

    DataInput(BaseOperator* parent_operator, const char * name, const DataTypeInfo& type_info);

    virtual ~DataInput();

    virtual bool compatible_with(const BaseDataType* data_block) const;

    bool is_connected() const;
    bool is_connected_to(const BaseDataType* data_block) const;
    const BaseDataType* get_connection() const;

    const DataTypeInfo * type() const;


public slots:

    // Undoable action
    void connect_to(BaseDataType* data_block);

    // Undoable action
    void disconnect();


signals:

    void has_connected(BaseDataType* output, DataInput* input);

    void has_disconnected(BaseDataType* output, DataInput* input);


private:

    friend class BaseOperator;
    friend class ConnectCommand;
    friend class DisconnectCommand;

    // Non action version of connect_to and disconnect_from
    bool set_connection(BaseDataType* data_block);

    BaseDataType* connection = nullptr;

    const DataTypeInfo * data_type;

};
