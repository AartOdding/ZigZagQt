#include "cameraoperator.h"
#include <QCameraInfo>

#include <iostream>


BaseOperator * CameraOperator::create(BaseZigZagObject* parent)
{
    return new CameraOperator(parent);
}


const OperatorTypeDetails CameraOperator::description
{
    "Camera",
    "Texture"
};


CameraOperator::CameraOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    capture.setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    camera.setCaptureMode(QCamera::CaptureStillImage);
    camera.start();

    std::cout << "\n cameras: \n";
    auto cams = QCameraInfo::availableCameras();
    for (auto& cam : cams)
    {
        std::cout << cam.deviceName().toStdString() << "\n";
    }
    std::cout << "\nformats: \n";
    for (auto fmt : capture.supportedBufferFormats())
    {
        std::cout << fmt << "\n";
    }

    std::cout << "\nresolutions: \n";
    for (auto size : capture.supportedResolutions())
    {
        std::cout << size.width() << " " << size.height() << "\n";
    }

    std::cout << "\ncodecs: \n";
    for (auto codec : capture.supportedImageCodecs())
    {
        std::cout << codec.toStdString() << "\n";
    }


    connect(&capture, &QCameraImageCapture::imageAvailable, this, &CameraOperator::on_image_captured);
}

void CameraOperator::run()
{
    if (has_frame)
    {
        if (output_texture.getWidth() != last_frame.width() || output_texture.getHeight() != last_frame.height())
        {
            output_texture.setResolution(last_frame.width(), last_frame.height());
        }
        if (last_frame.pixelFormat() == QVideoFrame::Format_RGB32 || last_frame.pixelFormat() == QVideoFrame::Format_ARGB32)
        {
            last_frame.map(QAbstractVideoBuffer::ReadOnly);
            auto raw = last_frame.bits();

            std::vector<unsigned char> rgb;
            rgb.reserve(last_frame.width() * last_frame.height() * 3);
            for (int i = 0; i < last_frame.width() * last_frame.height() * 4; i += 4)
            {
                rgb.push_back(raw[i]);
                rgb.push_back(raw[i+1]);
                rgb.push_back(raw[i+2]);
            }
            std::cout << "came frame\n";
            output_texture.uploadPixels(TextureData::ThreeChannels, TextureData::Normalized8Bit, rgb.data());
            updateView();
        }
        has_frame = false;
    }
    if (capture.isReadyForCapture())
    {
        capture.capture();
    }
}

void CameraOperator::on_image_captured(int, const QVideoFrame& buffer)
{
    last_frame = buffer;
    has_frame = true;
}

void CameraOperator::parameterChangeEvent(const BaseParameter* parameter)
{

}
