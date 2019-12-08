#include "thresholdoperator.h"



bool ThresholdOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram ThresholdOperator::shader;
GLuint ThresholdOperator::vao;
GLuint ThresholdOperator::vbo;





BaseOperator* ThresholdOperator::create()
{
    return new ThresholdOperator();
}


const OperatorDescription ThresholdOperator::description
{
    "Threshold",
    "Texture",
    &create,
    { &TextureData::Type },
    { &TextureData::Type },
    &TextureView::Type,
};



ThresholdOperator::ThresholdOperator()
    : BaseOperator(description)
{
    initializeOpenGLFunctions();
}


void ThresholdOperator::run()
{

}


void ThresholdOperator::parameterChangeEvent(const BaseParameter* parameter)
{

}
