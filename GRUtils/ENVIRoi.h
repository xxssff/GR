#pragma once

#include <string>

#include "GRColor.h"
#include "..\GRMath\Matrix.h"

namespace GR
{
namespace GRUtils
{


class ENVIRoi
{
public:
    std::string name;
    int samples;
    GRColor* color;
    GRMath::Matrix* data;
};

}
}