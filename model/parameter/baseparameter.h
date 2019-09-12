#pragma once

#include <vector>
#include <QMetaType>



class ParameterOwner;


enum class ParameterType : short
{
    Int,
    Int2,
    Int3,
    Int4,
    Enum,
    Float,
    Float2,
    Float3,
    Float4,
    Transform2D,
    Transform3D,
    ParameterRow,
};


enum class ParameterFamily : short
{
    ArithmeticParameter,
    TextualParameter,
    ReferenceParameter,
    DummyParameter // Dummy parameters are all parameters that cannot import / export.
};



class BaseParameter
{
public:

    BaseParameter(ParameterOwner* owner, ParameterType type, ParameterFamily family, const char * name);

    virtual ~BaseParameter();

    const char * name() const;
    ParameterType type() const;
    ParameterFamily family() const;
    ParameterOwner * owner() const;

    // Also flags the parameter owner as changed!
    void flag_changed();
    void reset_changed_flag();
    bool has_changed() const;

    bool is_importing() const;
    BaseParameter * get_import() const;
    const std::vector<BaseParameter *> get_exports() const;


    // Undoable action
    void add_import(BaseParameter * import);

    // Undoable action
    void remove_import();

    // Default implementation will check if family is the same and it's not a dummy.
    virtual bool compatible_with(const BaseParameter* other) const;


protected:

    virtual void import_flagged_changed() { }


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    ParameterOwner * const m_owner;
    const char * const m_name;
    BaseParameter * m_import = nullptr;
    std::vector<BaseParameter *> m_exports;

    const ParameterType m_type;
    const ParameterFamily m_family;

    bool m_changed = false;

};

Q_DECLARE_METATYPE(BaseParameter*);



class ArithmeticParameter : public BaseParameter
{
public:

    ArithmeticParameter(ParameterOwner* owner, ParameterType type, const char * name)
        : BaseParameter(owner, type, ParameterFamily::ArithmeticParameter, name)
    { }

    bool minimal_updates() const
    {
        return m_minimal_updates;
    }

    void set_minimal_updates(bool value)
    {
        m_minimal_updates = value;
    }

    bool rollover() const
    {
        return m_rollover;
    }

    void set_rollover(bool value)
    {
        m_rollover = value;
    }

    // Needs to be reimplemented to provide the most meaningful value at said index.
    virtual int32_t int_at(unsigned index) const = 0;

    // Needs to be reimplemented to provide the most meaningful value at said index.
    virtual double double_at(unsigned index) const = 0;


protected:

    bool is_int_based() const
    {
        return (type() == ParameterType::Int  || type() == ParameterType::Int2
             || type() == ParameterType::Int3 || type() == ParameterType::Int4
             || type() == ParameterType::Enum);
    }

    bool is_float_based() const
    {
        return !is_int_based();
    }


private:

    bool m_rollover = false;
    bool m_minimal_updates = false;

};



