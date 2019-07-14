#pragma once

#include <utility>
#include <initializer_list>

#include <QHash>
#include <QString>


class EnumDefinition
{

public:

    EnumDefinition(const QString& name);

    EnumDefinition(const QString& name, std::initializer_list<QString> values);

    EnumDefinition(const QString& name, std::initializer_list<std::pair<QString, int>> values);


    bool add(const QString& name);

    bool add(const QString& name, int ordinal);

    bool remove(int ordinal);

    bool remove(const QString& name);


    int size() const;

    bool contains(int ordinal) const;

    bool contains(const QString& name) const;

    QString name_of(int ordinal) const;

    int ordinal_of(const QString& name) const;


    QHash<int, QString>::ConstIterator begin() const;

    QHash<int, QString>::ConstIterator end() const;


private:

    QString enum_name;

    QHash<int, QString> ordinal_to_name;
    QHash<QString, int> name_to_ordinal;

};
