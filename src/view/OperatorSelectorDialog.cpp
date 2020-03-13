#include "OperatorSelectorDialog.hpp"

#include "view/Viewport.hpp"
#include "model/OperatorLibrary.hpp"
#include "application.h"
#include "model/BaseOperator.hpp"

#include "ui_librarydialogpanel.h"
#include <QComboBox>
#include <iostream>



OperatorSelectorDialog::OperatorSelectorDialog(QWidget* parent, int x, int y)
    : QDialog(parent, Qt::Popup),
      m_x(x),
      m_y(y)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui.setupUi(this);
    ui.accept_button->setDefault(true);

    auto library = activeOperatorLibrary();
    auto packages = library->packages();

    for (auto packageName : packages)
    {
        ui.filter->addItem(packageName);
    }

    if (!packages.empty())
    {
        auto ops = library->getPackage(packages[0]);

        for (auto op : ops)
        {
            ui.operator_list->addItem(op->name);
        }
    }

    ui.operator_list->setCurrentRow(0);
    ui.operator_list->setFocus();

    connect(ui.accept_button, &QPushButton::clicked, this, &OperatorSelectorDialog::onAccept);
    connect(ui.cancel_button, &QPushButton::clicked, this, &OperatorSelectorDialog::onCancel);
    connect(ui.filter, &QComboBox::currentTextChanged, this, &OperatorSelectorDialog::onPackageChanged);
}


void OperatorSelectorDialog::onPackageChanged(const QString& newPackage)
{
    ui.operator_list->clear();

    for (auto op : activeOperatorLibrary()->getPackage(newPackage))
    {
        ui.operator_list->addItem(op->name);
    }
}


void OperatorSelectorDialog::onAccept()
{
    if (ui.operator_list->currentItem())
    {
        auto op = activeOperatorLibrary()->getOperator(
                    ui.filter->currentText(),
                    ui.operator_list->currentItem()->text());
        if (op)
        {
            emit operatorRequested(op, m_x, m_y);
        }
    }
    close();
}


void OperatorSelectorDialog::onCancel()
{
    close();
}
