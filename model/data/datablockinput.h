#pragma once

#include <QObject>



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


    virtual bool compatible_with(const BaseDataBlock* data_block);

    bool connect_with(BaseDataBlock* data_block);
    bool disconnect_from(BaseDataBlock* data_block);


    const char * const type_name;

signals:

    void parameters_modified();

private:

    BaseDataBlock* connection;

};
