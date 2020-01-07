#pragma once

#include <vector>

#include <QColor>
#include <QObject>

#include "model/parameter/BaseParameter.hpp"

class BaseOperator;
class DataInput;



struct DataTypeDescription
{
    QString name;
    QString library;
    QColor gui_color;
    bool use_opengl;
    // Description
    // Version
    // Author
    // License
    // Etc
};


inline bool operator==(const DataTypeDescription& t1, const DataTypeDescription& t2)
{
    return t1.name == t2.name && t1.library == t2.library;
}


class BaseDataType : public BaseZigZagObject
{
    Q_OBJECT

public:

    BaseDataType(BaseOperator* parent, const QString& name, const DataTypeDescription& description);

    virtual ~BaseDataType();


    // Should be overriden to acquire resources.
    // Never call this function yourself, this is done for you.
    virtual void acquireResources() { }


    // Should be overriden to release resources.
    // Never call this function yourself, this is done for you.
    virtual void releaseResources() { }


    bool isConnected() const;
    bool isConnectedTo(const DataInput* data_input) const;

    BaseOperator * getOperator() const;
    const std::vector<DataInput*>& getConnections() const;
    const DataTypeDescription * getDescription() const;

public slots:

    // Undoable action
    void connectTo(DataInput* data_input);

    // Undoable action
    void disconnectFrom(DataInput* data_input);

    // Undoable action
    void disconnectFromAll();


signals:

    void hasConnected(BaseDataType* output, DataInput* input);

    void hasDisconnected(BaseDataType* output, DataInput* input);


private:

    friend class ConnectCommand;
    friend class DisconnectCommand;


    // Non action version of connect_to
    bool addConnection(DataInput* data_input);

    // Non action version of connect_to
    bool removeConnection(DataInput* data_input);


    std::vector<DataInput*> m_connections;

    BaseOperator* m_parentOperator;

    const DataTypeDescription * m_description;


};
