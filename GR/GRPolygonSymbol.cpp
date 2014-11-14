#include "GRPolygonSymbol.h"


GRPolygonSymbol::GRPolygonSymbol( void )
{
}


GRPolygonSymbol::~GRPolygonSymbol( void )
{
}

bool GRPolygonSymbol::operator==( const GRPolygonSymbol &rl )
{
    if ( rl.color() == this->color() &&
            rl.fillColor() == this->fillColor() &&
            rl.lineWidth() == this->lineWidth() )
    {
        return true;
    }
    return false;
}

GRPolygonSymbol& GRPolygonSymbol::operator=( const GRPolygonSymbol &rl )
{
    if ( &rl != this )
    {
        this->setColor( rl.color() );
        this->setFillColor( rl.fillColor() );
        this->setLineWidth( rl.lineWidth() );
    }
    return *this;
}
