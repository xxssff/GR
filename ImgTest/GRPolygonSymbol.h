#pragma once

#include "GRSymbol.h"

class GRPolygonSymbol : public GRSymbol
{
public:
    GRPolygonSymbol();
    ~GRPolygonSymbol();
    
    bool operator==( const GRPolygonSymbol &r1 );
    GRPolygonSymbol& operator=( const GRPolygonSymbol &rl );
};

