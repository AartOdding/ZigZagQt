#pragma once

#include <vector>
#include <QMetaType>


class BaseOperator;
class ParameterOwner;
class ParameterComponent;



enum class ParameterType : short
{
    Float,
    Float2,
    Float3,
    Float4,
    Matrix3x3,
    Matrix4x4,
    Int,
    Int2,
    Int3,
    Int4,
    Enum,
    ParameterOwner,
};



class BaseParameter
{
public:

    BaseParameter(ParameterOwner* owner, ParameterType parameter_type, const char * name);

    virtual ~BaseParameter();



    virtual int num_components() const = 0;

    virtual ParameterComponent* get_component(int index) = 0;

    virtual const ParameterComponent* get_component(int index) const = 0;



    virtual void remove_imports_exports();

    // Notifies parent operator if changed.
    virtual void process_parameter_changes();



    const char * get_name() const;

    ParameterType get_parameter_type() const;

    ParameterOwner * get_parent() const;

    // Recursive
    BaseOperator * get_operator() const;


private:

    ParameterOwner * parent;

    const char * name;

    ParameterType parameter_type;


};


Q_DECLARE_METATYPE(BaseParameter*);
