#include <QGraphicsScene>
#include <QScrollBar>
#include <QApplication>

#include "view/connection/ConnectionTreeView.hpp"
#include "view/connection/ConnectionEditor.hpp"
#include "view/viewport.h"
#include "view/operatorview.h"
#include "model/baseoperator.h"
#include <iostream>



ConnectionTreeView::ConnectionTreeView(QWidget* parent)
    : QFrame(parent)
{
    m_treeWidgetsLayout.setMargin(0);
    m_treeWidgetsLayout.setSpacing(0);

    m_treeWidgetLeft.setFrameStyle(QFrame::NoFrame);
    m_treeWidgetLeft.setHeaderHidden(true);
    m_treeWidgetLeft.setColumnCount(1);
    m_treeWidgetLeft.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetLeft.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetLeft.setMinimumWidth(400);
    m_treeWidgetLeft.setMaximumWidth(400);

    m_treeWidgetRight.setFrameStyle(QFrame::NoFrame);
    m_treeWidgetRight.setHeaderHidden(true);
    m_treeWidgetRight.setColumnCount(1);
    m_treeWidgetRight.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetRight.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetRight.setMinimumWidth(400);
    m_treeWidgetRight.setMaximumWidth(400);

    m_treeWidgetsLayout.addWidget(m_treeWidgetLeft.verticalScrollBar());
    m_treeWidgetsLayout.addStretch(1);
    m_treeWidgetsLayout.addWidget(&m_treeWidgetLeft);
    m_treeWidgetsLayout.addStretch(3);
    m_treeWidgetsLayout.addWidget(&m_treeWidgetRight);
    m_treeWidgetsLayout.addStretch(1);
    m_treeWidgetsLayout.addWidget(m_treeWidgetRight.verticalScrollBar());

    setStyleSheet(QStringLiteral("ConnectionTreeView { background-color:rgb(42, 42, 42); border: 1px solid black; }"));

}



void ConnectionTreeView::onSelectionChanged()
{
    auto selectedItems = m_model->selectedItems();

    if (selectedItems.size() == 1)
    {
        auto selected = dynamic_cast<OperatorView*>(selectedItems[0]);

        if (selected)
        {
            auto op = &selected->operator_model;

            m_treeWidgetLeft.clear();
            m_treeWidgetRight.clear();

            addToTree(op, m_treeWidgetLeft.invisibleRootItem());
            addToTree(op, m_treeWidgetRight.invisibleRootItem());
        }
    }
}



void ConnectionTreeView::setScene(QGraphicsScene* model)
{
    if (m_model != model)
    {
        if (m_model != nullptr)
        {
            disconnect(m_model, &QGraphicsScene::selectionChanged, this, &ConnectionTreeView::onSelectionChanged);
        }
        if (model)
        {
            m_model = model;
            connect(m_model, &QGraphicsScene::selectionChanged, this, &ConnectionTreeView::onSelectionChanged);
        }
    }
}



void ConnectionTreeView::wheelEvent(QWheelEvent *event)
{
    if (event != lastForwardedWheelEvent)
    {
        lastForwardedWheelEvent = event;

        if (event->x() < width() / 2)
        {
            //m_treeWidgetLeft.sendWheelEvent(event);
        }
        else
        {
            //m_treeWidgetRight.sendWheelEvent(event);
        }
    }
}



void ConnectionTreeView::addToTree(BaseZigZagObject* object, QTreeWidgetItem* currentTreeItem)
{
    auto parameter = qobject_cast<BaseParameter*>(object);
    auto children = object->findChildren<BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly);
    const std::vector<BaseComponent*> * components = nullptr;

    if (parameter)
    {
        components = &parameter->getComponents();
    }

    QTreeWidgetItem * thisTreeItem = nullptr;

    if (parameter && components && children.size() == 0 && components->size() == 1)
    {
        // If there is only one component and no other children add the component directly
        // instead of first adding the paramter and then the component.
        currentTreeItem->addChild(new QTreeWidgetItem(currentTreeItem, { object->objectName() } ));
    }
    else if ((components && components->size() > 1) || children.size() > 0)
    {
        thisTreeItem = new QTreeWidgetItem(currentTreeItem, { object->objectName() });
        thisTreeItem->setExpanded(true);
        thisTreeItem->setFlags(Qt::ItemIsEnabled); // No selectable flag!
        currentTreeItem->addChild(thisTreeItem);
    }

    if (components && components->size() > 1)
    {
        for (auto component : *components)
        {
            thisTreeItem->addChild(new QTreeWidgetItem(thisTreeItem, { component->objectName() } ));
        }
    }

    for (auto child : children)
    {
        addToTree(child, thisTreeItem);
    }
}
