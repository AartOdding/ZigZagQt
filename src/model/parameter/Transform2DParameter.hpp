#pragma once


#include "BaseParameter.hpp"
#include "FloatParameter.hpp"


enum class TransformationType
{
    Transle,
    Rotate,
    Scale
};


class Transform2DParameter : public BaseParameter
{
    Q_OBJECT

public:

    Transform2DParameter(BaseZigZagObject * parent, const QString& name);

public slots:

    void addTranslate();
    void addRotate();
    void addScale();

    Float2Parameter* addTranslate(float translateX, float translateY);
    FloatParameter* addRotate(float rotation);
    Float2Parameter* addScale(float scaleX, float scaleY);

signals:



private:

    std::vector<std::pair<TransformationType, BaseParameter*>> m_steps;

};

