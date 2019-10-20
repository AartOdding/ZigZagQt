#include "xmlserializer.h"

#include <QFile>


XmlSerializer::XmlSerializer(QFile& target_file)
    : xml_stream(&target_file)
{
    xml_stream.setAutoFormatting(true);
    xml_stream.writeStartDocument();
}


XmlSerializer::XmlSerializer(QString& target_string)
    : xml_stream(&target_string)
{
    xml_stream.setAutoFormatting(true);
    xml_stream.writeStartDocument();
}


void XmlSerializer::begin_element(const QString& element_name)
{
    xml_stream.writeStartElement(element_name);
}


void XmlSerializer::end_element()
{
    xml_stream.writeEndElement();
}


void XmlSerializer::add_text_attribute(const QString& attribute_name, const QString& attribute_text)
{
    xml_stream.writeAttribute(attribute_name, attribute_text);
}


void XmlSerializer::add_text_element(const QString& element_name, const QString& element_text)
{
    xml_stream.writeTextElement(element_name, element_text);
}


void XmlSerializer::add_double_element(const QString& element_name, double value)
{
    xml_stream.writeTextElement(element_name, QString::number(value));
}


void XmlSerializer::finish()
{
    xml_stream.writeEndDocument();
}


quint32 XmlSerializer::id(const void * address)
{
    if (address == nullptr)
    {
        return 0;
    }
    else if (ids.count(address) > 0)
    {
        return ids[address];
    }
    else
    {
        ids[address] = current_id;
        return current_id++;
    }
}
