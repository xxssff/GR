#include "GRInputStreamException.h"

namespace GR
{


GRInputStreamException::GRInputStreamException() : GRException( "A GRInputStreamException has been created.." )
{
}


GRInputStreamException::~GRInputStreamException()
{
}

GRInputStreamException::GRInputStreamException( const char* message ): GRException( message )
{

}

GRInputStreamException::GRInputStreamException( std::string message ) : GRException( message )
{

}

}