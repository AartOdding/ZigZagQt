#pragma once

#include <QObject>


#include "model/basedatablock.h"

class BaseOperator;
class BaseParameter;
class BaseDataBlock;



class DataBlockInput : public QObject
{
    Q_OBJECT

public:

    DataBlockInput(const char * data_block_type);

    virtual ~DataBlockInput();


    // This method needs to be overriden by the inheriting class, so that the GUI
    // can query how many parameters to add to the operator.
    virtual std::vector<BaseParameter*> get_parameters();


    // Causes get_paramers() to be called again, to reevaluate what parameters appear
    // in the GUI. Call this function after adding or removing a parameter.
    void refresh_parameters();


    BaseOperator* get_parent_operator();

    const BaseOperator* get_parent_operator() const;



    virtual bool compatible_with(const BaseDataBlock* data_block) const;


    bool is_connected() const;

    bool is_connected_to(const BaseDataBlock* data_block) const;

    const BaseDataBlock* get_connection() const;


    const char * const type_name;


public slots:

    // Undoable action
    void connect_to(BaseDataBlock* data_block);

    // Undoable action
    void disconnect();


signals:

    void parameters_modified();

    void has_connected(BaseDataBlock* output, DataBlockInput* input);

    void has_disconnected(BaseDataBlock* output, DataBlockInput* input);


private:

    friend class BaseOperator;
    friend class ConnectCommand;
    friend class DisconnectCommand;

    void set_parent_operator(BaseOperator* op);

    // Non action version of connect_to and disconnect_from
    bool set_connection(BaseDataBlock* data_block);

    BaseOperator* parent_operator = nullptr;
    BaseDataBlock* connection = nullptr;

};
