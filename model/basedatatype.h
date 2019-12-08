#pragma once

#include <vector>

#include <QColor>
#include <QObject>

#include "model/parameter/BaseParameter.hpp"

class BaseOperator;
class DataInput;



struct DataTypeInfo
{
    std::string name;
    std::string library;
    QColor gui_color;
    bool use_opengl;
    // Description
    // Version
    // Author
    // License
    // Etc
};


inline bool operator==(const DataTypeInfo& t1, const DataTypeInfo& t2)
{
    return t1.name == t2.name && t1.library == t2.library;
}


class BaseDataType : public QObject,
                     public BaseZigZagObject
{
    Q_OBJECT

public:

    BaseDataType(BaseOperator* parent_operator, const char * name, const DataTypeInfo& type_info);

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

    virtual void set_from_xml(QXmlStreamReader& xml);
    virtual void write_to_xml(XmlSerializer& xml);

    BaseOperator* get_operator() const;

public slots:

    // Undoable action
    void connect_to(DataInput* data_input);

    // Undoable action
    void disconnect_from(DataInput* data_input);

    // Undoable action
    void disconnect_all();


signals:

    void has_connected(BaseDataType* output, DataInput* input);

    void has_disconnected(BaseDataType* output, DataInput* input);


private:

    friend class ConnectCommand;
    friend class DisconnectCommand;


    // Non action version of connect_to
    bool add_connection(DataInput* data_input);

    // Non action version of connect_to
    bool remove_connection(DataInput* data_input);


    std::vector<DataInput*> connections;

    BaseOperator* m_parent_operator;

    const DataTypeInfo * data_type;


};
