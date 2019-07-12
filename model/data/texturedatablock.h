#pragma once

#include "model/data/basedatablock.h"
#include "model/data/integerparameter.h"

#include <QObject>
#include <QOpenGLFunctions_3_2_Core>



enum class PixelType : int
{
    UINT8_SINGLE    = GL_R8,
    UINT8_DOUBLE    = GL_RG8,
    UINT8_TRIPLE    = GL_RGB8,
    UINT8_QUADRUPLE = GL_RGBA8,
    FLOAT_SINGLE    = GL_R32F,
    FLOAT_DOUBLE    = GL_RG32F,
    FLOAT_TRIPLE    = GL_RGB32F,
    FLOAT_QUADRUPLE = GL_RGBA32F
};



class TextureDataBlock : public BaseDataBlock,
                         protected QOpenGLFunctions_3_2_Core
{
    Q_OBJECT

public:

    TextureDataBlock();
    ~TextureDataBlock() override;

    std::vector<BaseParameter*> get_parameters() override;

    void bind_as_framebuffer();
    void bind_as_texture(int texture_index);

    IntegerParameter resolution_x{ 256 };
    IntegerParameter resolution_y{ 256 };


public slots:

    void reallocate_texture();


private:

    PixelType pixel_type = PixelType::UINT8_QUADRUPLE;

    GLuint fbo_handle;
    GLuint texture_handle;

};
