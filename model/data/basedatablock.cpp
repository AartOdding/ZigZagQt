#include "model/data/basedatablock.h"

#include <functional>


BaseDataBlock::BaseDataBlock(QStringView data_type_name_)
    : data_type_name(data_type_name_)
{

}



void BaseDataBlock::parameters_changed()
{
    emit parameters_modified();
}
