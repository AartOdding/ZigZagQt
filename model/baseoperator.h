#pragma once

#include <array>

#include <QList>
#include <QObject>
#include <QVector>
#include <QPointer>


class ProgramModel;
class BaseDataBlock;
class BaseParameter;
class DataBlockInput;




class BaseOperator : public QObject
{
    Q_OBJECT

    friend class MoveCommand;
    friend class ProgramModel;

public:

    BaseOperator();

    virtual ~BaseOperator();

    virtual void run() = 0;

    virtual std::vector<DataBlockInput*> get_inputs() = 0;
    virtual std::vector<BaseDataBlock*> get_outputs() = 0;
    virtual std::vector<BaseParameter*> get_parameters() = 0;

    /*
    BaseOperator * get_input(int index);
    int get_num_inputs() const;
    int get_num_used_inputs() const;
    int get_num_output_users() const;
    */

    int get_position_x() const;
    int get_position_y() const;


    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }



public slots:

    /*
    void set_input(int index, BaseOperator* operator_);
    void set_num_inputs(int num_accepted_inputs);
    */

    void move_to(int x, int y);


signals:

    //void input_changed(int index);
    //void num_inputs_changed(int new_num_inputs);
    void position_changed(int pos_x, int pos_y);

protected:


    void refresh_inputs();

    void refresh_outputs();


private:

    void set_position(int pos_x, int pos_y);

    std::vector<DataBlockInput*> inputs;
    std::vector<BaseDataBlock*> outputs;

    int position_x = 0;
    int position_y = 0;

};
