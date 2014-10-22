#pragma once

#include "GRSymbol.h"

class GRMarkerSymbol: public GRSymbol
{
public:
    GRMarkerSymbol();
    ~GRMarkerSymbol();
    
    bool operator==( GRMarkerSymbol& rl );
    GRMarkerSymbol& operator=( GRMarkerSymbol& rl );
};

