#pragma once


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
    Enum,
    ParameterRow
};



class BaseParameter
{
public:

    BaseParameter(ParameterOwner& owner, ParameterType type, const char * name);
    BaseParameter(ParameterOwner* owner, ParameterType type, const char * name);
    virtual ~BaseParameter();

    bool minimal_updates() const;
    void set_minimal_updates(bool value);

    bool rollover() const;      // Maybe move to the arithmetic parameter classes?
    void set_rollover(bool value);

    const char * name() const;
    ParameterType type() const;
    ParameterOwner * owner() const;

    // Also flags the parameter owner as changed!
    void flag_changed();
    void reset_changed_flag();
    bool has_changed() const;


private:

    bool m_changed = false;
    bool m_minimal_updates = false;
    bool m_rollover = false;

    ParameterOwner * const m_owner;

    const ParameterType m_type;

    const char * const m_name;


};

