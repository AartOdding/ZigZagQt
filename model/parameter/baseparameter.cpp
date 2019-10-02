#include "baseparameter.h"
#include "parameterowner.h"
#include "application.h"

#include "model/baseoperator.h"
#include "model/xmlserializer.h"

#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"

#include <QXmlStreamWriter>



BaseParameter::BaseParameter(ParameterOwner* parent_, ParameterType type_, const QString& name_)
    : name(name_), parent(parent_), parameter_type(type_)
{
    // BaseOperator also inherits parameter so parent can be nullptr.
    if (parent)
    {
        parent->register_parameter(this);
    }
}


BaseParameter::~BaseParameter()
{
    if (parent)
    {
        parent->deregister_parameter(this);
    }
}


void BaseParameter::remove_imports_exports()
{
    for (int i = 0; i < num_components(); ++i)
    {
        get_component(i)->stop_importing();
        get_component(i)->stop_exporting();
    }
}


void BaseParameter::process_parameter_changes()
{
    bool changed = false;
    for (int i = 0; i < num_components(); ++i)
    {
        changed |= get_component(i)->process_changes();
    }
    if (changed)
    {
        ParameterOwner * owner = get_parent();

        while(owner)
        {
            owner->parameter_changed(this);
            owner = owner->get_parent();
        }
    }
}


const QString& BaseParameter::get_name() const
{
    return name;
}


ParameterType BaseParameter::get_parameter_type() const
{
    return parameter_type;
}


ParameterOwner * BaseParameter::get_parent() const
{
    return parent;
}


BaseOperator * BaseParameter::get_operator() const
{
    if (parent->is_operator())
    {
        return static_cast<BaseOperator*>(parent);
    }
    else
    {
        return parent->get_operator();
    }
}


void BaseParameter::set_from_xml(QXmlStreamReader& xml)
{

}


void BaseParameter::write_to_xml(XmlSerializer& xml)
{
    xml.begin_element("BaseParameter");
    xml.add_int_attribute("id", xml.id(this));

        xml.add_int_element("parameter_type", static_cast<qint64>(parameter_type));
        xml.add_text_element("name", name);

        xml.begin_element("components");
        xml.add_int_attribute("size", num_components());

            for (int i = 0; i < num_components(); ++i)
            {
                get_component(i)->write_to_xml(xml);
            }

        xml.end_element(); // ends components

    xml.end_element(); // ends BaseParameter
}



















