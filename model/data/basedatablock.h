#pragma once

#include <vector>

#include <QList>
#include <QObject>


class QString;
class BaseParameter;
class DataBlockInput;



class BaseDataBlock : public QObject
{
    Q_OBJECT

public:

    BaseDataBlock(const char * data_type_name);

    virtual ~BaseDataBlock();


    // This method needs to be overriden by the inheriting class, so that the GUI
    // can query how many parameters to add to the operator.
    virtual std::vector<BaseParameter*> get_parameters() = 0;


    // Causes get_paramers() to be called again, to reevaluate what parameters appear
    // in the GUI. Call this function after adding or removing a parameter.
    void refresh_parameters();


    bool connect_with(DataBlockInput* input);
    bool disconnect_from(DataBlockInput* input);


    const char * const type_name;


    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }


private:

    QList<DataBlockInput*> connections;


signals:

    void parameters_modified();


};
