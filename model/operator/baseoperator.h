#pragma once

#include <array>

#include <QList>
#include <QObject>
#include <QVector>
#include <QPointer>
#include <QOpenGLFunctions_4_5_Core>

class ProgramModel;



enum class PixelType : int
{
    UINT8_SINGLE    = GL_R8,
    UINT8_DOUBLE    = GL_RG8,
    UINT8_TRIPLE    = GL_RGB8,
    UINT8_QUADRUPLE = GL_RGBA8,
    FLOAT_SINGLE    = GL_R32F,
    FLOAT_DOUBLE    = GL_RG32F,
    FLOAT_TRIPLE    = GL_RGB32F,
    FLOAT_QUADRUPLE = GL_RGBA32F
};


class BaseOperator : public QObject,
                     protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

public:

    BaseOperator(ProgramModel& model);

    virtual ~BaseOperator();

    virtual void render() = 0;
    virtual bool can_render() = 0;

    void prepare_render();

    BaseOperator * get_input(int index);
    int get_num_inputs() const;
    int get_num_used_inputs() const;
    int get_num_output_users() const;

    int get_resolution_x() const;
    int get_resolution_y() const;
    int get_position_x() const;
    int get_position_y() const;

    PixelType get_pixel_type() const;

    //Policy get_pixel_type_policy() const;
    //Policy get_resolution_policy() const;

public slots:

    void set_input(int index, BaseOperator* operator_);
    void set_num_inputs(int num_accepted_inputs);

    void set_resolution(int res_x, int res_y);
    void set_position(int pos_x, int pos_y);
    void set_pixel_type(PixelType type);
    //void set_resolution_policy(Policy policy);
    //void set_pixel_type_policy(Policy policy);

signals:

    void input_changed(int index);
    void num_inputs_changed(int new_num_inputs);
    void resolution_changed(int res_x, int res_y);
    void position_changed(int pos_x, int pos_y);
    void pixel_type_changed(PixelType new_type);
    //void resolution_policy_changed(Policy new_policy);
    //void pixel_type_policy_changed(Policy new_policy);

protected:

    QVector<QPointer<BaseOperator>> inputs;
    QVector<QPointer<BaseOperator>> output_users;

    ProgramModel& model;

    int resolution_x = 256;
    int resolution_y = 256;
    int position_x = 0;
    int position_y = 0;
    PixelType pixel_type = PixelType::UINT8_QUADRUPLE;

    //Policy resolution_policy = Policy::CUSTOM;
    //Policy pixel_type_policy = Policy::CUSTOM;

    GLuint frame_buffer_object;
    GLuint output_texture;

};
