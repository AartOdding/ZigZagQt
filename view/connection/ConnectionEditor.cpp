#include "view/connection/ConnectionEditor.hpp"
#include "view/viewport.h"
#include "view/operatorview.h"
#include "model/baseoperator.h"

#include <QGraphicsScene>
#include <QScrollBar>
#include <iostream>


ConnectionEditor::ConnectionEditor(Viewport* viewport)
    : m_viewport(viewport)
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

    m_connectButton.setText(QStringLiteral("Connect"));
    m_disconnectButton.setText(QStringLiteral("Disconnect"));

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

    m_mainLayout.setMargin(9);
    m_mainLayout.setSpacing(15);
    m_buttonsLayout.setMargin(0);
    m_buttonsLayout.setSpacing(8);
    m_treeWidgetsLayout.setMargin(0);
    m_treeWidgetsLayout.setSpacing(0);

    m_buttonsLayout.addStretch();
    m_buttonsLayout.addWidget(&m_connectButton);
    m_buttonsLayout.addWidget(&m_disconnectButton);
    m_buttonsLayout.addStretch();

    m_treeWidgetsLayout.addWidget(m_treeWidgetLeft.verticalScrollBar());
    m_treeWidgetsLayout.addStretch(1);
    m_treeWidgetsLayout.addWidget(&m_treeWidgetLeft);
    m_treeWidgetsLayout.addStretch(3);
    m_treeWidgetsLayout.addWidget(&m_treeWidgetRight);
    m_treeWidgetsLayout.addStretch(1);
    m_treeWidgetsLayout.addWidget(m_treeWidgetRight.verticalScrollBar());

    m_mainLayout.addLayout(&m_buttonsLayout);
    m_mainLayout.addLayout(&m_treeWidgetsLayout);
    setLayout(&m_mainLayout);

    setStyleSheet(QStringLiteral("ConnectionEditor { background-color:rgb(42, 42, 42) }"));

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

            m_treeWidgetLeft.clear();
            m_treeWidgetRight.clear();

            addToTree(op, m_treeWidgetLeft.invisibleRootItem());
            addToTree(op, m_treeWidgetRight.invisibleRootItem());
        }
    }
}



void ConnectionEditor::addToTree(BaseZigZagObject* object, QTreeWidgetItem* currentTreeItem)
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
