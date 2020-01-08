#include "Serializer.hpp"
#include "model/projectmodel.h"
#include "model/BaseZigZagObject.hpp"
#include "model/BaseOperator.hpp"
#include "model/parameter/BaseParameter.hpp"
#include "model/parameter/BaseComponent.hpp"
#include "model/BaseDataType.hpp"
#include "model/datainput.h"
#include "view/basedataview.h"

#include <QMetaMethod>
#include <QMetaType>
#include <QMetaObject>

#include <iostream>


Serializer::Serializer()
    : xml(&text)
{
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
}



void Serializer::serializeVariant(const QVariant& variant, const QString& name, QXmlStreamWriter& xml)
{
    if (variant.type() == QMetaType::QVariantMap)
    {
        xml.writeStartElement(variant.typeName());
        xml.writeAttribute(QStringLiteral("id"), name);

        auto map = variant.toMap();

        for (auto key = map.keyBegin(); key != map.keyEnd(); ++key)
        {
            serializeVariant(map.value(*key), *key, xml);
        }

        xml.writeEndElement();
    }
    else if (variant.type() == QMetaType::QStringList)
    {
        xml.writeStartElement(QStringLiteral("QStringList"));
        xml.writeAttribute(QStringLiteral("id"), name);

        auto stringList = variant.toStringList();

        for (auto& string : stringList)
        {
            xml.writeStartElement(QStringLiteral("QString"));
            xml.writeCharacters(string);
            xml.writeEndElement();
        }

        xml.writeEndElement();
    }
    else if (variant.canConvert(QMetaType::QString))
    {
        xml.writeStartElement(variant.typeName());
        xml.writeAttribute(QStringLiteral("id"), name);

        xml.writeCharacters(variant.toString());

        xml.writeEndElement();
    }
    else
    {
        throw "error";
    }
}



void Serializer::serialize(const QObject* object)
{
    static const QString CATEGORY = QStringLiteral("category");
    static const QString PACKAGE = QStringLiteral("package");
    static const QString TYPE = QStringLiteral("type");

    xml.writeStartElement(QStringLiteral("object"));

    if (qobject_cast<const BaseComponent*>(object))
    {
        xml.writeAttribute(CATEGORY, QStringLiteral("component"));
        xml.writeAttribute(TYPE, object->metaObject()->className());
    }
    else if (qobject_cast<const BaseParameter*>(object))
    {
        xml.writeAttribute(CATEGORY, QStringLiteral("parameter"));
        xml.writeAttribute(TYPE, object->metaObject()->className());
    }
    else if (qobject_cast<const DataInput*>(object))
    {
        auto in = static_cast<const DataInput*>(object);
        xml.writeAttribute(CATEGORY, QStringLiteral("dataInput"));
    }
    else if (qobject_cast<const BaseDataType*>(object))
    {
        auto out = static_cast<const BaseDataType*>(object);
        xml.writeAttribute(CATEGORY, QStringLiteral("dataType"));
    }
    else if (qobject_cast<const BaseDataView*>(object))
    {
        auto view = static_cast<const BaseDataView*>(object);
        xml.writeAttribute(CATEGORY, QStringLiteral("dataView"));
    }
    else if (qobject_cast<const BaseOperator*>(object))
    {
        auto op = static_cast<const BaseOperator*>(object);
        xml.writeAttribute(CATEGORY, QStringLiteral("operator"));
        xml.writeAttribute(PACKAGE, op->description()->package);
        xml.writeAttribute(TYPE, op->description()->name);
    }
    else if (qobject_cast<const ProjectModel*>(object))
    {
        xml.writeAttribute(CATEGORY, QStringLiteral("network"));
    }
    xml.writeAttribute(QStringLiteral("id"), object->objectName());

    //----------

    QVariantMap state;
    state = static_cast<const BaseZigZagObject*>(object)->storeState();

    if (state.size() > 0)
    {
        xml.writeStartElement(QStringLiteral("state"));
        serializeVariant(state, QString(), xml);
        xml.writeEndElement(); // state
    }

    //----------

    auto children = object->findChildren<const BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly);

    if (!children.empty())
    {
        xml.writeStartElement(QStringLiteral("children"));

        for (auto child : children)
        {
            serialize(child);
        }

        xml.writeEndElement(); // children
    }
    xml.writeEndElement(); // object
}


/*
void Serializer::serializeRecursive(const BaseZigZagObject* object, const QMetaObject* metaObject)
{
    auto children = object->findChildren<BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly);
    auto components = object->findChildren<BaseComponent*>(QString(), Qt::FindDirectChildrenOnly);

    xml.writeStartElement(QStringLiteral("object"));

    if (qobject_cast<Base>)


    if (metaObject->superClass())
    {
        if (metaObject->superClass()->className() != QStringLiteral("BaseZigZagObject"))
        {
            xml.writeStartElement(QStringLiteral("Base"));
            serializeRecursive(object, metaObject->superClass());
            xml.writeEndElement(); // Base
        }
    }


    QVariantMap selfState = object->storeState();
    std::vector<QVariantMap> parametersState;
    std::vector<QVariantMap> childrenState;

    parametersState.reserve(children.size());
    childrenState.reserve(children.size());

    for (auto child : children)
    {
        if (qobject_cast<BaseParameter*>(child))
        {
            parametersState.push_back(child->storeState());
        }
        else
        {

        }
    }
    //metaObject->method(writeState).invoke(const_cast<BaseZigZagObject*>(object),
    //                                      Qt::DirectConnection, Q_ARG(QVariantMap*, &map));

    xml.writeStartElement(QStringLiteral("State"));

    if (selfState.size() > 0)
    {
        serializeVariant(selfState, metaObject->className(), xml);
    }

    xml.writeEndElement(); // State

    //if (parameters.size() > 0)
    {
        xml.writeStartElement(QStringLiteral("Parameters"));

        xml.writeEndElement(); // Parameters
    }

    xml.writeStartElement(QStringLiteral("Children"));

    xml.writeEndElement(); // Children
    xml.writeEndElement(); // className
}*/

