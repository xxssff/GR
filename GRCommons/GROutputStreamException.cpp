#include "GROutputStreamException.h"

namespace GR
{

GROutputStreamException::GROutputStreamException(): GRException( "A new GROutputStreamException has been created.." )
{
}


GROutputStreamException::~GROutputStreamException()
{
}

GROutputStreamException::GROutputStreamException( const char* message ) : GRException( message )
{

}

GROutputStreamException::GROutputStreamException( std::string message ) : GRException( message )
{

}

}