#pragma once

#include <unordered_map>

#include <QWidget>
#include <QSizeGrip>


class BaseParameter;
class OperatorView;

class QLabel;
class QFormLayout;
class QGraphicsScene;


class ParameterEditor;



class ParameterEditorHeader : public QWidget
{
public:

    ParameterEditorHeader(ParameterEditor& editor);

protected:

    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;


private:

    ParameterEditor& editor;

    int start_y;
    int offset_y;

};



class ParameterEditor : public QWidget
{
    Q_OBJECT

public:

    ParameterEditor(QOpenGLWidget* gl);

    QSize sizeHint() const override { return QSize(400, 500); }

    void set_scene(QGraphicsScene* scene);


protected:

    void resizeEvent(QResizeEvent *event) override;


public slots:

    void on_selection_changed();


signals:

private:

    void build_up_ui();
    void tear_down_ui();

    QGraphicsScene* scene = nullptr;
    OperatorView* focus_op = nullptr;
    QFormLayout * form_layout = nullptr;

    QSizeGrip size_grip;

    ParameterEditorHeader header;
};

