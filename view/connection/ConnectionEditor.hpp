#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>

class BaseZigZagObject;
class Viewport;
class QGraphicsScene;



class ConnectionEditor : public QWidget
{
    Q_OBJECT

public:

    explicit ConnectionEditor(Viewport* viewport);

    void setScene(QGraphicsScene* scene);

public slots:

    void onSelectionChanged();

signals:


private:

    static void addToTree(BaseZigZagObject* object, QTreeWidgetItem* treeItem);

    Viewport* m_viewport = nullptr;
    QGraphicsScene * m_model = nullptr;

    QVBoxLayout m_mainLayout{ this };

    QHBoxLayout m_buttonsLayout{ this };
    QPushButton m_connectButton{ this };
    QPushButton m_disconnectButton{ this };

    QHBoxLayout m_treeWidgetsLayout{ this };
    QTreeWidget m_treeWidgetLeft{ this };
    QTreeWidget m_treeWidgetRight{ this };

};
