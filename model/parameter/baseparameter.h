#pragma once

#include <vector>
#include <QString>
#include <QMetaType>


class BaseOperator;
class ParameterOwner;
class BaseParameterComponent;



enum class ParameterType : int64_t // Use 8 byte int for better alignment.
{
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Enum,
    Button,
    Matrix3x3,
    Matrix4x4,
    ParameterOwner,
};



class BaseParameter
{
public:

    BaseParameter(ParameterOwner* parent, ParameterType parameter_type, const QString& name);

    virtual ~BaseParameter();


    virtual int num_components() const = 0;

    virtual BaseParameterComponent* get_component(int index) = 0;

    virtual const BaseParameterComponent* get_component(int index) const = 0;


    virtual void remove_imports_exports();  // Overrides from ParameterOwner, removes imports/ exports for every component.

    virtual void process_parameter_changes();  // Notifies parent operator if changed.


    const QString & get_name() const;

    ParameterType get_parameter_type() const;

    ParameterOwner * get_parent() const;

    BaseOperator * get_operator() const;


    // The default implementation of set_from_xml will loop through all the components and set them from the xml file.
    // If you decide to override this function you need to make sure that either you deserialize all the parameters
    // yourself, or that you only deserialize the non parameter members, and call the set_from_xml function in the base
    // implementation, "BaseParameter::set_from_xml();"
    //virtual void set_from_xml();

    // The default implementation of get_as_xml will loop through all the components and return them as xml.
    // If you decide to override this function you need to make sure that either you serialize all the parameters
    // yourself, or that you only serialize the non parameter members, and call the get_as_xml function in the base
    // implementation, "BaseParameter::get_as_xml();"
    //virtual void get_as_xml();


private:

    QString name;

    ParameterOwner * parent;

    ParameterType parameter_type;

};


Q_DECLARE_METATYPE(BaseParameter*);
