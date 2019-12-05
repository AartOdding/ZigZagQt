#include "baseparameterold.h"

#include "model/baseoperator.h"
#include "zigzaglib/xmlserializer.h"
#include <QXmlStreamWriter>     // TODO replace for XmlDeserializer

#include "utility/std_containers_helpers.h"




BaseParameterOld::BaseParameterOld(BaseParameterOld* parent_, ParameterType type_, const QString& name_)
    : parent_parameter(parent_), name(name_), parameter_type(type_)
{
    if (parent_parameter)
    {
        Q_ASSERT(parent_parameter != this);
        Q_ASSERT(!contains(parent_parameter->child_parameters, this));
        parent_parameter->child_parameters.push_back(this);
    }
}


BaseParameterOld::~BaseParameterOld()
{
    if (parent_parameter)
    {
        auto pos = std::find(parent_parameter->child_parameters.begin(), parent_parameter->child_parameters.end(), this);
        Q_ASSERT(pos != parent_parameter->child_parameters.end());
        parent_parameter->child_parameters.erase(pos);
    }
}


void BaseParameterOld::remove_imports_exports()
{
    for (auto child : child_parameters)
    {
        child->remove_imports_exports();
    }
    for (int i = 0; i < num_components(); ++i)
    {
        get_component(i)->stopImporting();
        get_component(i)->stopExporting();
    }
}


void BaseParameterOld::process_parameter_changes()
{
    for (auto child : child_parameters)
    {
        child->process_parameter_changes();
    }

    bool changed = false;

    for (int i = 0; i < num_components(); ++i)
    {
        changed |= get_component(i)->run();
    }

    if (changed)
    {
        auto p = parent_parameter;

        while(p)
        {
            p->parameter_changed(this);
            p = p->get_parent_parameter();
        }
    }
}


const QString& BaseParameterOld::get_name() const
{
    return name;
}


ParameterType BaseParameterOld::get_parameter_type() const
{
    return parameter_type;
}


bool BaseParameterOld::is_operator() const
{
    return dynamic_cast<const BaseOperator*>(this);
}


BaseOperator * BaseParameterOld::get_operator() const
{
    if (parent_parameter->is_operator())
    {
        return static_cast<BaseOperator*>(parent_parameter);
    }
    else
    {
        return parent_parameter->get_operator();
    }
}


bool BaseParameterOld::has_parent_parameter() const
{
    return parent_parameter;
}


BaseParameterOld * BaseParameterOld::get_parent_parameter() const
{
    return parent_parameter;
}


bool BaseParameterOld::has_child_parameters() const
{
    return !child_parameters.empty();
}


const std::vector<BaseParameterOld*>& BaseParameterOld::get_child_parameters() const
{
    return child_parameters;
}


void BaseParameterOld::set_from_xml(QXmlStreamReader& xml)
{

}


void BaseParameterOld::write_to_xml(XmlSerializer& xml)
{
    xml.begin_element("BaseParameter");
    xml.add_int_attribute("id", xml.id(this));

        xml.add_int_element("parameter_type", static_cast<qint64>(parameter_type));
        xml.add_text_element("name", name);

        xml.begin_element("child_parameters");
        xml.add_int_attribute("size", child_parameters.size());

            for (auto child : child_parameters)
            {
                child->write_to_xml(xml);
            }

        xml.end_element(); // ends child_parameters

        xml.begin_element("components");
        xml.add_int_attribute("size", num_components());

            for (int i = 0; i < num_components(); ++i)
            {
                get_component(i)->writeXml(xml);
            }

        xml.end_element(); // ends components

    xml.end_element(); // ends BaseParameter
}



















