#include "OperatorPackage.hpp"

#include <QQmlEngine>



QHash<QString, OperatorPackage*>* availableOperatorPackages()
{
    static QHash<QString, OperatorPackage*> availableOperatorPackages;
    return &availableOperatorPackages;
}



OperatorPackage::OperatorPackage(const QString& packageName)
    : m_packageName(packageName)
{
    if (!availableOperatorPackages()->contains(packageName))
    {
        availableOperatorPackages()->insert(packageName, this);
    }
    else
    {
        // TODO: log error
    }
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}


OperatorPackage::OperatorPackage(const QString& packageName, std::initializer_list<OperatorEntry> operators)
    : m_packageName(packageName),
      m_packageContents(operators)
{
    if (!availableOperatorPackages()->contains(packageName))
    {
        availableOperatorPackages()->insert(packageName, this);
    }
    else
    {
        // TODO: log error
    }
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}


const QString& OperatorPackage::packageName() const
{
    return m_packageName;
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
    if (index.row() >= 0 && index.row() < static_cast<int>(m_packageContents.size()))
    {
        switch (role)
        {
        case OperatorType_name:
            return m_packageContents[index.row()].first->name;
        case OperatorType_briefDescription:
            return m_packageContents[index.row()].first->briefDescription;
        case OperatorType_systemDependencies:
            return m_packageContents[index.row()].first->systemDependencies;
        case OperatorType_author:
            return m_packageContents[index.row()].first->author;
        case OperatorType_extendedDescription:
            return m_packageContents[index.row()].first->extendedDescription;
        }
    }
    return QVariant();
}


QHash<int, QByteArray> OperatorPackage::roleNames() const
{
    return
    {
        { OperatorType_name,                "name" },
        { OperatorType_briefDescription,    "briefDescription" },
        { OperatorType_systemDependencies,  "systemDependencies" },
        { OperatorType_author,              "author" },
        { OperatorType_extendedDescription, "extendedDescription" }
    };
}

