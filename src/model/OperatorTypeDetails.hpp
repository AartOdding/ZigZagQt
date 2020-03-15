#pragma once

#include <functional>
#include <vector>
#include <QString>
#include <QStringList>


class BaseOperator;
class BaseZigZagObject;
struct DataTypeDescription;
struct DataViewDescription;


enum OperatorTypeFields
{
    OperatorType_name = Qt::UserRole + 1,
    OperatorType_briefDescription,
    OperatorType_systemDependencies,
    OperatorType_author,
    OperatorType_extendedDescription
};


struct OperatorTypeDetails
{
    QString name;
    QString briefDescription;
    QStringList systemDependencies;
    QString author;
    QString extendedDescription;
};
