#include "GRSymbol.h"

GRSymbol::GRSymbol( QColor color /*= QColor( 0, 0, 0 ) */ )
    : m_color( color )
{

}

GRSymbol::GRSymbol( GRSymbol& rl )
    : m_color( rl.color() ),
      m_fillColor( rl.fillColor() ),
      m_lineWidth( rl.lineWidth() )
{
}

GRSymbol::~GRSymbol()
{

}

bool GRSymbol::operator==( const GRSymbol& rl )
{
    if ( rl.color() == this->color() &&
            rl.fillColor() == this->fillColor() &&
            rl.lineWidth() == this->lineWidth() )
    {
        return true;
    }
    return false;
}

GRSymbol& GRSymbol::operator=( const GRSymbol& rl )
{
    if( &rl != this )
    {
        m_color = rl.color();
        m_fillColor = rl.fillColor();
        m_lineWidth = rl.lineWidth();
    }
    return *this;
}

