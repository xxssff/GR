#pragma once

#include <string>
#include <vector>

namespace GR
{
namespace utils
{


class GRTextUtils
{
public:
    GRTextUtils();
    ~GRTextUtils();

    bool lineStart( std::string line, char token );
    void tokenizeString( std::string line, char token, std::vector<std::string>* tokens, bool ignoreDuplicateTokens, bool trimWhitespace = false );
    std::vector<std::string> split( std::string str, std::string pattern );
    bool blankline( std::string line );
};



}
}


