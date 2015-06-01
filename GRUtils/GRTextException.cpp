#include "GRTextException.h"

namespace GR
{
namespace utils
{


GRTextException::GRTextException() : GR::GRException( "A GRTextException has been created.." )
{
}

GRTextException::GRTextException( const char* message ) : GR::GRException( message )
{

}
GRTextException::GRTextException( std::string message ) : GR::GRException( message )
{

}

GRTextException::~GRTextException()
{
}

}
}