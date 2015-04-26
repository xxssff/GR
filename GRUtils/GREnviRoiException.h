#pragma once

#include "..\GRCommons\GRException.h"

namespace GR
{

namespace GRUtils
{

class GREnviRoiException: public GR::GRException
{
public:
    GREnviRoiException();
    GREnviRoiException( const char* message );
    GREnviRoiException( std::string message );
    ~GREnviRoiException();
};

}
}
