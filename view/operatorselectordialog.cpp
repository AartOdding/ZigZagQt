#include "operatorselectordialog.h"

#include "view/viewport.h"
#include "model/librarymodel.h"
#include "application.h"

#include "ui_librarydialogpanel.h"

#include <iostream>



OperatorSelectorDialog::OperatorSelectorDialog(Viewport* vp, const QPointF& where)
    : QDialog(vp, Qt::Popup), operator_position(where)
{
    MontSerrat.setPixelSize(14);
    OpenSans.setPixelSize(14);
    setAttribute(Qt::WA_DeleteOnClose);

    ui.setupUi(this);
    ui.label_filter_input->setFont(MontSerrat);
    ui.label_filter_output->setFont(MontSerrat);
    ui.input_filter->setFont(OpenSans);
    ui.output_filter->setFont(OpenSans);
    ui.accept_button->setFont(OpenSans);
    ui.cancel_button->setFont(OpenSans);
    ui.operator_list->setFont(MontSerrat);
    ui.accept_button->setDefault(true);

    auto library = application::library_model();

    data_types.reserve(library->data_types().size());

    ui.input_filter->addItem("No Filter");
    ui.output_filter->addItem("No Filter");
    data_types.push_back(nullptr);

    for (const auto& [name, details] : library->data_types())
    {
        ui.input_filter->addItem(name.c_str());
        ui.output_filter->addItem(name.c_str());
        data_types.push_back(details);
    }

    for (const auto& [name, details] : library->operators())
    {
        ui.operator_list->addItem(name.c_str());
    }

    ui.operator_list->setCurrentRow(0);
    ui.operator_list->setFocus();

    connect(ui.accept_button, &QPushButton::clicked, this, &OperatorSelectorDialog::accept_clicked);
    connect(ui.cancel_button, &QPushButton::clicked, this, &OperatorSelectorDialog::cancel_clicked);
}


void OperatorSelectorDialog::accept_clicked()
{
    auto current = ui.operator_list->currentItem()->text().toStdString();
    auto details = application::library_model()->operators().at(current);
    emit operator_requested(details, operator_position);
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
