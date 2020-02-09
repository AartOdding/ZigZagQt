#include "BaseOperator.hpp"
#include "BaseDataType.hpp"
#include "application.h"

#include "command/movecommand.h"
#include "model/OperatorNetwork.hpp"
#include "model/OperatorLibrary.hpp"
#include "model/datainput.h"

#include <QPointer>

#include <algorithm>




OperatorDescription::OperatorDescription(const QString& name_,
                                         const QString& package_,
                                         std::function<BaseOperator*(BaseZigZagObject* parent)> construct_,
                                         const std::vector<const DataTypeDescription*>& inputs_,
                                         const std::vector<const DataTypeDescription*>& outputs_,
                                         const DataViewTypeInfo * view_)
    : name(name_),
      package(package_),
      construct(construct_),
      inputs(inputs_),
      outputs(outputs_),
      view(view_)
{
    OperatorLibrary::instance()->add(this);
}



BaseOperator::BaseOperator(BaseZigZagObject* parent, const OperatorDescription& type_)
    : BaseZigZagObject(parent, type_.name),
      m_mutex(std::make_shared<std::mutex>()),
      m_description(&type_)
{

}



BaseOperator::~BaseOperator()
{

}


void BaseOperator::lock()
{
    m_mutex->lock();
}


void BaseOperator::unlock()
{
    m_mutex->unlock();
}


std::shared_ptr<std::mutex> BaseOperator::getLock()
{
    return m_mutex;
}


void BaseOperator::updateView()
{
    emit update_view_requested();
}



int BaseOperator::positionX() const
{
    return m_positionX;
}



int BaseOperator::positionY() const
{
    return m_positionY;
}



const OperatorDescription * BaseOperator::description() const
{
    return m_description;
}


/*
void BaseOperator::remove()
{
    application::project_model()->removeOperator(this);
}*/



void BaseOperator::move_to(int pos_x, int pos_y)
{
    if (m_positionX != pos_x || m_positionY != pos_y)
    {
        application::project_model()->getUndoStack()->push(new MoveCommand(*this, pos_x, pos_y));
    }
}



void BaseOperator::set_position(int pos_x, int pos_y)
{
    if (m_positionX != pos_x || m_positionY != pos_y)
    {
        m_positionX = pos_x;
        m_positionY = pos_y;

        emit position_changed(pos_x, pos_y);
    }
}



QList<DataInput*> BaseOperator::dataInputs() const
{
    return findChildren<DataInput*>(QString(), Qt::FindDirectChildrenOnly);
}



QList<BaseDataType*> BaseOperator::dataOutputs() const
{
    return findChildren<BaseDataType*>(QString(), Qt::FindDirectChildrenOnly);
}



QList<DataInput*> BaseOperator::activeDataInputs() const
{
    auto inputs = dataInputs();
    inputs.erase(std::remove_if(inputs.begin(), inputs.end(), [](DataInput* input){ return !input->is_connected(); }), inputs.end());
    return inputs;
}



QList<BaseDataType*> BaseOperator::activeDataOutputs() const
{
    auto outputs = dataOutputs();
    outputs.erase(std::remove_if(outputs.begin(), outputs.end(), [](BaseDataType* output){ return !output->isConnected(); }), outputs.end());
    return outputs;
}



bool BaseOperator::hasActiveDataInputs() const
{
    for (auto input : dataInputs())
    {
        if (input->is_connected())
        {
            return true;
        }
    }
    return false;
}



bool BaseOperator::hasActiveDataOutputs() const
{
    for (auto output : dataOutputs())
    {
        if (output->isConnected())
        {
            return true;
        }
    }
    return false;
}



QVariantMap BaseOperator::storeState() const
{
    QVariantMap state;
    state.insert(QStringLiteral("posX"), QVariant(m_positionX));
    state.insert(QStringLiteral("posY"), QVariant(m_positionY));
    return state;
}



void BaseOperator::loadState(const QVariantMap& state)
{
    auto itX = state.find(QStringLiteral("posX"));
    auto itY = state.find(QStringLiteral("posY"));

    if (itX != state.end())
    {
        m_positionX = itX->toInt();
    }
    if (itY != state.end())
    {
        m_positionY = itY->toInt();
    }
}

/*
void BaseOperator::write_to_xml(XmlSerializer& xml)
{
    xml.begin_element("BaseOperator");
    xml.add_int_attribute("id", xml.id(this));

        //BaseParameter::write_to_xml(xml);

        xml.add_int_element("position_x", posX);
        xml.add_int_element("position_y", posY);

        xml.begin_element("inputs");
        xml.add_int_attribute("size", inputs.size());
            for (auto in : inputs)
            {
                in->write_to_xml(xml);
            }
        xml.end_element(); // ends inputs

        xml.begin_element("outputs");
        xml.add_int_attribute("size", outputs.size());
            for (auto out : outputs)
            {
                out->write_to_xml(xml);
            }
        xml.end_element(); // ends outputs

    xml.end_element();
}*/
