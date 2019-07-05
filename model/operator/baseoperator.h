#pragma once

#include <array>

#include <QList>
#include <QObject>
#include <QVector>
#include <QPointer>
#include <QOpenGLFunctions_4_5_Core>

class ProgramModel;





class BaseOperator : public QObject
{
    Q_OBJECT

public:

    BaseOperator(ProgramModel& model);

    virtual ~BaseOperator();

    virtual void render() = 0;
    virtual bool can_render() = 0;


    BaseOperator * get_input(int index);
    int get_num_inputs() const;
    int get_num_used_inputs() const;
    int get_num_output_users() const;


    int get_position_x() const;
    int get_position_y() const;


    //Policy get_pixel_type_policy() const;
    //Policy get_resolution_policy() const;

public slots:

    void set_input(int index, BaseOperator* operator_);
    void set_num_inputs(int num_accepted_inputs);

    void set_position(int pos_x, int pos_y);

    //void set_resolution_policy(Policy policy);
    //void set_pixel_type_policy(Policy policy);

signals:

    void input_changed(int index);
    void num_inputs_changed(int new_num_inputs);
    void position_changed(int pos_x, int pos_y);

    //void resolution_policy_changed(Policy new_policy);
    //void pixel_type_policy_changed(Policy new_policy);

protected:

    QVector<QPointer<BaseOperator>> inputs;
    QVector<QPointer<BaseOperator>> output_users;

    ProgramModel& model;


    int position_x = 0;
    int position_y = 0;

    //Policy resolution_policy = Policy::CUSTOM;
    //Policy pixel_type_policy = Policy::CUSTOM;



};
