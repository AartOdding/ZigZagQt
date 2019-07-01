#include "operator/basetop.h"
#include "programmodel.h"

#include <QPointer>



BaseTOP::BaseTOP(ProgramModel& model_)
    : QObject(&model_), model(model_)
{
    initializeOpenGLFunctions();

    glGenTextures(1, &output_texture);  // exception happens here
    glBindTexture(GL_TEXTURE_2D, output_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(pixel_type), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenFramebuffers(1, &frame_buffer_object);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, output_texture, 0);

    //input = nullptr;

    //inputs = QVector<QPointer<BaseTOP>>(6);

    for (int i = 0; i < 4; ++i)
    {
        //inputs.append(nullptr);
    }
}


BaseTOP::~BaseTOP()
{
    glDeleteFramebuffers(1, &frame_buffer_object);
    glDeleteTextures(1, &output_texture);
}


void BaseTOP::prepare_render()
{
    // Bind inputs to texture targets
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object);
}


BaseTOP * BaseTOP::get_input(int index)
{
    if (index >= 0 && index < inputs.size())
    {
        return inputs[index];
    }
    else
    {
        return nullptr;
    }
}

int BaseTOP::get_num_inputs() const
{
    return inputs.size();
}

int BaseTOP::get_num_used_inputs() const
{
    /*
    int count = 0;

    for (auto& input : inputs)
    {
        if (input)
        {
            ++count;
        }
    }
    */
    return inputs.size();
}

int BaseTOP::get_num_output_users() const
{
    int count = 0;
    for (auto& o : output_users)
    {
        if (o) ++count;
    }
    return count;
}

int BaseTOP::get_resolution_x() const
{
    return resolution_x;
}

int BaseTOP::get_resolution_y() const
{
    return resolution_y;
}

int BaseTOP::get_position_x() const
{
    return position_x;
}

int BaseTOP::get_position_y() const
{
    return position_y;
}

PixelType BaseTOP::get_pixel_type() const
{
    return pixel_type;
}

Policy BaseTOP::get_resolution_policy() const
{
    return resolution_policy;
}

Policy BaseTOP::get_pixel_type_policy() const
{
    return pixel_type_policy;
}


// SLOTS

void BaseTOP::set_input(int index, BaseTOP* operator_)
{
    /*
    if (index >= 0 && index != static_cast<int>(inputs.size()))
    {
        if (inputs[index] != operator_)
        {
            if (inputs[index]) // First properly remove old connection
            {
                inputs[index]->output_users.removeOne(this);
            }

            inputs[index] = operator_;

            if (operator_)
            {
                operator_->output_users.append(this);
            }
            emit input_changed(index);
        }
    }
    */
}

void BaseTOP::set_num_inputs(int new_num_inputs)
{
    if (new_num_inputs >= 0 && new_num_inputs != inputs.size())
    {
        inputs.resize(new_num_inputs);
        emit num_inputs_changed(new_num_inputs);
    }
}

void BaseTOP::set_resolution(int res_x, int res_y)
{
    if (resolution_x != res_x || resolution_y != res_y)
    {
        if (res_x > 0 && res_y > 0)
        {
            resolution_x = res_x;
            resolution_y = res_y;

            glBindTexture(GL_TEXTURE_2D, output_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(pixel_type), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

            emit resolution_changed(res_x, res_y);
        }
    }
}

void BaseTOP::set_position(int pos_x, int pos_y)
{
    if (position_x != pos_x || position_y != pos_y)
    {
        position_x = pos_x;
        position_y = pos_y;

        emit position_changed(pos_x, pos_y);
    }
}

void BaseTOP::set_pixel_type(PixelType new_type)
{
    if (pixel_type != new_type)
    {
        pixel_type = new_type;

        glBindTexture(GL_TEXTURE_2D, output_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(pixel_type), resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        emit pixel_type_changed(new_type);
    }
}

void BaseTOP::set_resolution_policy(Policy new_policy)
{
    if (resolution_policy != new_policy)
    {
        resolution_policy = new_policy;
        emit resolution_policy_changed(new_policy);
    }
}

void BaseTOP::set_pixel_type_policy(Policy new_policy)
{
    if (pixel_type_policy != new_policy)
    {
        pixel_type_policy = new_policy;
        emit pixel_type_policy_changed(new_policy);
    }
}


