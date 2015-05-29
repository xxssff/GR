#pragma once


#include "GRException.h"

namespace GR
{

#include "GRException.h"

class GROutputStreamException : public GRException
{
public:
    GROutputStreamException() ;
    ~GROutputStreamException();
    GROutputStreamException( const char* message );
    GROutputStreamException( std::string message );
};

}


