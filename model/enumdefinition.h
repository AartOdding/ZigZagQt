#pragma once

#include <string>
#include <vector>
#include <utility>
#include <initializer_list>

#include <QObject>


class EnumDefinition : public QObject
{
    Q_OBJECT

public:

    EnumDefinition(const char* name);

    EnumDefinition(const char* name, std::initializer_list<const char*> values);


    bool add(const char* value);

    bool insert(const char* value, int index);


    bool remove(int index);

    bool remove(const char* value);


    bool contains(int index) const;

    bool contains(const char* name) const;

    int index_of(const char* name) const;


    int size() const;


    const std::string& operator[](int index) const;

    std::vector<std::string>::const_iterator begin() const;

    std::vector<std::string>::const_iterator end() const;


signals:

    /*
     * When new values are inserted, or values are removed the indexes of some values change.
     * this signal lets you know when indexes have changed. Indexes below first_invalid_index
     * are gauranteed to still be valid.
     */
    void invalidated_from(int first_invalid_index);


private:

    std::string enum_name;

    std::vector<std::string> enum_values;


public:

    const char * const name;


};
