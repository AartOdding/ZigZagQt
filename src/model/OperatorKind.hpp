#pragma once

#include <functional>
#include <vector>
#include <QString>


class BaseOperator;
class BaseZigZagObject;
struct DataTypeDescription;
struct DataViewDescription;


enum OperatorKindFields
{
    OperatorKindName = Qt::UserRole + 1,
    OperatorKindPackage,
    OperatorKindAuthor,
    OperatorKindBriefDescription,
    OperatorKindExtendedDescription
};


struct OperatorKind
{
    QString name;
    QString package;
    QString author;
    QString briefDescription;
    QString extendedDescription;
};


struct RegisterOperatorKind
{
    using CreateFunctionType = std::function<BaseOperator*(BaseZigZagObject*)>;

    RegisterOperatorKind(const OperatorKind* kind, CreateFunctionType createFunction);
};


inline bool operator<(const OperatorKind& t1, const OperatorKind& t2)
{
    return t1.name < t2.name;
}
