#pragma once

#include <QXmlStreamWriter>
#include <QVariantMap>


class BaseZigZagObject;


class Serializer
{
public:

    Serializer();

    void serialize(const QObject* object);

    QString text;

private:

    void serializeRecursive(const QObject* object, const QMetaObject* metaObject);

    static void serializeVariant(const QVariant& variant, const QString& name, QXmlStreamWriter& xml);

    QXmlStreamWriter xml;

};
