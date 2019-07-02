#include "model/data/basedatablock.h"

#include <functional>


BaseDataBlock::BaseDataBlock(const std::string& data_type_name_)
    : data_type_name(data_type_name_)
{
    //std::function<BaseDataBlock *(BaseDataBlock *)> c;
}
