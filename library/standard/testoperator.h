#pragma once

#include "model/baseoperator.h"

#include "testdatablock.h"
#include "model/datablockinput.h"


// Implementation in testoperator.cpp
BaseOperator * create_test_operator();


class TestOperator : public BaseOperator
{

public:

    TestOperator()
    {
        std::cout << "TestOperator - constructor\n";
    }

    void run()
    {
        std::cout << "TestOperator - run\n";
    }

    std::vector<DataBlockInput*> get_inputs()
    {
        std::cout << "TestOperator - get_inputs\n";
        return { &input1, &input2, &input3 };
    }

    std::vector<BaseDataBlock*> get_outputs()
    {
        std::cout << "TestOperator - get_outputs\n";
        return { &output1, &output2 };
    }

    std::vector<BaseParameter*> get_parameters()
    {
        std::cout << "TestOperator - get_parameters\n";
        return { };
    }

    void acquire_resources()
    {
        std::cout << "TestOperator - acquire_resources\n";
    }


    void release_resources()
    {
        std::cout << "TestOperator - release_resources\n";
    }

private:

    DataBlockInput input1{ "test" };
    DataBlockInput input2{ "test" };
    DataBlockInput input3{ "test" };

    TestDataBlock output1;
    TestDataBlock output2;

};
