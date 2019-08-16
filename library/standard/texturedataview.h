#pragma once

#include "view/opengldataview.h"


class OperatorView;
class TextureDataBlock;


class TextureDataView : public OpenGLDataView
{

public:

    TextureDataView(TextureDataBlock* texture, OperatorView* parent_op);

    void paint_opengl(int res_x, int res_y) override;


private:

    TextureDataBlock* texture;

};
