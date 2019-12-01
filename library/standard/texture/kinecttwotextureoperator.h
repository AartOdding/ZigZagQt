#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QtGlobal>

#include "model/baseoperator.h"

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

    void parameter_changed(BaseParameterOld* parameter) override;


    static BaseOperator * create();

    static const OperatorDescription description;


private:

    TextureData output_texture{ this, "Depth Texture", false };


#ifdef Q_OS_WIN

    IKinectSensor* kinect = nullptr;

    IDepthFrameReader* depth_reader = nullptr;

#endif

};
