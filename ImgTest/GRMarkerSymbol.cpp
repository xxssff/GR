#include "GRMarkerSymbol.h"


GRMarkerSymbol::GRMarkerSymbol( void )
{
}


GRMarkerSymbol::~GRMarkerSymbol( void )
{
}

bool GRMarkerSymbol::operator==( GRMarkerSymbol& rl )
{
    if ( rl.color() == this->color() )
    {
        return true;
    }
    return false;
}

GRMarkerSymbol& GRMarkerSymbol::operator=( GRMarkerSymbol& rl )
{
    GRSymbol s = rl;
    return ( GRMarkerSymbol& )s;
}
