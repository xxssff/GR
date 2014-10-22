#pragma once


#include "GRSymbol.h"


class GRLineSymbol : public GRSymbol
{
public:
    GRLineSymbol( void );
    ~GRLineSymbol( void );
    
    bool operator==( GRLineSymbol& rl );
    GRLineSymbol& operator=( GRLineSymbol& rl );
};

