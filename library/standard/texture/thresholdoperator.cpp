#include "thresholdoperator.h"



bool ThresholdOperator::gpu_resources_initialized = false;
QOpenGLShaderProgram ThresholdOperator::shader;
GLuint ThresholdOperator::vao;
GLuint ThresholdOperator::vbo;


ThresholdOperator::ThresholdOperator()
    : BaseOperator(Type)
{
    initializeOpenGLFunctions();
}


void ThresholdOperator::run()
{

}


void ThresholdOperator::parameter_changed(BaseParameter* parameter)
{

}
