#pragma once

#include "model/basedatablock.h"
#include "model/enumdefinition.h"
#include "model/parameter/enumparameter.h"
#include "model/parameter/integerparameter.h"

#include <QObject>
#include <QOpenGLFunctions_3_2_Core>




const inline EnumDefinition PixelType
{
    "PixelType",
    {
        { "uint8_1_channel", GL_R8 },
        { "uint8_2_channel", GL_RG8 },
        { "uint8_3_channel", GL_RGB8 },
        { "uint8_4_channel", GL_RGBA8 },
        { "float_1_channel", GL_R32F },
        { "float_2_channel", GL_RG32F },
        { "float_3_channel", GL_RGB32F },
        { "float_4_channel", GL_RGBA32F }
    }
};


class TextureDataBlock : public BaseDataBlock,
                         protected QOpenGLFunctions_3_2_Core
{
    Q_OBJECT

public:

    TextureDataBlock();
    ~TextureDataBlock() override;

    void acquire_resources() override;

    void release_resources() override;


    void bind_as_framebuffer();

    void bind_as_texture(int texture_index);


    EnumParameter pixel_type{ PixelType, GL_RGBA8 };
    IntegerParameter resolution_x{ 256 };
    IntegerParameter resolution_y{ 256 };

    std::vector<BaseParameter*> get_parameters() override
    {
        return { &pixel_type, &resolution_x, &resolution_y };
    }

public slots:

    void reallocate_texture();


private:

    bool currently_allocated = false;
    GLuint fbo_handle;
    GLuint texture_handle;

};
