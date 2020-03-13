#pragma once

#include <vector>

#include <QDialog>

#include "ui_librarydialogpanel.h"


struct DataTypeDescription;
struct OperatorKind;


class OperatorSelectorDialog : public QDialog
{
    Q_OBJECT

public:

    OperatorSelectorDialog(QWidget* parent, int x, int y);


signals:

    void operatorRequested(const OperatorKind* op_type, int x, int y);


public slots:

    void onPackageChanged(const QString& new_library);

    void onAccept();

    void onCancel();


private:

    Ui::OperatorSelectorForm ui;

    int m_x;
    int m_y;

};
