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
        "uint8_1_channel",
        "uint8_2_channel",
        "uint8_3_channel",
        "uint8_4_channel",
        "float_1_channel",
        "float_2_channel",
        "float_3_channel",
        "float_4_channel"
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


    EnumParameter pixel_type{ PixelType, "pixel type", "uint8_4_channel" };
    IntegerParameter resolution_x{ "resolution x", 256 };
    IntegerParameter resolution_y{ "resolution y", 256 };

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
