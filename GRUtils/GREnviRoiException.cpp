#include "GREnviRoiException.h"


namespace GR
{
namespace utils
{

GREnviRoiException::GREnviRoiException(): GR::GRException( "A GREnviRoiException has been created.." )
{
}

GREnviRoiException::GREnviRoiException( const char* message ): GR::GRException( message )
{

}

GREnviRoiException::GREnviRoiException( std::string message ): GR::GRException( message )
{

}

GREnviRoiException::~GREnviRoiException()
{
}

}
}