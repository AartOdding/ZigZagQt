#pragma once

#include "model/BaseDataType.hpp"
#include "model/parameter/EnumParameter.hpp"
#include "model/parameter/IntParameter.hpp"

#include <QObject>
#include <QOpenGLFunctions_3_2_Core>



class TextureData : public BaseDataType,
                    protected QOpenGLFunctions_3_2_Core
{
    Q_OBJECT

public:

    enum PixelFormat
    {
        Normalized8Bit        = 0,
        Normalized8BitSigned  = 1,
        Normalized16Bit       = 2,
        Normalized16BitSigned = 3,
        Float16Bit            = 4,
        Float32Bit            = 5
    };

    enum NumChannels
    {
        OneChannel    = 0,
        TwoChannels   = 1,
        ThreeChannels = 2,
        FourChannels  = 3
    };

    TextureData(BaseOperator* parentOperator, const QString& name, bool createFbo = true);

    ~TextureData() override;

    // Note, num channels and format describe the image data as it resides in memory at the pixel_data
    // pointer, it is not a description of the storage method on the gpu!
    void uploadPixels(NumChannels numChannels, PixelFormat format, const void * pixels);

    void bindFramebuffer();
    void bindTexture(int texture_index) const;

    void setResolution(int x, int y);
    void setNumChannels(NumChannels num);
    void setPixelFormat(PixelFormat format);

    int getWidth() const;
    int getHeight() const;
    NumChannels getNumChannels() const;
    PixelFormat getPixelFormat() const;

    static void bind_empty_texture(int texture_index); // TODO find better solution

    static const inline DataTypeDescription description { "Texture", "Texture", QColor(255, 20, 147), true };

protected:

    void acquireResources() override;
    void releaseResources() override;

    void parameterChangeEvent(const BaseParameter*) override;

private:

    GLenum openGLPixelFormat() const;

    void reallocate();

    const static std::vector<QString> pixelFormatStrings;
    const static std::vector<QString> numChannelsStrings;

    Int2Parameter m_resolution{ this, QStringLiteral("Resolution"), { 256, 256 }, { 1, 1 }, { 16384, 16384 } };
    EnumParameter m_pixelFormat{ this, QStringLiteral("Pixel Format"), pixelFormatStrings, 0 };
    EnumParameter m_numChannels{ this, QStringLiteral("Num Channels"), numChannelsStrings, 3 };

    GLuint m_fboHandle;
    GLuint m_textureHandle;

    bool m_hasFbo = false;
    bool m_isAllocated = false;
    bool m_needsReallocation = false;

};
