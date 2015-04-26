#pragma once

#include <string>
#include <exception>


namespace GR
{

class GRException : std::exception
{
public:
    GRException();
    GRException( const char* message );
    GRException( std::string message );

    virtual ~GRException() throw();

    virtual const char* what() const throw();

protected:
    std::string msgs;
};

}

