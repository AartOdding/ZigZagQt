#pragma once

#include <vector>
#include <QMetaType>



class ParameterOwner;


enum class ParameterType
{
    ArithmeticParametersBegin,
        Int,
        Int2,
        Int3,
        Int4,
        Float,
        Float2,
        Float3,
        Float4,
        Enum,
        Transform2D,
        Transform3D,
    ArithmeticParametersEnd,

    TextualParametersBegin,
        // Add textual parameter types here.
    TextualParametersEnd,

    ReferenceParametersBegin,
        // Add reference parameter types here.
    ReferenceParametersEnd,

    DummyParametersBegin,
        ParameterRow,
    DummyParametersEnd
};


enum class ParameterFamily
{
    ArithmeticParameter,
    TextualParameter,
    ReferenceParameter,
    DummyParameter // Dummy parameters are all parameters that cannot import / export.
};


constexpr ParameterFamily family_for(ParameterType type)
{
    if (static_cast<int>(type) > static_cast<int>(ParameterType::ArithmeticParametersBegin)
        && static_cast<int>(type) < static_cast<int>(ParameterType::ArithmeticParametersEnd))
    {
        return ParameterFamily::ArithmeticParameter;
    }
    else if (static_cast<int>(type) > static_cast<int>(ParameterType::TextualParametersBegin)
        && static_cast<int>(type) < static_cast<int>(ParameterType::TextualParametersEnd))
    {
        return ParameterFamily::TextualParameter;
    }
    else if (static_cast<int>(type) > static_cast<int>(ParameterType::ReferenceParametersBegin)
        && static_cast<int>(type) < static_cast<int>(ParameterType::ReferenceParametersEnd))
    {
        return ParameterFamily::ReferenceParameter;
    }
    else
    {
        return ParameterFamily::DummyParameter;
    }
}



class BaseParameter
{
public:

    BaseParameter(ParameterOwner* owner, ParameterType type, const char * name);

    virtual ~BaseParameter();


    const char * name() const;

    ParameterType type() const;

    ParameterFamily family() const;

    ParameterOwner * owner() const;


    bool compatible_with(const BaseParameter* other) const;


    // Also flags the parameter owner as changed!
    void flag_changed();

    void reset_changed_flag();

    bool has_changed() const;


    bool is_importing() const;

    BaseParameter * get_import() const;

    const std::vector<BaseParameter *> get_exports() const;


public: // slots?

    // Undoable action
    void add_import(BaseParameter * import);

    // Undoable action
    void remove_import();


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    ParameterOwner * const m_owner;
    const char * const m_name;

    BaseParameter * m_import = nullptr;
    std::vector<BaseParameter *> m_exports;

    const ParameterType m_type;
    bool m_changed = false;

};

Q_DECLARE_METATYPE(BaseParameter*);



class ArithmeticParameter : public BaseParameter
{
public:

    using BaseParameter::BaseParameter;


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

private:

    bool m_rollover = false;

    bool m_minimal_updates = false;
};



