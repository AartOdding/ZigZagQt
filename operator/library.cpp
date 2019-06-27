#include "operator/library.h"
#include "operator/basetop.h"
#include "operator/shadertop.h"
#include "programmodel.h"



Library::Library(QObject *parent)
    : QObject(parent)
{

}

BaseTOP* Library::create(const QString& operator_type, ProgramModel& model)
{
    if (operator_type == "sine")
    {
        auto op = new ShaderTOP(model);
        // set proper source code
        return op;
    }
    else if (operator_type == "square")
    {
        auto op = new ShaderTOP(model);
        // set proper source code
        return op;
    }
    else if (operator_type == "average")
    {
        auto op = new ShaderTOP(model);
        // set proper source code
        return op;
    }
}
