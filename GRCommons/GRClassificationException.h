#pragma once

#include "GRException.h"

namespace GR
{

class GRClassificationException : public GRException
{
public:
    GRClassificationException();
    GRClassificationException( const char* message );
    GRClassificationException( std::string message );
    ~GRClassificationException();
};

}


