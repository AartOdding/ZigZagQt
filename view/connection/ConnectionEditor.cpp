#include "view/connection/ConnectionEditor.hpp"
#include "view/viewport.h"
#include "view/operatorview.h"
#include "model/BaseOperator.hpp"

#include <QGraphicsScene>
#include <QScrollBar>
#include <iostream>



ConnectionEditor::ConnectionEditor(QWidget * parent)
    : ConnectionEditor(nullptr, nullptr, parent)
{
}



ConnectionEditor::ConnectionEditor(BaseZigZagObject * output, BaseZigZagObject * input, QWidget * parent)
    : m_connectionTreeView(output, input, this)
{
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

    connect(&m_connectButton, &QPushButton::pressed, this, &ConnectionEditor::connectButtonPressed);
    connect(&m_disconnectButton, &QPushButton::pressed, this, &ConnectionEditor::disconnectButtonPressed);
}



void ConnectionEditor::connectButtonPressed()
{
    auto output = m_connectionTreeView.getSelectedOutput();
    auto input = m_connectionTreeView.getSelectedInput();

    if (input && output)
    {
        if (!input->isImportingFrom(output))
        {
            input->startImporting(output);
        }
    }
}



void ConnectionEditor::disconnectButtonPressed()
{
    auto output = m_connectionTreeView.getSelectedOutput();
    auto input = m_connectionTreeView.getSelectedInput();

    if (input && output)
    {
        if (input->isImportingFrom(output))
        {
            input->stopImporting();
        }
    }
}
