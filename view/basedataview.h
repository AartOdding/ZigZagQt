#pragma once

#include <QGraphicsItem>


class OperatorView;
class BaseDataType;
class BaseDataView;

struct DataTypeInfo;


enum class DataViewGraphicsApi
{
    QPainter,
    OpenGL
};


struct DataViewTypeInfo
{
    std::string name;
    std::string library;
    const DataTypeInfo* data_type;
    DataViewGraphicsApi graphics_api;
    std::function<BaseDataView*(const BaseDataType*)> construct;
    // Library
    // Image
    // Version
    // Description
    // Author
    // License
    // Etc
};


class BaseDataView : public QGraphicsItem
{

public:

    BaseDataView();


    QRectF boundingRect() const override;

    void set_bounds(double x, double y, double w, double h);


    //virtual void draw(int res_x, int res_y) = 0;

private:

    // Arbitrary initial bounding box, will be changed by OperatorView calling set_bounds().
    QRectF bounds{ 0, 0, 10, 10 };


};
