#pragma once

#include <QWidget>
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
    QVBoxLayout m_layout;
    QTreeWidget m_treeWidget;

    QGraphicsScene * m_model = nullptr;

};
