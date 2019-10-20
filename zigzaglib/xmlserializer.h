#pragma once

#include <type_traits>
#include <unordered_map>
#include <QXmlStreamWriter>

class QFile;


class XmlSerializer
{

public:

    XmlSerializer(QFile& target_file);

    XmlSerializer(QString& target_string);


    void begin_element(const QString& element_name);

    void end_element();

    void add_text_attribute(const QString& attribute_name, const QString& attribute_text);

    template<typename INT_T>
    void add_int_attribute(const QString& attribute_name, INT_T attribute_value)
    {
        static_assert(std::is_integral_v<INT_T>, "Use an integer type instead!");
        xml_stream.writeAttribute(attribute_name, QString::number(attribute_value));
    }

    void add_text_element(const QString& element_name, const QString& element_text);

    void add_double_element(const QString& element_name, double element_value);

    template<typename INT_T>
    void add_int_element(const QString& element_name, INT_T value)
    {
        static_assert(std::is_integral_v<INT_T>, "Use an integer type instead!");
        xml_stream.writeTextElement(element_name, QString::number(value));
    }

    void finish();

    quint32 id(const void *);


private:

    std::unordered_map<const void *, quint32> ids;
    quint32 current_id = 1337;

    QXmlStreamWriter xml_stream;

};
