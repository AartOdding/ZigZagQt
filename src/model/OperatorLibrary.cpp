#include "OperatorLibrary.hpp"

#include "BaseOperator.hpp"
#include "BaseDataType.hpp"
#include "view/basedataview.h"



OperatorLibrary* OperatorLibrary::instance()
{
    static OperatorLibrary library;
    return &library;
}


OperatorLibrary::OperatorLibrary()
{

}


void OperatorLibrary::add(const OperatorDescription* type)
{
    if (type)
    {
        m_operators[type->package][type->name] = type;
    }
}


void OperatorLibrary::add(const OperatorDescription& type)
{
    add(&type);
}


QStringList OperatorLibrary::packages() const
{
    QStringList returnValue = m_operators.keys();
    returnValue.sort();
    return returnValue;
}


QList<const OperatorDescription*> OperatorLibrary::getPackage(const QString& package) const
{
    QList<const OperatorDescription*> returnValue;

    if (m_operators.contains(package))
    {
        returnValue = m_operators[package].values();
        std::sort(returnValue.begin(), returnValue.end());
    }
    return returnValue;
}


const OperatorDescription* OperatorLibrary::getOperator(const QString& package, const QString& operatorName)
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
