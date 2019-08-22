#pragma once

#include <vector>

#include <QFont>
#include <QDialog>

#include "ui_librarydialogpanel.h"


class Viewport;
class DataTypeInfo;
class OperatorTypeInfo;


class OperatorSelectorDialog : public QDialog
{
    Q_OBJECT

public:

    OperatorSelectorDialog(Viewport* viewport, const QPointF& where);


signals:

    void operator_requested(const OperatorTypeInfo* op_type, const QPointF& where);


public slots:

    //void build_list(int);

    void accept_clicked();

    void cancel_clicked();


private:

    Ui::OperatorSelectorForm ui;

    QFont MontSerrat{ "MontSerrat" };

    QPointF operator_position;

    // Used to quickly translate from combobox index to corresponding DataTypeInfo.
    std::vector<const DataTypeInfo*> data_types;


};
