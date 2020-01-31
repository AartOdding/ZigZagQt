#pragma once

#include "view/opengldataview.h"
#include "texturedata.h"
#include "textureviewwindow.h"

#include <QObject>
#include <QPointer>
#include <QOpenGLShaderProgram>

#include "model/parameter/ButtonParameter.hpp"


class OperatorView;


class TextureView : public OpenGLDataView
{
    Q_OBJECT

public:

    TextureView(BaseOperator* parentOperator, TextureData* viewedTexture);

    ~TextureView() override;

    void paint_opengl(int res_x, int res_y) override;

    void parameterChangedEvent(const BaseParameter* parameter) override;

    static BaseDataView* create(BaseOperator* m_parentOperator);

    static const inline DataViewTypeInfo Type { "Texture View", "Texture", DataViewGraphicsApi::OpenGL, &create };

public slots:

    void update_view();

private:

    friend class TextureViewWindow;

    ButtonParameter open_window_button{ this, "Open in Separate Window" };

    const BaseOperator* m_parentOperator;
    TextureData* m_viewedTexture = nullptr;

    QPointer<TextureViewWindow> window;

    static bool gpu_resources_initialized;
    static QOpenGLShaderProgram shader;
    static GLuint vao;
    static GLuint vbo;

};
