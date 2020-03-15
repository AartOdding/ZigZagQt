#include "LibrarySystem.hpp"
#include "model/OperatorPackage.hpp"

#include <iostream>

LibrarySystem librarySystem;



LibrarySystem::LibrarySystem()
    : BaseSystem("librarySystem")
{

}


bool LibrarySystem::canBeLoaded()
{
    return true;
}


OperatorPackage* LibrarySystem::getOperatorPackage(const QString& packageName)
{
    if (availableOperatorPackages()->contains(packageName))
    {
        return availableOperatorPackages()->value(packageName);
    }
    return nullptr;
}


QStringListModel* LibrarySystem::getAvailablePackageNames()
{
    return &m_availablePackages;
}


void LibrarySystem::loadSystem()
{
    QStringList packageNames;
    packageNames.reserve(availableOperatorPackages()->size());

    for (auto pkg : *availableOperatorPackages())
    {
        packageNames << pkg->packageName();
    }

    m_availablePackages.setStringList(packageNames);
}


void LibrarySystem::unloadSystem()
{

}
