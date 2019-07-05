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

    BaseParameter(ParameterMode mode_ = ParameterMode::PASSTHROUGH)
        : mode(mode_)
    { }

    ParameterMode get_mode() const
    {
        return mode;
    }


protected:

    void apply_change()
    {
        emit has_changed();
    }

private:


    ParameterMode mode;

signals:

    void has_changed();


};
