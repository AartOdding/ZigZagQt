#pragma once

#include <QGraphicsItem>

#include "model/BaseZigZagObject.hpp"


class OperatorView;
class BaseOperator;
class BaseDataType;
class BaseDataView;

struct DataTypeDescription;


enum class DataViewGraphicsApi
{
    QPainter,
    OpenGL
};


struct DataViewDescription
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

inline bool operator==(const DataViewDescription& t1, const DataViewDescription& t2)
{
    return t1.name == t2.name && t1.library == t2.library && t1.graphics_api == t2.graphics_api;
}



class BaseDataView : public BaseZigZagObject,
                     public QGraphicsItem
{
    Q_OBJECT

public:

    BaseDataView(BaseOperator * parent_operator, const DataViewDescription * type_info);

    virtual ~BaseDataView();

    QRectF boundingRect() const final;

    void set_bounds(double x, double y, double w, double h);

    const DataViewDescription * get_type();

    //virtual void draw(int res_x, int res_y) = 0;

private:

    const DataViewDescription * type_info;

    // Arbitrary initial bounding box, will be changed by OperatorView calling set_bounds().
    QRectF bounds{ 0, 0, 10, 10 };


};
