#pragma once

#include <QObject>



class BaseTOP;
class ProgramModel;



class Library : public QObject
{
    Q_OBJECT

public:

    Library(QObject *parent = nullptr);

    BaseTOP* create(const QString& operator_type, ProgramModel& model);

signals:


public slots:


};
