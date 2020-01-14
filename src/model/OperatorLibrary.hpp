#pragma once

#include <QList>
#include <QHash>
#include <QString>
#include <QStringList>


struct DataTypeDescription;
struct DataViewTypeInfo;
struct OperatorDescription;



class OperatorLibrary
{

public:

    static OperatorLibrary* instance();

    void add(const OperatorDescription* type);
    void add(const OperatorDescription& type);

    QStringList packages() const;

    QList<const OperatorDescription*> getPackage(const QString& package) const;

    const OperatorDescription* getOperator(const QString& package, const QString& operatorName);


private:

    OperatorLibrary();

    QHash<QString, QHash<QString, const OperatorDescription*>> m_operators;

};
