#include "texturedataview.h"



TextureDataView::TextureDataView(TextureData* t, OperatorView* parent_op)
    : OpenGLDataView(*parent_op), texture(t)
{

}


void TextureDataView::paint_opengl(int res_x, int res_y)
{
    glClearColor(0, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
