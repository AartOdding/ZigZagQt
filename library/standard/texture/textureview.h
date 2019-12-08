#pragma once

#include "view/opengldataview.h"
#include "texturedata.h"
#include "textureviewwindow.h"

#include <QObject>
#include <QPointer>
#include <QOpenGLShaderProgram>

#include "model/parameter/buttonparameter.h"


class OperatorView;


class TextureView : public QObject,
                    public OpenGLDataView
{
    Q_OBJECT

public:

    TextureView(BaseOperator* parent_operator);

    ~TextureView() override;

    void paint_opengl(int res_x, int res_y) override;

    void parameterChangeEvent(const BaseParameter* parameter) override;

    static BaseDataView* create(BaseOperator* parent_operator);

    static const inline DataViewTypeInfo Type { "Texture View", "Texture", DataViewGraphicsApi::OpenGL, &create };

public slots:

    void update_view();

private:

    friend class TextureViewWindow;

    ButtonPar open_window_button{ this, "Open in Separate Window" };

    const BaseOperator* parent_operator;
    TextureData* viewed_texture = nullptr;

    QPointer<TextureViewWindow> window;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
