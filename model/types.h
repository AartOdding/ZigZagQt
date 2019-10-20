#pragma once

#include "zigzaglib/zz_type.h"



enum class IDs : zz::TypeID
{
    // Parameter Type ID's:
    IntPar       = 2001,
    Int2Par      = 2002,
    Int3Par      = 2003,
    Int4Par      = 2004,
    FloatPar     = 2005,
    Float2Par    = 2006,
    Float3Par    = 2007,
    Float4Par    = 2008,
    EnumPar      = 2009,
    ButtonPar    = 2010,
    Matrix3x3Par = 2011,
    Matrix4x4Par = 2012,

    // Parameter Component Type ID's
    IntParComponent   = 3001,
    FloatParComponent = 3002,
    TextParComponent  = 3002,
    RefParComponent   = 3003
};



