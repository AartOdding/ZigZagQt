#pragma once

#include "BaseComponent.hpp"



class TextComponent : public BaseComponent
{
    Q_OBJECT

public:

    TextComponent(BaseParameter * parameter, const QString& name);
    TextComponent(BaseParameter * parameter, const QString& name, const QString& text);

    bool update() override;

    const QString& getText();

    virtual void loadState(const QVariantMap&) override;
    virtual QVariantMap storeState() const override;

public slots:

    // Will return true if the component's value changed.
    bool setText(const QString& text, bool overwritePendingChanges = true);

    void importChange(int64_t value) override;
    void importChange(double value) override;
    void importChange(const QString& value) override;

private:

    QString m_text;
    QString m_pendingText;
    bool m_newTextPending = false;

};
