#pragma once

#include <vector>
#include <QStringView>
#include <QObject>



class BaseParameter;



class BaseDataBlock : public QObject
{
    Q_OBJECT

public:

    BaseDataBlock(QStringView data_type_name);

    virtual ~BaseDataBlock() { }

    virtual std::vector<BaseParameter*> get_parameters() = 0;


protected:

    void parameters_changed();


private:

    QStringView data_type_name;

signals:

    void parameters_modified();


};
