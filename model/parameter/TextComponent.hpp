#pragma once

#include "BaseComponent.hpp"



class TextComponent : public BaseComponent
{
    Q_OBJECT

public:

    TextComponent(BaseParameter * parameter);
    TextComponent(BaseParameter * parameter, const QString& text);

    bool update() override;

    const QString& getText();

    virtual void loadState(const QVariantMap&) override;
    virtual QVariantMap storeState() const override;

public slots:

    // Will return true if the component's value changed.
    bool setText(const QString& text, bool overwritePendingChanges = true);

    void change(int64_t value) override;
    void change(double value) override;
    void change(const QString& value) override;

private:

    QString m_text;
    QString m_pendingText;
    bool m_newTextPending = false;

};
