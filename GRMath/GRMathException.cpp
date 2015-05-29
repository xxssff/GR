#include "GRMathException.h"

namespace GR
{
namespace math
{

GRMathException::GRMathException(): GRException( "A GRMathException has been created.." )
{

}

GRMathException::GRMathException( const char* message ): GRException( message )
{

}

GRMathException::GRMathException( std::string message ): GRException( message )
{

}

GRMathException::~GRMathException()
{
}


}
}