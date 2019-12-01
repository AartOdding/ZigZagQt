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


BaseOperator* ColorOperator::create()
{
    return new ColorOperator();
}


ColorOperator::ColorOperator()
    : BaseOperator(Type)
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
    glClearColor(red_value.get() / 255.0, green_value.get() / 255.0, blue_value.get() / 255.0, alpha_value.get() / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //auto test_t = test.get()[1];
}
