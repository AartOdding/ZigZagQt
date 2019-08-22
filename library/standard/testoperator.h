#pragma once

#include "model/baseoperator.h"

#include "testdata.h"
#include "texturedata.h"
#include "model/datainput.h"
#include "model/parameter/integerparameter.h"
#include "model/parameter/enumparameter.h"


// Implementation in testoperator.cpp
BaseOperator * create_test_operator();



class TestOperator : public BaseOperator
{

public:



    static const inline OperatorTypeInfo Type { "Test Operator", create_test_operator };

    TestOperator()
        : BaseOperator(Type)
    {
        std::cout << "TestOperator - constructor\n";
        resolution_x.set_update_mode(BaseParameter::UpdateMode::NecessaryUpdates);
        resolution_y.set_update_mode(BaseParameter::UpdateMode::NecessaryUpdates);
    }

    void run()
    {
        std::cout << "TestOperator - run\n";
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

    EnumParameter pixel_format{ this, PixelDataFormat, "Pixel Data Format", 0 };
    EnumParameter pixel_channels{ this, PixelNumChannels, "Pixel Num Channels", 3 };
    EnumParameter pixel_normalized{ this, PixelIsNormalized, "Pixel is Normalized", 1 };
    IntegerParameter resolution_x{ this, "Resolution X", 600 };
    IntegerParameter resolution_y{ this, "Resolution Y", 600 };
    IntegerParameter resolution_z{ this, "Resolution Z", 300 };

    //DataInput input1{ this, TestData::Type };
    //DataInput input2{ this, TestData::Type };
    //DataInput input3{ this, TestData::Type };
    //DataInput input4{ this, TestData::Type };
    //DataInput input5{ this, TestData::Type };
    //DataInput input6{ this, TestData::Type };
    DataInput input7{ this, TestData::Type };
    DataInput input8{ this, TestData::Type };
    DataInput input9{ this, TestData::Type };
    DataInput input1{ this, TestData::Type };
    DataInput input2{ this, TestData::Type };
    DataInput input3{ this, TestData::Type };

    TestData output1{ this };
    TestData output2{ this };
    TestData output3{ this };
    TestData output4{ this };

};
