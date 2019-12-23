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

    m_mainLayout.setMargin(9);
    m_mainLayout.setSpacing(9);
    m_buttonsLayout.setMargin(0);
    m_buttonsLayout.setSpacing(9);

    m_buttonsLayout.addStretch();
    m_buttonsLayout.addWidget(&m_connectButton);
    m_buttonsLayout.addWidget(&m_disconnectButton);
    m_buttonsLayout.addStretch();


    m_mainLayout.addLayout(&m_buttonsLayout);
    m_mainLayout.addWidget(&m_connectionTreeView);
    setLayout(&m_mainLayout);


    show();
}



void ConnectionEditor::setScene(QGraphicsScene* model)
{
    m_connectionTreeView.setScene(model);
}


