#include "GRClassificationException.h"

namespace GR
{

GRClassificationException::GRClassificationException(): GRException( "A GRClassificationException has been created.." )
{
}


GRClassificationException::~GRClassificationException()
{
}

GRClassificationException::GRClassificationException( const char* message ): GRException( message )
{
}

GRClassificationException::GRClassificationException( std::string message ) : GRException( message )
{
}

}
