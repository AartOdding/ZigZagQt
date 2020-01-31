#pragma once

#include <QFrame>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QWheelEvent>

class BaseComponent;
class BaseZigZagObject;
class Viewport;
class QGraphicsScene;




class ConnectionTreeView : public QFrame
{
    Q_OBJECT

public:

    ConnectionTreeView(BaseZigZagObject * output, BaseZigZagObject * input, QWidget* parent);


    BaseComponent* getSelectedInput() const;
    BaseComponent* getSelectedOutput() const;


private:

    QHBoxLayout m_treeWidgetsLayout{ this };
    QTreeWidget m_treeWidgetLeft{ this };
    QTreeWidget m_treeWidgetRight{ this };

};

