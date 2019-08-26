#pragma once

#include <QObject>







namespace parameter
{

    class ParameterOwner;


    enum class ParameterType
    {
        Int,
        Int2,
        Int3,
        Int4,
        Float,
        Float2,
        Float3,
        Float4,
        Enum
    };


    enum class UpdateMode
    {
        AllUpdates,
        NecessaryUpdates
    };

    class BaseParameter : public QObject
    {
        Q_OBJECT

    public:

        BaseParameter(ParameterOwner* owner, ParameterType type, const char * name);


        UpdateMode update_mode() const;

        void set_update_mode(const UpdateMode& mode);


        ParameterOwner * const owner;

        const ParameterType type;

        const char * const name;


    protected:

        void flag_changed()
        {
            emit value_changed();
        }


    signals:

        void value_changed();


    private:

        UpdateMode m_update_mode = UpdateMode::AllUpdates;


    };


}
