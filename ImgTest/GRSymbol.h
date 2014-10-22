#pragma once

#include <QtGui/QColor>

class GRSymbol
{
public:
    GRSymbol( QColor color = QColor( 0, 0, 0 ) );
    GRSymbol( GRSymbol& rl );
    ~GRSymbol();
    
    void setColor( const QColor c ) {m_color = c;};
    void setFillColor( const QColor c ) {m_fillColor = c;};
    void setLineWidth( const int width ) {m_lineWidth = width;};
    QColor color() const {return m_color;};
    QColor fillColor() const {return m_fillColor;};
    int lineWidth() const {return m_lineWidth;};
    
    bool operator==( const GRSymbol& rl );
    GRSymbol& operator=( const GRSymbol& rl );
    
private:
    QColor m_color;
    QColor m_fillColor;
    int m_lineWidth;
};
