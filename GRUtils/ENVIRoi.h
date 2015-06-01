#pragma once

#include <string>

#include "GRColor.h"
#include "..\GRMath\GRMatrices.h"

namespace GR
{
namespace utils
{


class ENVIRoi
{
public:
    ENVIRoi();
    ~ENVIRoi();

    std::string name;
    int samples;
    GRColor* color;
    GR::math::Matrix* data;
};

}
}