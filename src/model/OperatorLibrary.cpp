#include "OperatorLibrary.hpp"

#include "BaseOperator.hpp"
#include "BaseDataType.hpp"
#include "view/basedataview.h"




OperatorPackage::OperatorPackage(const QString& packageName)
    : m_packageName(packageName)
{

}


int OperatorPackage::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        return static_cast<int>(m_packageContents.size());
    }
}


QVariant OperatorPackage::data(const QModelIndex &index, int role) const
{

}


QHash<int, QByteArray> OperatorPackage::roleNames() const
{

}



OperatorLibrary* activeOperatorLibrary(OperatorLibrary* resetActiveOperatorLibrary)
{
    static OperatorLibrary* activeLibrary = defaultOperatorLibrary();

    if (resetActiveOperatorLibrary)
    {
        activeLibrary = resetActiveOperatorLibrary;
    }
    return activeLibrary;
}


OperatorLibrary* defaultOperatorLibrary()
{
    static OperatorLibrary defaultLibrary;

    return &defaultLibrary;
}

/*
OperatorLibrary* OperatorLibrary::instance()
{
    static OperatorLibrary library;
    return &library;
}*/


OperatorLibrary::OperatorLibrary()
{

}


void OperatorLibrary::add(const OperatorKind* type)
{
    if (type)
    {
        m_operators[type->package][type->name] = type;
    }
}


void OperatorLibrary::add(const OperatorKind& type)
{
    add(&type);
}


QStringList OperatorLibrary::packages() const
{
    QStringList returnValue = m_operators.keys();
    returnValue.sort();
    return returnValue;
}


QList<const OperatorKind*> OperatorLibrary::getPackage(const QString& package) const
{
    QList<const OperatorKind*> returnValue;

    if (m_operators.contains(package))
    {
        returnValue = m_operators[package].values();
        std::sort(returnValue.begin(), returnValue.end());
    }
    return returnValue;
}


const OperatorKind* OperatorLibrary::getOperator(const QString& package, const QString& operatorName)
{
    if (m_operators.contains(package))
    {
        if (m_operators[package].contains(operatorName))
        {
            return m_operators[package][operatorName];
        }
    }
    return nullptr;
}
