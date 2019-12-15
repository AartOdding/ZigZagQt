#pragma once

#include "model/basedatatype.h"
#include "model/enumdefinition.h"
#include "model/parameter/EnumParameter.hpp"
#include "model/parameter/IntParameter.hpp"

#include <QObject>
#include <QOpenGLFunctions_3_2_Core>



enum class PixelDataFormatEnum
{
    unsigned_norm_8bit,
    signed_norm_8bit,
    unsigned_int_8bit,
    signed_int_8bit,

    unsigned_norm_16bit,
    signed_norm_16bit,
    unsigned_int_16bit,
    signed_int_16bit,

    unsigned_int_32bit,
    signed_int_32bit,

    float_16bit,
    float_32bit
};


const inline EnumDefinition PixelDataFormat
{
    "PixelDataType",
    {
        "8 Bit Unsigned Norm",
        "8 Bit Signed Norm",
        "8 Bit Unsigned Int",
        "8 Bit Signed Int",
        "16 Bit Unsigned Norm",
        "16 Bit Signed Norm",
        "16 Bit Unsigned Int",
        "16 Bit Signed Int",
        "32 Bit Unsigned Int",
        "32 Bit Signed Int",
        "16 Bit Float",
        "32 Bit Float"
    }
};


enum class PixelNumChannelsEnum
{
    one_channel,
    two_channels,
    three_channels,
    four_channels
};


const inline EnumDefinition PixelNumChannels
{
    "PixelNumChannels",
    {
        "1 Channel",
        "2 Channels",
        "3 Channels",
        "4 Channels"
    }
};


class TextureData : public BaseDataType,
                    protected QOpenGLFunctions_3_2_Core
{
    Q_OBJECT

public:

    TextureData(BaseOperator* parent_operator, const char * name, bool has_fbo = true);

    ~TextureData() override;

    void parameterChangeEvent(const BaseParameter*) override;

    // Note, num channels and format describe the image data as it resides in memory at the pixel_data
    // pointer, it is not a description of the storage method on the gpu!
    void upload_data(PixelNumChannelsEnum num_channels, PixelDataFormatEnum format, const void * pixel_data);

    void acquire_resources() override;
    void release_resources() override;

    void bind_as_framebuffer();
    void bind_as_texture(int texture_index) const;
    static void bind_empty_texture(int texture_index);

    void set_resolution(int x, int y);
    void set_num_channels(PixelNumChannelsEnum num);
    void set_format(PixelDataFormatEnum format);

    int get_resolution_x() const;
    int get_resolution_y() const;
    PixelNumChannelsEnum get_num_channels() const;
    PixelDataFormatEnum get_format() const;

    static const inline DataTypeInfo Type { "Texture", "Texture", QColor(255, 20, 147), true };


private:

    void reallocate();

    static GLenum gl_format_for(const EnumPar& format, const EnumPar& num_channels);

    Int2Par resolution{ this, "Resolution", { 256, 256 }, 1, 16384 };
    EnumPar pixel_format{ this, "Format", PixelDataFormat, 0 };
    EnumPar pixel_channels{ this, "Num Channels", PixelNumChannels, 3 };

    GLuint fbo_handle;
    GLuint texture_handle;

    bool currently_allocated = false;
    bool needs_reallocation = false;
    bool has_fbo;

};
