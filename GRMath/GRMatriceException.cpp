#include "GRMatriceException.h"

namespace GR
{
namespace math
{

GRMatriceException::GRMatriceException(): GRException( "A new GRMatriceException has been created.." )
{
}

GRMatriceException::GRMatriceException( const char* message ): GRException( message )
{

}

GRMatriceException::GRMatriceException( std::string message ) : GRException( message )
{

}


GRMatriceException::~GRMatriceException()
{
}

}
}