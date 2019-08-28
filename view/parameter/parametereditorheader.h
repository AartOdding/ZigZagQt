#pragma once


#include <QWidget>


class ParameterEditor;



class ParameterEditorHeader : public QWidget
{
public:

    ParameterEditorHeader(ParameterEditor* editor);

protected:

    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;


private:

    ParameterEditor& editor;

    int start_y;
    int offset_y;

};

