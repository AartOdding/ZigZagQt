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


class Kinect2TextureOperator : public BaseOperator,
                               public QOpenGLFunctions_3_3_Core
{
public:

    Kinect2TextureOperator();

    void run() override;

    void parameter_changed(BaseParameter* parameter) override;


    static BaseOperator * create() { return new Kinect2TextureOperator(); }

    static const inline OperatorTypeInfo Type { "Kinect 2", "Texture", {  },
                                              { &TextureData::Type }, &TextureView::Type, &create };

private:

    TextureData output_texture{ this, "Depth Texture", false };


#ifdef Q_OS_WIN

    IKinectSensor* kinect = nullptr;

    IDepthFrameReader* depth_reader = nullptr;

#endif

};
