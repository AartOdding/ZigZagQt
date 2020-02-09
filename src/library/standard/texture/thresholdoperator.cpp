#include "thresholdoperator.h"



bool ThresholdOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram ThresholdOperator::shader;
GLuint ThresholdOperator::vao;
GLuint ThresholdOperator::vbo;





BaseOperator* ThresholdOperator::create(BaseZigZagObject* parent)
{
    return new ThresholdOperator(parent);
}


const OperatorDescription ThresholdOperator::description
{
    "Threshold",
    "Texture",
    &create,
    { &TextureData::description },
    { &TextureData::description },
    &TextureView::Type,
};



ThresholdOperator::ThresholdOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    initializeOpenGLFunctions();
}


void ThresholdOperator::run()
{

}


void ThresholdOperator::parameterChangeEvent(const BaseParameter* parameter)
{

}
