#pragma once

#include <QGraphicsItem>

#include "model/parameter/baseparameter.h"


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
    DataViewGraphicsApi graphics_api;
    std::function<BaseDataView*(BaseOperator*)> construct;
    // Library
    // Image
    // Version
    // Description
    // Author
    // License
    // Etc
};

inline bool operator==(const DataViewTypeInfo& t1, const DataViewTypeInfo& t2)
{
    return t1.name == t2.name && t1.library == t2.library && t1.graphics_api == t2.graphics_api;
}

class BaseDataView : public QGraphicsItem,
                     public BaseParameter
{

public:

    BaseDataView(BaseOperator * parent_operator, const DataViewTypeInfo * type_info);


    QRectF boundingRect() const override;

    void set_bounds(double x, double y, double w, double h);

    const DataViewTypeInfo * get_type();

    //virtual void draw(int res_x, int res_y) = 0;

private:

    const DataViewTypeInfo * type_info;

    // Arbitrary initial bounding box, will be changed by OperatorView calling set_bounds().
    QRectF bounds{ 0, 0, 10, 10 };


};
