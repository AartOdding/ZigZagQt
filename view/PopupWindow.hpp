#pragma once

#include <QWidget>
#include <QVBoxLayout>


class PopupWindow : public QWidget
{
    Q_OBJECT

public:

    explicit PopupWindow(QWidget* presentedWidget, QWidget *parent = nullptr);

    QWidget * presentedWidget() const;

public slots:

    void setPresentedWidget(QWidget * widget);

protected:

    bool eventFilter(QObject *, QEvent * event);

private:

    QVBoxLayout m_layout{ this };
    QWidget* m_presentedWidget = nullptr;

};
