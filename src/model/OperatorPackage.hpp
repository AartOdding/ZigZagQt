#pragma once

#include <QString>
#include <QAbstractListModel>

#include <initializer_list>
#include <utility>

#include "OperatorTypeDetails.hpp"



class OperatorPackage : public QAbstractListModel
{
    Q_OBJECT

public:

    using OperatorCreateFn = BaseOperator*(*)(BaseZigZagObject*);
    using OperatorEntry = std::pair<const OperatorTypeDetails*, OperatorCreateFn>;

    OperatorPackage() = delete;
    OperatorPackage(const OperatorPackage&) = delete;
    OperatorPackage(OperatorPackage&&) = delete;


    OperatorPackage(const QString& packageName);

    OperatorPackage(const QString& packageName, std::initializer_list<OperatorEntry> operators);


    const QString& packageName() const;


    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;


private:

    QString m_packageName;

    std::vector<OperatorEntry> m_packageContents;

};


QHash<QString, OperatorPackage*>* availableOperatorPackages();
