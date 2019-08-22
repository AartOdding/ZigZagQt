#pragma once


#include <QWidget>


class ParameterEditor;



class ParameterPanelHeader : public QWidget
{
public:

    ParameterPanelHeader(ParameterEditor* editor);

protected:

    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;


private:

    ParameterEditor& editor;

    int start_y;
    int offset_y;

};

