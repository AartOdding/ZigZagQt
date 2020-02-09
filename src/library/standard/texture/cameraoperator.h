#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include <QCamera>
#include <QVideoFrame>
#include <QCameraImageCapture>

#include "model/BaseOperator.hpp"

#include "texturedata.h"
#include "textureview.h"



class CameraOperator : public BaseOperator,
                       public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:

    CameraOperator(BaseZigZagObject* parent);

    void run() override;

    void parameterChangedEvent(const BaseParameter* parameter) override;


    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;

public slots:

    void on_image_captured(int id, const QVideoFrame& buffer);

private:

    TextureData output_texture{ this, "Camera Image", false };
    //TextureView outputView{ this, &output_texture };

    QCamera camera;
    QCameraImageCapture capture{ &camera };

    QVideoFrame last_frame;
    bool has_frame;

};
