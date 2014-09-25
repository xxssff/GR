#include "GRPoint.h"
#include <QtCore/QString>
#include <QtCore/QTextStream>

/// <summary>
/// Initializes a new instance of the <see cref="GRPoint"/> class.
/// </summary>
GRPoint::GRPoint( void )
{
}

/// <summary>
/// Initializes a new instance of the <see cref="GRPoint"/> class.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
GRPoint::GRPoint( double x, double y )
{
    m_x = x;
    m_y = y;
    
}


/// <summary>
/// Finalizes an instance of the <see cref="GRPoint"/> class.
/// </summary>
GRPoint::~GRPoint( void )
{
}

/// <summary>
/// Xs to int.
/// </summary>
/// <returns>int.</returns>
int GRPoint::xToInt()
{
    return ( int )m_x;
}

/// <summary>
/// Ys to int.
/// </summary>
/// <returns>int.</returns>
int GRPoint::yToInt()
{
    return ( int )m_y;
}

/// <summary>
/// Strings the rep.
/// </summary>
/// <returns>QString.</returns>
QString GRPoint::stringRep() const
{
    QString rep;
    /*QTextStream ot( &rep );
    ot.precision( 12 );
    ot << m_x << ", " << m_y;*/
    return rep;
}

/// <summary>
/// Operator==s the specified other.
/// </summary>
/// <param name="other">The other.</param>
/// <returns>bool.</returns>
bool GRPoint::operator==( const GRPoint &other )
{
    if ( ( other.x() == m_x ) && ( other.y() == m_y ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// <summary>
/// Operator!=s the specified other.
/// </summary>
/// <param name="other">The other.</param>
/// <returns>bool.</returns>
bool GRPoint::operator!=( const GRPoint &other )
{
    if ( ( other.x() == m_x ) && ( other.y() == m_y ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/// <summary>
/// Operator=s the specified other.
/// </summary>
/// <param name="other">The other.</param>
/// <returns>GRPoint &.</returns>
GRPoint& GRPoint::operator=( const GRPoint &other )
{
    if ( &other != this )
    {
        m_x = other.x();
        m_y = other.y();
    }
    return *this;
}
