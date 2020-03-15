#pragma once

#include <QList>
#include <QHash>
#include <QString>
#include <QStringList>


struct DataTypeDescription;
struct DataViewDescription;
struct OperatorTypeDetails;

class OperatorLibrary;


OperatorLibrary* activeOperatorLibrary(OperatorLibrary* resetActiveOperatorLibrary = nullptr);
OperatorLibrary* defaultOperatorLibrary();




class OperatorLibrary
{

public:

    OperatorLibrary();

    void add(const OperatorTypeDetails* type);
    void add(const OperatorTypeDetails& type);

    QStringList packages() const;

    QList<const OperatorTypeDetails*> getPackage(const QString& package) const;

    const OperatorTypeDetails* getOperator(const QString& package, const QString& operatorName);


private:

    QHash<QString, QHash<QString, const OperatorTypeDetails*>> m_operators;

};
