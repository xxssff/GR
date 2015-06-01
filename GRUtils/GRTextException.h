#pragma once

#include "..\GRCommons\GRException.h"

namespace GR
{
namespace utils
{


class GRTextException : public GRException
{
public:
    GRTextException();
    ~GRTextException();
    GRTextException( const char* message );
    GRTextException( std::string message );
};

}
}

