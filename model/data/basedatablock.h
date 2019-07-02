#pragma once

#include <string>


class BaseDataBlock
{

public:

    BaseDataBlock(const std::string& data_type_name);

    virtual ~BaseDataBlock() { }

    virtual BaseDataBlock * create() = 0;

private:

    std::string data_type_name;


};
