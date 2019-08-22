#pragma once

#include "view/opengldataview.h"


class OperatorView;
class TextureData;


class TextureDataView : public OpenGLDataView
{

public:

    TextureDataView(TextureData* texture, OperatorView* parent_op);

    void paint_opengl(int res_x, int res_y) override;


private:

    TextureData* texture;

};
