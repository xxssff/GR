#include "GRLineSymbol.h"


GRLineSymbol::GRLineSymbol( void )
{
}


GRLineSymbol::~GRLineSymbol( void )
{
}

bool GRLineSymbol::operator==( GRLineSymbol& rl )
{
    if ( rl.color() == this->color() &&
            rl.lineWidth() == this->lineWidth() )
    {
        return true;
    }
    return false;
}

GRLineSymbol& GRLineSymbol::operator=( GRLineSymbol& rl )
{
    if ( &rl != this )
    {
        this->setColor( rl.color() );
        this->setFillColor( rl.fillColor() );
        this->setLineWidth( rl.lineWidth() );
    }
    return *this;
}
