#pragma once

#include <string>

#include "GRColor.h"
#include "..\GRMath\Matrix.h"

namespace GR
{
namespace utils
{


class ENVIRoi
{
public:
    std::string name;
    int samples;
    GRColor* color;
    math::GRMatrix* data;
};

}
}