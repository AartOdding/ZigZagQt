#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QtGlobal>

#include "model/BaseOperator.hpp"

#include "texturedata.h"
#include "textureview.h"


#ifdef Q_OS_WIN
    #include "Kinect.h"
#endif


class KinectTwoTextureOperator : public BaseOperator,
                                 public QOpenGLFunctions_3_3_Core
{
public:

    KinectTwoTextureOperator();

    void run() override;

    void parameterChangeEvent(const BaseParameter* parameter) override;


    static BaseOperator * create();

    static const OperatorDescription description;


private:

    TextureData output_texture{ this, "Depth Texture", false };


#ifdef Q_OS_WIN

    IKinectSensor* kinect = nullptr;

    IDepthFrameReader* depth_reader = nullptr;

#endif

};
