#include "TextComponent.hpp"




TextComponent::TextComponent(BaseParameter * parameter)
    : BaseComponent(parameter)
{

}



TextComponent::TextComponent(BaseParameter * parameter, const QString& text)
    : BaseComponent(parameter),
      m_text(text)
{

}



bool TextComponent::update()
{
    if (m_newTextPending)
    {
        m_text = m_pendingText;
        emit valueChanged(m_text);
        return true;
    }
    return false;
}



const QString& TextComponent::getText()
{
    return m_text;
}



bool TextComponent::setText(const QString& text, bool overwritePendingChanges)
{
    if (overwritePendingChanges)
    {
        m_newTextPending = false;
    }

    if (m_text != text)
    {
        m_text = text;
        emit valueChanged(m_text);
        return true;
    }
    return false;
}



void TextComponent::change(int64_t value)
{
    m_pendingText = QString::number(value);
    m_newTextPending = m_text != m_pendingText;
}



void TextComponent::change(double value)
{
    m_pendingText = QString::number(value, 'f', 6);
    m_newTextPending = m_text != m_pendingText;
}



void TextComponent::change(const QString& text)
{
    m_pendingText = text;
    m_newTextPending = m_text != m_pendingText;
}
