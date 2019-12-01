#pragma once

#include <vector>
#include <QString>
#include <QMetaType>


class BaseOperator;
class BaseComponent;

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

    Operator = 500,
    DataInput = 501,
    DataOutput = 502,
    DataView = 503
};



class BaseParameterOld
{
public:

    BaseParameterOld(BaseParameterOld* parent_parameter, ParameterType parameter_type, const QString& name);

    virtual ~BaseParameterOld();

    virtual int num_components() const { return 0; }
    virtual BaseComponent* get_component(int index) { return nullptr; }
    virtual const BaseComponent* get_component(int index) const { return nullptr; }

    virtual void remove_imports_exports();

    virtual void process_parameter_changes();
    virtual void parameter_changed(BaseParameterOld*) { }

    const QString& get_name() const;
    ParameterType get_parameter_type() const;

    bool is_operator() const;
    BaseOperator * get_operator() const;

    bool has_parent_parameter() const;
    BaseParameterOld * get_parent_parameter() const;
    bool has_child_parameters() const;
    const std::vector<BaseParameterOld*>& get_child_parameters() const;

    virtual void set_from_xml(QXmlStreamReader& xml);
    virtual void write_to_xml(XmlSerializer& xml);

private:

    BaseParameterOld * parent_parameter;
    std::vector<BaseParameterOld*> child_parameters;
    QString name;
    ParameterType parameter_type;

};


Q_DECLARE_METATYPE(BaseParameterOld*);
