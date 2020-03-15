#pragma once

#include <QObject>
#include <QStringListModel>
#include <QAbstractListModel>

#include <model/BaseSystem.hpp>
#include <model/OperatorPackage.hpp>



class LibrarySystem : public QObject,
                      public BaseSystem
{
    Q_OBJECT

public:

    LibrarySystem();

    virtual bool canBeLoaded() override;

    Q_INVOKABLE OperatorPackage* getOperatorPackage(const QString& packageName);

    QStringListModel* getAvailablePackageNames();

protected:

    virtual void loadSystem() override;

    virtual void unloadSystem() override;

private:

    QStringListModel m_availablePackages;

};


extern LibrarySystem librarySystem;
