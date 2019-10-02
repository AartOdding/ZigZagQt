#pragma once

#include <vector>
#include <initializer_list>

#include <QObject>
#include <QString>



class EnumDefinition : public QObject
{
    Q_OBJECT

public:

    EnumDefinition(const QString& enum_name);
    EnumDefinition(const char* enum_name, std::initializer_list<const char*> enum_values);

    bool add_value(const QString& value);
    bool insert_value(const QString& value, int index);

    bool remove_value(int index);
    bool remove_value(const QString& value);

    bool contains(int index) const;
    bool contains(const QString& value) const;

    int index_of(const QString& value) const;

    const QString& enum_name() const;
    int size() const;

    const QString& operator[](int index) const;

    std::vector<QString>::const_iterator begin() const;
    std::vector<QString>::const_iterator end() const;


signals:

    /*
     * When new values are inserted, or values are removed the indexes of some values change.
     * this signal lets you know when indexes have changed. Indexes below first_invalid_index
     * are gauranteed to still be valid. However any pointer or reference to an enum value is
     * also invalidated, because the vector might have reallocated.
     */
    void invalidated_from(int first_invalid_index);


private:

    const QString name;

    std::vector<QString> enum_values;

};
