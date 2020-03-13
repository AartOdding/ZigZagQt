#pragma once

#include <QList>
#include <QHash>
#include <QString>
#include <QStringList>
#include <QAbstractListModel>


struct DataTypeDescription;
struct DataViewDescription;
struct OperatorKind;

class OperatorLibrary;


OperatorLibrary* activeOperatorLibrary(OperatorLibrary* resetActiveOperatorLibrary = nullptr);
OperatorLibrary* defaultOperatorLibrary();



class OperatorPackage : public QAbstractListModel
{
public:

    OperatorPackage(const QString& packageName);

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:

    QString m_packageName;

    std::vector<std::pair<QString, const OperatorKind*>> m_packageContents;

};


class OperatorLibrary
{

public:

    OperatorLibrary();

    void add(const OperatorKind* type);
    void add(const OperatorKind& type);

    QStringList packages() const;

    QList<const OperatorKind*> getPackage(const QString& package) const;

    const OperatorKind* getOperator(const QString& package, const QString& operatorName);


private:

    QHash<QString, QHash<QString, const OperatorKind*>> m_operators;

};
