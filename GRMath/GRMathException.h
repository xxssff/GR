#pragma once

#include "..\GRCommons\GRException.h"

namespace GR
{
namespace math
{


class GRMathException : public GRException
{
public:
    GRMathException();
    ~GRMathException();

    GRMathException( const char* message );
    GRMathException( std::string message );
};

}
}

