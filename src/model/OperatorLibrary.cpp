#include "OperatorLibrary.hpp"

#include "BaseOperator.hpp"
#include "BaseDataType.hpp"
#include "view/basedataview.h"




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


void OperatorLibrary::add(const OperatorTypeDetails* type)
{
    if (type)
    {
        //m_operators[type->package][type->name] = type;
    }
}


void OperatorLibrary::add(const OperatorTypeDetails& type)
{
    add(&type);
}


QStringList OperatorLibrary::packages() const
{
    QStringList returnValue = m_operators.keys();
    returnValue.sort();
    return returnValue;
}


QList<const OperatorTypeDetails*> OperatorLibrary::getPackage(const QString& package) const
{
    QList<const OperatorTypeDetails*> returnValue;

    if (m_operators.contains(package))
    {
        returnValue = m_operators[package].values();
        std::sort(returnValue.begin(), returnValue.end());
    }
    return returnValue;
}


const OperatorTypeDetails* OperatorLibrary::getOperator(const QString& package, const QString& operatorName)
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
