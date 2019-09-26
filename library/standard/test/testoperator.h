#pragma once

#include "model/baseoperator.h"

#include "testdata.h"
#include "library/standard/texture/texturedata.h"
#include "model/datainput.h"
#include "model/parameter/int64parameter.h"
#include "model/parameter/enumparameter.h"
#include "model/parameter/doubleparameter.h"
#include "library/standard/test/testdataview.h"


// Implementation in testoperator.cpp
BaseOperator * create_test_operator();



class TestOperator : public BaseOperator
{

public:

    static const inline OperatorTypeInfo Type { "Test Operator", "Test",
        { &TestData::Type, &TestData::Type, &TestData::Type },
        { &TestData::Type, &TestData::Type }, &TestDataView::Type, create_test_operator };


    TestOperator()
        : BaseOperator(Type)
    {
        std::cout << "TestOperator - constructor\n";
        //resolution_x.set_minimal_updates(true);
        //resolution_y.set_minimal_updates(true);
    }


    void parameter_changed(BaseParameter* par) override
    {
        std::cout << "par changed " << par->get_name() << "\n";
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

    ButtonPar test_buton{ this, "Test Button" };
    EnumPar pixel_format{ this, "Pixel Data Format", PixelDataFormat, 0 };
    EnumPar pixel_channels{ this, "Pixel Num Channels", PixelNumChannels, 3 };
    IntPar resolution_x{ this, "Resolution X", 600, 0, 255 };
    IntPar resolution_y{ this, "Resolution Y", 600, 0, 255 };
    IntPar resolution_z{ this, "Resolution Z", 300, 0, 255 };
    DoublePar test_float{ this, "test float", 0.3 };

    //DataInput input1{ this, TestData::Type };
    //DataInput input2{ this, TestData::Type };
    //DataInput input3{ this, TestData::Type };
    //DataInput input4{ this, TestData::Type };
    //DataInput input5{ this, TestData::Type };
    //DataInput input6{ this, TestData::Type };
    DataInput input1{ this, "Test In 1", TestData::Type };
    DataInput input2{ this, "Test In 2", TestData::Type };
    DataInput input3{ this, "Test In 3", TestData::Type };

    TestData output1{ this };
    TestData output2{ this };

};
