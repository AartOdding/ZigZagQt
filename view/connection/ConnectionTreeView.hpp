#pragma once

#include <QFrame>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QWheelEvent>

class BaseZigZagObject;
class Viewport;
class QGraphicsScene;



class ConnectionTreeWidget : public QTreeWidget
{
public:

    using QTreeWidget::QTreeWidget;

    void sendWheelEvent(QWheelEvent *event)
    {
        wheelEvent(event);
        //event->accept();
    }

protected:

    void wheelEvent(QWheelEvent *event) override
    {
        QTreeView::wheelEvent(event);
        //event->accept();
    }

};


class ConnectionTreeView : public QFrame
{
    Q_OBJECT

public:

    ConnectionTreeView(QWidget* parent);

    void setScene(QGraphicsScene* scene);

public slots:

    void onSelectionChanged();

protected:

    void wheelEvent(QWheelEvent *event) override;

private:

    static void addToTree(BaseZigZagObject* object, QTreeWidgetItem* treeItem);

    QGraphicsScene * m_model = nullptr;

    QHBoxLayout m_treeWidgetsLayout{ this };
    ConnectionTreeWidget m_treeWidgetLeft{ this };
    ConnectionTreeWidget m_treeWidgetRight{ this };

    QWheelEvent* lastForwardedWheelEvent = nullptr;

};

