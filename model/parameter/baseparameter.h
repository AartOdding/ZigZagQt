#pragma once

#include <vector>
#include <QString>
#include <QMetaType>


class BaseOperator;
class ParameterOwner;
class BaseParameterComponent;

class XmlSerializer;
class QXmlStreamReader;



enum class ParameterType : qint64 // 8 Byte int for better alignment.
{
    Int  = 0,
    Int2 = 1,
    Int3 = 2,
    Int4 = 3,
    Float  = 4,
    Float2 = 5,
    Float3 = 6,
    Float4 = 7,
    Enum   = 8,
    Button = 9,
    Matrix3x3 = 10,
    Matrix4x4 = 11,
    // Add more here

    ParameterOwner = 500,
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


    virtual void set_from_xml(QXmlStreamReader& xml);

    virtual void write_to_xml(XmlSerializer& xml);


private:

    QString name;

    ParameterOwner * parent;

    ParameterType parameter_type;

};


Q_DECLARE_METATYPE(BaseParameter*);
