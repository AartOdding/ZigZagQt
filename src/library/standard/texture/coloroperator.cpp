#include "coloroperator.h"




const OperatorDescription ColorOperator::Type
{
    "Uniform Fill",
    "Texture",
    &create,
    { },
    { &TextureData::Type },
    &TextureView::Type
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
    output_texture.bind_as_framebuffer();
    auto color = m_color.get();
    glClearColor(color.red(), color.green(), color.blue(), color.alpha());
    glClear(GL_COLOR_BUFFER_BIT);
    //auto test_t = test.get()[1];
}
