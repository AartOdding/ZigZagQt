#pragma once

#include "model/basedatablock.h"

#include <iostream>


class TestDataBlock : public BaseDataBlock
{

public:

    TestDataBlock()
        : BaseDataBlock("test")
    {
        std::cout << "TestDataBlock - constructor\n";
    }

    std::vector<BaseParameter*> get_parameters()
    {
        std::cout << "TestDataBlock - get_parameters\n";
        return {};
    }

    void acquire_resources()
    {
        std::cout << "TestDataBlock - acquire_resources\n";
    }

    void release_resources()
    {
        std::cout << "TestDataBlock - release_resources\n";
    }

};
