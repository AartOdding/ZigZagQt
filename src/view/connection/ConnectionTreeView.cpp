#include <QGraphicsScene>
#include <QScrollBar>
#include <QApplication>

#include "view/connection/ConnectionTreeView.hpp"
#include "view/connection/ConnectionEditor.hpp"
#include "view/Viewport.hpp"
#include "view/operatorview.h"
#include "model/BaseOperator.hpp"
#include <iostream>



/*
 * Recursive function that will add BaseZigZagObject, BaseParameters and
 * BaseComponents, to a QTreeWidgetItem.
 */
static void addToTree(BaseZigZagObject* object, QTreeWidgetItem* currentTreeItem)
{
    auto parameter = qobject_cast<BaseParameter*>(object);
    auto childParameters = object->findChildren<BaseParameter*>(QString(), Qt::FindDirectChildrenOnly);
    QList<BaseComponent*> components;

    if (parameter)
    {
        components = parameter->getComponents();
    }

    QTreeWidgetItem * thisTreeItem = nullptr;

    if (parameter && childParameters.size() == 0 && components.size() == 1)
    {
        // If there is only one component and no other children add the component directly
        // instead of first adding the paramter and then the component.
        auto newItem = new QTreeWidgetItem(currentTreeItem, { object->objectName() } );
        newItem->setData(0, 201, QVariant::fromValue<BaseComponent*>(components.at(0)));
        currentTreeItem->addChild(newItem);
    }
    else if ((components.size() > 1) || childParameters.size() > 0)
    {
        thisTreeItem = new QTreeWidgetItem(currentTreeItem, { object->objectName() });
        thisTreeItem->setExpanded(true);
        thisTreeItem->setFlags(Qt::ItemIsEnabled); // No selectable flag!
        currentTreeItem->addChild(thisTreeItem);
    }

    if (components.size() > 1)
    {
        for (auto component : components)
        {
            auto newItem = new QTreeWidgetItem(thisTreeItem, { component->objectName() } );
            newItem->setData(0, 201, QVariant::fromValue<BaseComponent*>(component));
            thisTreeItem->addChild(newItem);
        }
    }

    for (auto child : childParameters)
    {
        addToTree(child, thisTreeItem);
    }
}



ConnectionTreeView::ConnectionTreeView(BaseZigZagObject * output, BaseZigZagObject * input, QWidget* parent)
    : QFrame(parent)
{
    m_treeWidgetsLayout.setMargin(0);
    m_treeWidgetsLayout.setSpacing(0);

    m_treeWidgetLeft.setFrameStyle(QFrame::NoFrame);
    m_treeWidgetLeft.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_treeWidgetLeft.setHeaderHidden(true);
    m_treeWidgetLeft.setColumnCount(1);
    m_treeWidgetLeft.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetLeft.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetLeft.setMinimumWidth(200);

    m_treeWidgetRight.setFrameStyle(QFrame::NoFrame);
    m_treeWidgetRight.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_treeWidgetRight.setHeaderHidden(true);
    m_treeWidgetRight.setColumnCount(1);
    m_treeWidgetRight.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetRight.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_treeWidgetRight.setMinimumWidth(200);

    m_treeWidgetsLayout.addWidget(m_treeWidgetLeft.verticalScrollBar());
    m_treeWidgetsLayout.addWidget(&m_treeWidgetLeft, 1);
    m_treeWidgetsLayout.addStretch(1);
    m_treeWidgetsLayout.addWidget(&m_treeWidgetRight, 1);
    m_treeWidgetsLayout.addWidget(m_treeWidgetRight.verticalScrollBar());

    if (output)
    {
        addToTree(output, m_treeWidgetLeft.invisibleRootItem());
    }
    if (input)
    {
        addToTree(input, m_treeWidgetRight.invisibleRootItem());
    }
}



BaseComponent* ConnectionTreeView::getSelectedInput() const
{
    auto selected = m_treeWidgetRight.currentItem();

    if (selected)
    {
        return selected->data(0, 201).value<BaseComponent*>();
    }
    return nullptr;
}



BaseComponent* ConnectionTreeView::getSelectedOutput() const
{
    auto selected = m_treeWidgetLeft.currentItem();

    if (selected)
    {
        return selected->data(0, 201).value<BaseComponent*>();
    }
    return nullptr;
}


