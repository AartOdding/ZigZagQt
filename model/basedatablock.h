#pragma once

#include <vector>

#include <QList>
#include <QObject>


class QString;
class BaseOperator;
class BaseParameter;
class DataBlockInput;



class BaseDataBlock : public QObject
{
    Q_OBJECT

public:

    BaseDataBlock(const char * data_type_name);

    virtual ~BaseDataBlock();


    BaseOperator* get_parent_operator();

    const BaseOperator* get_parent_operator() const;


    // This method needs to be overriden by the inheriting class, so that the GUI
    // can query how many parameters to add to the operator.
    virtual std::vector<BaseParameter*> get_parameters() = 0;


    // Causes get_paramers() to be called again, to reevaluate what parameters appear
    // in the GUI. Call this function after adding or removing a parameter.
    void refresh_parameters();



    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }



    bool is_connected() const;

    bool is_connected_to(const DataBlockInput* data_input) const;

    std::vector<const DataBlockInput*> get_connections() const;


    const char * const type_name;


public slots:

    // Undoable action
    void connect_to(DataBlockInput* data_input);

    // Undoable action
    void disconnect_from(DataBlockInput* data_input);

    // Undoable action
    void disconnect_all();


signals:

    void parameters_modified();

    void connected_to(DataBlockInput* data_block);

    void disconnected_from(DataBlockInput* data_block);


private:

    friend class BaseOperator;
    friend class ConnectCommand;
    friend class DisconnectCommand;

    void set_parent_operator(BaseOperator* op);


    // Non action version of connect_to
    bool add_connection(DataBlockInput* data_input);

    // Non action version of connect_to
    bool remove_connection(DataBlockInput* data_input);


    BaseOperator* parent_operator;

    std::vector<DataBlockInput*> connections;


};
