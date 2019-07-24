#pragma once

#include <vector>
#include <QObject>


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

    // Cannot be const because they might have to cache the data.
    const std::vector<DataBlockInput*>& inputs();
    const std::vector<BaseDataBlock*>& outputs();
    const std::vector<BaseParameter*>& parameters();

    int get_position_x() const;
    int get_position_y() const;


public slots:

    // Undoable action.
    void remove();

    // Undoable action.
    void move_to(int x, int y);

    void refresh_inputs();
    void refresh_outputs();
    void refresh_parameters();


signals:

    void inputs_modified();
    void outputs_modified();
    void parameters_modified();

    void position_changed(int pos_x, int pos_y);


protected:

    virtual std::vector<DataBlockInput*> provide_inputs() = 0;
    virtual std::vector<BaseDataBlock*>  provide_outputs() = 0;
    virtual std::vector<BaseParameter*>  provide_parameters() = 0;

    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquire_resources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void release_resources() { }


private:

    void set_position(int pos_x, int pos_y);



    std::vector<DataBlockInput*> cached_inputs;
    std::vector<BaseDataBlock*> cached_outputs;
    std::vector<BaseParameter*> cached_parameters;

    bool inputs_cached = false;
    bool outputs_cached = false;
    bool parameters_cached = false;

    int position_x = 0;
    int position_y = 0;

};
