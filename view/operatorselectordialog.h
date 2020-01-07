#pragma once

#include <vector>

#include <QFont>
#include <QDialog>
#include <QObject>

#include "ui_librarydialogpanel.h"


class Viewport;
struct DataTypeDescription;
struct OperatorDescription;


class OperatorSelectorDialog : public QDialog
{
    Q_OBJECT

public:

    OperatorSelectorDialog(Viewport* viewport, const QPointF& where);


signals:

    void operator_requested(const OperatorDescription* op_type, const QPointF& where);


public slots:

    //void build_list(int);

    void on_different_library_selected(const QString& new_library);

    void accept_clicked();

    void cancel_clicked();


private:

    Ui::OperatorSelectorForm ui;

    QFont MontSerrat{ "MontSerrat" };
    QFont OpenSans{ "Open Sans" };

    QPointF operator_position;

    // Used to quickly translate from combobox index to corresponding DataTypeInfo.
    std::vector<const DataTypeDescription*> data_types;


};
