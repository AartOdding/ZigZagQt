#pragma once

#include <QHash>
#include <QString>

#include <vector>


/*
 * Systems should be available for the complete duration of the program
 *
 */
class BaseSystem
{
public:

    BaseSystem(const QString& systemName, bool tryLoadOnStartup);

    virtual ~BaseSystem() = default;


    virtual bool canBeLoaded() = 0;

    const QString& getSystemName() const;

    bool isLoaded() const;

    static const QHash<QString, BaseSystem*>& getAvailableSystems();

protected:

    virtual void loadSystem() = 0;

    virtual void unloadSystem() = 0;


    virtual void beginOfFrame() { }

    virtual void endOfFrame() { }

private:

    QString m_systemName;

    bool m_isLoaded;

    static QHash<QString, BaseSystem*> availableSystems;

};
