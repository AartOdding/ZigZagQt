#pragma once

#include <QWidget>
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

    explicit ConnectionEditor(Viewport* viewport);

    void setScene(QGraphicsScene* scene);


private:

    Viewport* m_viewport = nullptr;
    QGraphicsScene * m_model = nullptr;

    QVBoxLayout m_mainLayout{ this };

    QHBoxLayout m_buttonsLayout{ this };
    QPushButton m_connectButton{ this };
    QPushButton m_disconnectButton{ this };

    ConnectionTreeView m_connectionTreeView{ this };

};
