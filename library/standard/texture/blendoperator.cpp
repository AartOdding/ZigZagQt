#include "blendoperator.h"

BlendOperator::BlendOperator()
    : BaseOperator(Type)
{
    int x = 0;
}

BlendOperator::~BlendOperator()
{

    int x = 0;
}


void BlendOperator::run()
{

    int x = 0;
}


BaseOperator* BlendOperator::create()
{
    return new BlendOperator();
}
