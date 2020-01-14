#include "TextComponent.hpp"




TextComponent::TextComponent(BaseParameter * parameter, const QString& name)
    : BaseComponent(parameter, name)
{

}



TextComponent::TextComponent(BaseParameter * parameter, const QString& name, const QString& text)
    : BaseComponent(parameter, name),
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


void TextComponent::loadState(const QVariantMap& state)
{
    auto text = state.find(QStringLiteral("text"));
    auto pendingText = state.find(QStringLiteral("pendingText"));
    auto base = state.find(QStringLiteral("BaseComponent"));

    if (text != state.end())
    {
        m_text = text->toString();
    }
    if (pendingText != state.end())
    {
        m_newTextPending = true;
        m_pendingText = pendingText->toString();
    }
    if (base != state.end())
    {
        BaseComponent::loadState(base->toMap());
    }
}


QVariantMap TextComponent::storeState() const
{
    QVariantMap state;
    state.insert(QStringLiteral("text"), m_text);
    if (m_newTextPending)
    {
        state.insert(QStringLiteral("pendingText"), m_pendingText);
    }
    state.insert(QStringLiteral("BaseComponent"), BaseComponent::storeState());
    return state;
}
