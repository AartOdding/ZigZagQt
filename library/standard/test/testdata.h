#pragma once

#include "model/basedatatype.h"
#include "model/baseoperator.h"
#include "model/parameter/int.h"

#include <iostream>



class TestData : public BaseDataType
{

public:

    static const inline DataTypeInfo Type { "Test", "Standard/Test", QColor(205, 255, 0), false };

    TestData(BaseOperator* op)
        : BaseDataType(op, Type)
    {
        std::cout << "Test Data - constructor\n";
    }

    void acquire_resources() override
    {
        std::cout << "Test Data - acquire_resources\n";
    }

    void release_resources() override
    {
        std::cout << "Test Data - release_resources\n";
    }


    IntPar par1 { this, "Test Parameter 1", -334 };
    IntPar par2 { this, "Test Parameter 2", 43551 };

};
