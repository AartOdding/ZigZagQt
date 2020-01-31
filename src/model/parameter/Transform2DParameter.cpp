#include "Transform2DParameter.hpp"




Transform2DParameter::Transform2DParameter(BaseZigZagObject * parent, const QString& name)
    : BaseParameter(ParameterType::Transform2D, parent, name)
{

}


void Transform2DParameter::addTranslate()
{
    addTranslate(0, 0);
}


void Transform2DParameter::addRotate()
{
    addRotate(0);
}


void Transform2DParameter::addScale()
{
    addScale(1, 1);
}


Float2Parameter* Transform2DParameter::addTranslate(float tx, float ty)
{
    auto translate = new Float2Parameter(this, "Translate", { tx, ty });
    m_steps.push_back({ TransformationType::Transle, translate });
    return translate;
}


FloatParameter* Transform2DParameter::addRotate(float rotation)
{
    auto rotate = new FloatParameter(this, "Rotate", rotation);
    m_steps.push_back({ TransformationType::Rotate, rotate });
    return rotate;
}


Float2Parameter* Transform2DParameter::addScale(float scaleX, float scaleY)
{
    auto scale = new Float2Parameter(this, "Scale", { scaleX, scaleY });
    m_steps.push_back({ TransformationType::Scale, scale });
    return scale;
}
