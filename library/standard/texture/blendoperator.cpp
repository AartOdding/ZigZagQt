#include "blendoperator.h"

BlendOperator::BlendOperator()
    : BaseOperator(Type)
{

}

BlendOperator::~BlendOperator()
{

}


void BlendOperator::run()
{

}


BaseOperator* BlendOperator::create()
{
    return new BlendOperator();
}
