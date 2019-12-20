#include "view/connection/ConnectionEditor.hpp"
#include "view/viewport.h"
#include "view/operatorview.h"
#include "model/baseoperator.h"

#include <QGraphicsScene>
#include <iostream>


ConnectionEditor::ConnectionEditor(Viewport* viewport)
    : m_viewport(viewport),
      m_layout(this),
      m_treeWidget(this)
{
    Q_ASSERT(viewport);

#ifdef Q_OS_MAC
    setParent(nullptr);
    setWindowFlags(Qt::WindowStaysOnTopHint);
#else
    setParent(viewport);
    setWindowFlags(Qt::Window |Qt::CustomizeWindowHint | Qt::WindowTitleHint
                   /*| Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint*/);
#endif

    m_layout.setMargin(0);
    m_layout.setSpacing(0);
    m_layout.addWidget(&m_treeWidget);

    show();
}



void ConnectionEditor::setScene(QGraphicsScene* model)
{
    if (m_model != model)
    {
        if (m_model != nullptr)
        {
            disconnect(m_model, &QGraphicsScene::selectionChanged, this, &ConnectionEditor::onSelectionChanged);
        }
        if (model)
        {
            m_model = model;
            connect(m_model, &QGraphicsScene::selectionChanged, this, &ConnectionEditor::onSelectionChanged);
        }
    }
}



void ConnectionEditor::onSelectionChanged()
{
    auto selectedItems = m_model->selectedItems();

    if (selectedItems.size() == 1)
    {
        auto selected = dynamic_cast<OperatorView*>(selectedItems[0]);

        if (selected)
        {
            auto op = &selected->operator_model;

            m_treeWidget.clear();
            m_treeWidget.setColumnCount(1);

            addToTree(op, m_treeWidget.invisibleRootItem());

            //for (auto p : op->findChildren<BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly))
            //{
            //    m_treeWidget.insertTopLevelItem(index++, new QTreeWidgetItem({ p->objectName() }));
            //}

            //m_treeWidget.addTopLevelItem
        }
    }
}



void ConnectionEditor::addToTree(BaseZigZagObject* object, QTreeWidgetItem* treeItem)
{
    auto parameter = qobject_cast<BaseParameter*>(object);
    auto children = object->findChildren<BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly);

    QTreeWidgetItem * newTreeItem = nullptr;

    if (parameter || children.size() != 0)
    {
        newTreeItem = new QTreeWidgetItem(treeItem, { object->objectName() });
        treeItem->addChild(newTreeItem);
    }


    auto components = parameter->getComponents();

    if (children.size() == 0)
    {

        return;
    }
    else
    {
        auto newTreeItem = new QTreeWidgetItem(treeItem, { object->objectName() });
        treeItem->addChild(newTreeItem);

        for (auto child : children)
        {
            addToTree(child, newTreeItem);
        }
    }
}
