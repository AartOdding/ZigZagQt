#pragma once

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>

#include "view/connection/ConnectionTreeView.hpp"

class BaseZigZagObject;
class Viewport;
class QGraphicsScene;



class ConnectionEditor : public QWidget
{
    Q_OBJECT

public:

    explicit ConnectionEditor(QWidget * parent = nullptr);

    ConnectionEditor(BaseZigZagObject * output, BaseZigZagObject * input, QWidget * parent = nullptr);

public slots:

    void connectButtonPressed();

    void disconnectButtonPressed();

private:

    QVBoxLayout m_mainLayout{ this };

    QHBoxLayout m_buttonsLayout;
    QPushButton m_connectButton{ this };
    QPushButton m_disconnectButton{ this };

    ConnectionTreeView m_connectionTreeView;

};
