#include "GRException.h"

namespace GR
{

GRException::GRException(): std::exception()
{
    msgs = "A GRException has been created..";
}

GRException::GRException( const char* message ): exception()
{
    msgs = std::string( message );
}

GRException::GRException( std::string message ): std::exception()
{
    msgs = message;
}

GRException::~GRException()
{
}

const char* GRException::what() const throw()
{
    return msgs.c_str();
}

}
