#pragma once

#include <QObject>



enum class ParameterMode
{
    PASSTHROUGH, // Default: Parameter can be used as input and output.
    INPUT,
    OUTPUT
};


enum class ParameterType
{
    INT,
    FLOAT,
    ENUM
};


class BaseParameter : public QObject
{
    Q_OBJECT

public:

    BaseParameter(ParameterType type, const char * name, ParameterMode mode = ParameterMode::PASSTHROUGH);

    const char * const name;
    const ParameterType type;
    const ParameterMode mode;


public slots:

    //virtual void input_changed();

protected:

    void propagate_changes()
    {
        emit has_changed();
    }



signals:

    void has_changed();


};
