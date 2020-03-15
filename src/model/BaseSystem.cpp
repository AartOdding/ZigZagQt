#include "BaseSystem.hpp"




QHash<QString, BaseSystem*>* availableSystems()
{
    static QHash<QString, BaseSystem*> availableSystems;
    return &availableSystems;
}



BaseSystem::BaseSystem(const QString& systemName)
    : m_systemName(systemName)
{
    if (!availableSystems()->contains(systemName))
    {
        availableSystems()->insert(systemName, this);
    }
    else
    {
        // TODO: log error
    }
}


BaseSystem::~BaseSystem()
{
    // Should not remove the system from the availableSystems, because the system
    // should be a static variable, in which case it might be deleted after the
    // availableSystems hash map had been deleted.
}



void BaseSystem::load()
{
    if (!m_isLoaded && canBeLoaded())
    {
        loadSystem();
        m_isLoaded = true;
    }
}


void BaseSystem::unload()
{
    if (m_isLoaded && canBeUnloaded())
    {
        unloadSystem();
        m_isLoaded = false;
    }
}


bool BaseSystem::isLoaded() const
{
    return m_isLoaded;
}


bool BaseSystem::canBeLoaded()
{
    return true;
}


bool BaseSystem::canBeUnloaded()
{
    return true;
}


const QString& BaseSystem::getSystemName() const
{
    return m_systemName;
}


void BaseSystem::beginOfFrame()
{

}


void BaseSystem::endOfFrame()
{

}
