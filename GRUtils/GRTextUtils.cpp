#include "GRTextUtils.h"
#include "GRTextException.h"

namespace GR
{
namespace utils
{

GRTextUtils::GRTextUtils()
{
}


GRTextUtils::~GRTextUtils()
{
}

bool GRTextUtils::lineStart( std::string line, char token )
{
    int lineLength = line.length();
    for ( int i = 0; i < lineLength; i++ )
    {
        if ( line.at( i ) == ' ' | line.at( i ) == '\t' | line.at( i ) == '\n' )
        {
            // spaces and tabs at the beginning of a line can be ignored.
        }
        else if ( line.at( i ) == token )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void GRTextUtils::tokenizeString( std::string line, char token, std::vector<std::string>* tokens, bool ignoreDuplicateTokens, bool trimWhitespace )
{
    tokens = &( split( line, std::string( &token ) ) );
}

std::vector<std::string> GRTextUtils::split( std::string str, std::string pattern )
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size = str.size();

    for ( int i = 0; i < size; i++ )
    {
        pos = str.find ( pattern, i );
        if ( pos < size )
        {
            std::string s = str.substr ( i, pos - i );
            result.push_back ( s );
            i = pos + pattern.size() - 1;
        }
    }

    std::vector<std::string>::iterator iter;
    for ( iter = result.begin(); iter != result.end(); )
    {
        if ( *iter == " " || *iter == "" )
        {
            iter = result.erase( iter );
        }
        else
        {
            iter++;
        }
    }

    return result;
}

bool GRTextUtils::blankline( std::string line )
{
    int lineLength = line.length();
    if( lineLength == 1 )
    {
        return true;
    }
    else
    {
        for( int i = 0; i < lineLength; i++ )
        {
            if( line.at( i ) == ' ' | line.at( i ) == '\t' | line.at( i ) == '\n' )
            {
                // spaces and tabs at the beginning of a line can be ignored.
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

}
}