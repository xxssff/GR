#pragma once

#include "..\GRCommons\GRException.h"

namespace GR
{
namespace math
{

class GRMatriceException : public GRException
{
public:
    GRMatriceException();
    ~GRMatriceException();
    GRMatriceException( const char* message );
    GRMatriceException( std::string message );
};

}
}