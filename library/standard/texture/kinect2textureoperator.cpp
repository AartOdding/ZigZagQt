#include "kinect2textureoperator.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utility/stb_image_write.h"

#include <iostream>



Kinect2TextureOperator::Kinect2TextureOperator()
    : BaseOperator(Type)
{
    output_texture.set_resolution(512, 424);
    output_texture.set_num_channels(PixelNumChannelsEnum::one_channel);
    output_texture.set_format(PixelDataFormatEnum::unsigned_norm_8bit);

#ifdef Q_OS_WIN
    if (FAILED(GetDefaultKinectSensor(&kinect))) return;

    BOOLEAN open_already;
    kinect->get_IsOpen(&open_already);

    if (open_already) return;
    kinect->Open();

    IDepthFrameSource * depth_source = nullptr;
    kinect->get_DepthFrameSource(&depth_source);

    if (depth_source)
    {
        std::cout << "Got reader\n";
        depth_source->OpenReader(&depth_reader);
        depth_source->Release();
    }
#endif

}


void Kinect2TextureOperator::run()
{

#ifdef Q_OS_WIN

    IDepthFrame * frame = nullptr;

    if (SUCCEEDED(depth_reader->AcquireLatestFrame(&frame)))
    {
        if (output_texture.get_resolution_x() != 512 || output_texture.get_resolution_y() != 424)
        {
            output_texture.set_resolution(512, 424);
        }
        /*
        if (output_texture.get_format() != PixelDataFormatEnum::unsigned_norm_8bit)
        {
            output_texture.set_format(PixelDataFormatEnum::unsigned_norm_8bit);
        }
        if (output_texture.get_num_channels() != PixelNumChannelsEnum::one_channel)
        {
            output_texture.set_num_channels(PixelNumChannelsEnum::one_channel);
        }*/

        uint16_t * buffer_pointer = nullptr;
        unsigned buffer_size = 0;
        frame->AccessUnderlyingBuffer(&buffer_size, &buffer_pointer);

        //std::vector<unsigned short> depth_data;
        //depth_data.resize(512 * 424);

        //frame->CopyFrameDataToArray(depth_data.size(), depth_data.data());

        std::vector<unsigned char> depth_data_8bit;
        depth_data_8bit.reserve(512 * 424);

        constexpr int count = 512 * 424;

        for (int i = 0; i < count; ++i)
        {
            unsigned short val = (buffer_pointer[count - i - 1] << 4) >> 8;

            if (val != 0) val = 255 - val;

            depth_data_8bit.emplace_back(val);

            //depth_data_8bit[i] = val >> 8;
        }

        if (buffer_size == 512 * 424 && buffer_pointer != nullptr)
        {
            output_texture.upload_data(PixelNumChannelsEnum::one_channel, PixelDataFormatEnum::unsigned_int_8bit, depth_data_8bit.data());
        }

        frame->Release();
        update_view();
    }
    else
    {
        // No new frame to load.
    }

#endif

}


void Kinect2TextureOperator::parameter_changed(BaseParameter* parameter)
{

}
