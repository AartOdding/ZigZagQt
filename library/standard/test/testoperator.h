#pragma once

#include "model/baseoperator.h"

#include "testdata.h"
#include "library/standard/texture/texturedata.h"
#include "model/datainput.h"
#include "model/parameter/int.h"
#include "model/parameter/enum.h"


// Implementation in testoperator.cpp
BaseOperator * create_test_operator();



class TestOperator : public BaseOperator
{

public:

    static const inline OperatorTypeInfo Type { "Test Operator", "Standard/Test",
        { &TestData::Type, &TestData::Type, &TestData::Type },
        { &TestData::Type, &TestData::Type }, true, create_test_operator };


    TestOperator()
        : BaseOperator(Type)
    {
        std::cout << "TestOperator - constructor\n";
        resolution_x.set_update_mode(parameter::UpdateMode::NecessaryUpdates);
        resolution_y.set_update_mode(parameter::UpdateMode::NecessaryUpdates);
    }

    void run()
    {
        //std::cout << "TestOperator - run\n";
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

    parameter::Enum pixel_format{ this, PixelDataFormat, "Pixel Data Format", 0 };
    parameter::Enum pixel_channels{ this, PixelNumChannels, "Pixel Num Channels", 3 };
    parameter::Enum pixel_normalized{ this, PixelIsNormalized, "Pixel is Normalized", 1 };
    parameter::Int resolution_x{ this, "Resolution X", 600 };
    parameter::Int resolution_y{ this, "Resolution Y", 600 };
    parameter::Int resolution_z{ this, "Resolution Z", 300 };

    //DataInput input1{ this, TestData::Type };
    //DataInput input2{ this, TestData::Type };
    //DataInput input3{ this, TestData::Type };
    //DataInput input4{ this, TestData::Type };
    //DataInput input5{ this, TestData::Type };
    //DataInput input6{ this, TestData::Type };
    DataInput input1{ this, TestData::Type };
    DataInput input2{ this, TestData::Type };
    DataInput input3{ this, TestData::Type };

    TestData output1{ this };
    TestData output2{ this };

};
