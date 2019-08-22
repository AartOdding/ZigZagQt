#pragma once

#include <QObject>



class ParameterOwner;



enum class ParameterType
{
    Int,
    Float,
    Enum
};



class BaseParameter : public QObject
{
    Q_OBJECT

public:

    enum class UpdateMode
    {
        AllUpdates,
        NecessaryUpdates
    };

    BaseParameter(ParameterOwner* owner, ParameterType type, const char * name);


    UpdateMode update_mode() const;

    void set_update_mode(const UpdateMode& mode);


    ParameterOwner * const owner;

    const ParameterType type;

    const char * const name;


protected:

    void emit_changes()
    {
        emit value_changed();
    }


signals:

    void value_changed();


private:

    UpdateMode m_update_mode = UpdateMode::AllUpdates;


};
