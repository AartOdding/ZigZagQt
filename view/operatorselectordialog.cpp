#include "operatorselectordialog.h"

#include "view/viewport.h"
#include "model/librarymodel.h"
#include "application.h"

#include "ui_librarydialogpanel.h"


OperatorSelectorDialog::OperatorSelectorDialog(Viewport* vp)
{
    MontSerrat.setPixelSize(14);

    ui.setupUi(this);
    ui.label_filter_input->setFont(MontSerrat);
    ui.label_filter_output->setFont(MontSerrat);

    ui.input_filter->addItem("No Filter");
    ui.output_filter->addItem("No Filter");


    //setAutoFillBackground(true);
    //setMinimumSize(100, 100);

    //auto lib = application::library_model();

}


