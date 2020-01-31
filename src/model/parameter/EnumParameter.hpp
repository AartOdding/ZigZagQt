#pragma once

#include <QObject>
#include "BaseParameter.hpp"
#include "Int64Component.hpp"



class EnumParameter : public BaseParameter
{
    Q_OBJECT

public:

    EnumParameter(BaseZigZagObject * parent, const QString& name, const std::vector<QString>& values, int value = 0);
    EnumParameter(BaseZigZagObject * parent, const QString& name, const std::vector<QString>& values, const QString& value);
    //EnumParameter(BaseZigZagObject * parent, const QString& name, std::initializer_list<QString> values, int value = 0);
    //EnumParameter(BaseZigZagObject * parent, const QString& name, std::initializer_list<QString> values, const QString& value);

    int getIndex() const;
    const QString& getValue() const;
    const std::vector<QString>& getPossibleValues() const;

    int indexOf(const QString& value) const;

    const QString& operator[](int index) const;

    std::vector<QString>::const_iterator begin() const;
    std::vector<QString>::const_iterator end() const;

public slots:

    void set(int index);
    void set(const QString& value);

    void addValue(const QString& value, int index = -1);

    bool removeValue(int index);
    bool removeValue(const QString& value);

signals:

    void enumValueAdded(const QString& addedValue, int index);
    void enumValueRemoved(const QString removedValue, int index);
    void enumValuesChanged(const std::vector<QString>& newValues);

private:

    Int64Component m_enumComponent;
    std::vector<QString> m_possibleValues;

};
