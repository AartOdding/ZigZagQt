#include "coloroperator.h"




const OperatorTypeDetails ColorOperator::Type
{
    "Uniform Fill",
    "Creates a texure of uniform color.",
    { "openGLSystem" },
    "Aart Odding",
    "Creates a texure of uniform color."
};


BaseOperator* ColorOperator::create(BaseZigZagObject* parent)
{
    return new ColorOperator(parent);
}


ColorOperator::ColorOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, Type)
{
    initializeOpenGLFunctions();
}


ColorOperator::~ColorOperator()
{
}


void ColorOperator::run()
{
    //std::cout << red_value.get() << "color run \n";
    output_texture.bindFramebuffer();
    auto color = m_color.get();
    glClearColor(color.red(), color.green(), color.blue(), color.alpha());
    glClear(GL_COLOR_BUFFER_BIT);
    //auto test_t = test.get()[1];
}
