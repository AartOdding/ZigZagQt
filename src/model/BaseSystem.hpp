#pragma once

#include <QHash>
#include <QString>

#include <vector>


/*
 * Systems should be available for the complete duration of the program.
 *
 */
class BaseSystem
{
public:

    BaseSystem(const QString& systemName);

    virtual ~BaseSystem();


    void load();

    void unload();

    bool isLoaded() const;


    virtual bool canBeLoaded();

    virtual bool canBeUnloaded();


    const QString& getSystemName() const;


protected:

    virtual void loadSystem() = 0;

    virtual void unloadSystem() = 0;


    virtual void beginOfFrame();

    virtual void endOfFrame();


private:

    QString m_systemName;

    bool m_isLoaded;

};


QHash<QString, BaseSystem*>* availableSystems();
