#pragma once

#include "GRException.h"


namespace GR
{

class GRInputStreamException : public GRException
{
public:
    GRInputStreamException();
    ~GRInputStreamException();

    GRInputStreamException( const char* message );
    GRInputStreamException( std::string message );
};

}
