#include "ParameterFlags.hpp"



unsigned long ParameterFlags::m_defaultFlags
    = (1 << static_cast<int>(ParameterFlag::CanExport))
    | (1 << static_cast<int>(ParameterFlag::CanImport))
    | (1 << static_cast<int>(ParameterFlag::IsVisible))
    | (1 << static_cast<int>(ParameterFlag::IsEditable))
    | (1 << static_cast<int>(ParameterFlag::UpdatesWhileEditing))
    | (1 << static_cast<int>(ParameterFlag::IsDisabledWhileImporting));


bool ParameterFlags::getFlag(ParameterFlag flag) const
{
    return m_flags.test(static_cast<unsigned long>(flag));
}


void ParameterFlags::setFlag(ParameterFlag flag, bool value)
{
    m_flags.set(static_cast<unsigned long>(flag), value);
}


void ParameterFlags::operator=(quint32 value)
{
    m_flags = std::bitset<32>(value);
}


ParameterFlags::operator quint32() const
{
    return static_cast<quint32>(m_flags.to_ulong());
}
