#include "GRRect.h"


GRRect::~GRRect( void )
{
}

void GRRect::normalize()
{
    double temp;
    if ( xmin > xmax )
    {
        temp = xmin;
        xmin = xmax;
        xmax = temp;
    }
    if ( ymin > ymax )
    {
        temp = ymin;
        ymin = ymax;
        ymax = temp;
    }
}

double GRRect::width() const
{
    return xmax - xmin;
}

double GRRect::height() const
{
    return ymax - ymin;
}

GRPoint GRRect::center() const
{
    GRPoint centerPoint;
    centerPoint.setX( ( xmax - xmin ) / 2 );
    centerPoint.setY( ( ymax - ymin ) / 2 );
    return centerPoint;
}

void GRRect::scale( double scaleFactor, GRPoint *c /*= 0 */ )
{
    double centerX, centerY;
    if ( c )
    {
        centerX = c->x();
        centerY = c->y();
    }
    else
    {
        centerX = xmin + width() / 2;
        centerY = ymin + height() / 2;
    }
    double newWidth = width() * scaleFactor;
    double newHeight = height() * scaleFactor;
    xmin = centerX - newWidth / 2.0;
    xmax = centerX + newWidth / 2.0;
    ymin = centerY - newHeight / 2.0;
    ymax = centerY + newHeight / 2.0;
    
}

void GRRect::expand( double scaleFactor, GRPoint* c /*= 0 */ )
{
    double centerX, centerY;
    if ( c )
    {
        centerX = c->x();
        centerY = c->y();
    }
    else
    {
        centerX = xmin + width() / 2;
        centerY = ymin + height() / 2;
    }
    double newWidth = width() * scaleFactor;
    double newHeight = height() * scaleFactor;
    xmin = centerX - newWidth;
    xmax = centerX + newWidth;
    ymin = centerY -  newHeight;
    ymax = centerY +  newHeight;
}

QString GRRect::stringRep() const
{
    QString tmp;
    QString rep = tmp.setNum( xmin );;
    rep += " ";
    rep += tmp.setNum( ymin );
    rep += ",";
    rep += tmp.setNum( xmax );
    rep += " ";
    rep += tmp.setNum( ymax );
    return rep;
}

GRRect::GRRect( double xmin /*= 0*/, double ymin /*= 0*/, double xmax /*= 0*/, double ymax /*= 0 */ )
    : xmin( xmin ),
      ymin( ymin ),
      xmax( xmax ),
      ymax( ymax )
{

}

GRRect::GRRect( GRPoint p1, GRPoint p2 )
{
    xmin = p1.x();
    xmax = p2.x();
    ymin = p1.y();
    ymax = p2.y();
    normalize();
}


bool GRRect::operator==( const GRRect& other )
{
    if ( ( xmin == other.xMin() ) && ( xmax == other.xMax() )
            && ( ymin == other.yMin() ) && ymax == other.yMax() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

GRRect& GRRect::operator=( const GRRect& other )
{
    if ( *this == other )
    {
        return *this;
    }
    else
    {
        xmin = other.xMin();
        ymin = other.yMin();
        xmax = other.xMax();
        ymax = other.yMax();
    }
    return *this;
}
