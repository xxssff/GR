#include "GRCoordinateTransform.h"

#include <QtCore/QPoint>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include "GRPoint.h"




GRCoordinateTransform::~GRCoordinateTransform( void )
{
}

GRCoordinateTransform::GRCoordinateTransform( double mupp /*= 0*/, double ymax /*= 0*/, double ymin /*= 0*/, double xmin /*= 0 */ )
    : mapUnitsPerPixel( mupp ),
      yMax( ymax ),
      yMin( ymin ),
      xMin( xmin )
{

}

GRPoint GRCoordinateTransform::toDeviceCoordinates( GRPoint p )
{
    // transform x
    double dx = ( p.x() - xMin ) / mapUnitsPerPixel;
    double dy = yMax - ( p.y() - yMin ) / mapUnitsPerPixel;
    
    return GRPoint( dx, dy );
}

GRPoint GRCoordinateTransform::toDeviceCoordinates( double x, double y )
{
    return toDeviceCoordinates( GRPoint( x, y ) );
}

GRPoint GRCoordinateTransform::toMapCoordinates( QPoint p )
{
    GRPoint mapPt = toMapPoint( p.x(), p.y() );
    return GRPoint( mapPt );
}

GRPoint GRCoordinateTransform::toMapCoordinates( int x, int y )
{
    return toMapPoint( x, y );
}

GRPoint GRCoordinateTransform::toMapPoint( int x, int y )
{
    double mx = x * mapUnitsPerPixel + xMin;
    double my = -1 * ( ( y - yMax )  * mapUnitsPerPixel - yMin );
    return GRPoint( mx, my );
}

void GRCoordinateTransform::setParameters( double mupp, double xmin, double ymin, double ymax )
{
    mapUnitsPerPixel = mupp;
    xMin = xmin;
    yMin = ymin;
    yMax = ymax;
}
