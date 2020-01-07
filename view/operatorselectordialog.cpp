#include "operatorselectordialog.h"

#include "view/viewport.h"
#include "model/OperatorLibrary.hpp"
#include "application.h"
#include "model/BaseOperator.hpp"

#include "ui_librarydialogpanel.h"
#include <QComboBox>
#include <iostream>



OperatorSelectorDialog::OperatorSelectorDialog(Viewport* vp, const QPointF& where)
    : QDialog(vp, Qt::Popup),
      operator_position(where)
{
    MontSerrat.setPixelSize(14);
    OpenSans.setPixelSize(14);
    setAttribute(Qt::WA_DeleteOnClose);

    ui.setupUi(this);
    ui.filter->setFont(OpenSans);
    ui.accept_button->setFont(OpenSans);
    ui.cancel_button->setFont(OpenSans);
    ui.operator_list->setFont(MontSerrat);
    ui.accept_button->setDefault(true);

    auto library = OperatorLibrary::instance();

    auto packages = library->packages();

    for (auto packageName : packages)
    {
        ui.filter->addItem(packageName);
    }

    //ui.filter->setCurrentText("Texture");
    auto ops = library->getPackage("Control");

    for (auto op : ops)
    {
        ui.operator_list->addItem(op->name);
    }

    ui.operator_list->setCurrentRow(0);
    ui.operator_list->setFocus();

    connect(ui.accept_button, &QPushButton::clicked, this, &OperatorSelectorDialog::accept_clicked);
    connect(ui.cancel_button, &QPushButton::clicked, this, &OperatorSelectorDialog::cancel_clicked);
    connect(ui.filter, &QComboBox::currentTextChanged, this, &OperatorSelectorDialog::on_different_library_selected);
}


void OperatorSelectorDialog::on_different_library_selected(const QString& new_library)
{
    ui.operator_list->clear();
    auto name = new_library.toStdString();

    auto operators = OperatorLibrary::instance()->getPackage(name.c_str());
    for (auto op : operators)
    {
        ui.operator_list->addItem(op->name);
    }
}


void OperatorSelectorDialog::accept_clicked()
{
    if (ui.operator_list->currentItem())
    {
        auto op = OperatorLibrary::instance()->getOperator(
                    ui.filter->currentText(),
                    ui.operator_list->currentItem()->text());
        if (op)
        {
            emit operator_requested(op, operator_position);
        }
    }
    close();
}


void OperatorSelectorDialog::cancel_clicked()
{
    close();
}

/*
void OperatorSelectorDialog::build_list(int)
{
    // filtering the operators is hard for now, because then the inputs and outputs need
    // to be know to the OpeatorTypeInfo instance.
    //const DataTypeInfo* input_filter = data_types[ui.input_filter->currentIndex()];
    //const DataTypeInfo* output_filter = data_types[ui.output_filter->currentIndex()];


    //auto library = application::library_model();
}*/
