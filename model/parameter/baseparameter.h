#pragma once

#include <QObject>



enum class ParameterMode
{
    PASSTHROUGH, // Default: Parameter can be used as input and output.
    INPUT,
    OUTPUT
};




class BaseParameter : public QObject
{
    Q_OBJECT

public:

    BaseParameter(const char * parameter_type, ParameterMode mode = ParameterMode::PASSTHROUGH);

    ParameterMode get_mode() const;

    const char * const type_name;

protected:

    void propagate_changes()
    {
        emit has_changed();
    }

private:


    ParameterMode mode;

signals:

    void has_changed();


};
