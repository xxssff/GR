#include "GRScaleCalculator.h"

#include <QtCore/QtDebug>

GRScaleCalculator::GRScaleCalculator( double dpi /*= 0*/, GR::UnitType mapUnits /*= GR::Meters */ )
    : mDpi( dpi ), mMapUnits( mapUnits )
{

}


GRScaleCalculator::~GRScaleCalculator( void )
{
}

double GRScaleCalculator::calculate( const GRRect& mapExtent, int canvasWidth )
{
    double conversionFactor = 0;
    double delta = 0;
    
    switch( mMapUnits )
    {
    case GR::Meters:
        conversionFactor = 39.3700787;
        delta = mapExtent.xMax() - mapExtent.xMin();
        break;
    case GR::Feet:
        conversionFactor = 12.0;
        delta = mapExtent.xMax() - mapExtent.xMin();
        break;
    case GR::DecimalDegrees:
        // degrees require conversion to meters first
        conversionFactor = 39.3700787;
        delta = calculateGeographicDistance( mapExtent );
        break;
    case GR::DegreesMinutesSeconds:
        // degrees require conversion to meters first
        conversionFactor = 39.3700787;
        delta = calculateGeographicDistance( mapExtent );
        break;
    case GR::DegreesDecimalMinutes:
        // degrees require conversion to meters first
        conversionFactor = 39.3700787;
        delta = calculateGeographicDistance( mapExtent );
        break;
    default:
        Q_ASSERT( "bad map units" );
        break;
    }
    
    if ( canvasWidth == 0 || mDpi == 0 )
    {
        qDebug() <<  "Can't calculate scale from the input values" ;
        return 0;
    }
    double scale = ( delta * conversionFactor ) / ( ( double )canvasWidth / mDpi );
    return scale;
}

double GRScaleCalculator::calculateGeographicDistance( const GRRect& mapExtent )
{
    // need to calculate the x distance in meters
    // We'll use the middle latitude for the calculation
    // Note this is an approximation (although very close) but calculating scale
    // for geographic data over large extents is quasi-meaningless
    
    // The distance between two points on a sphere can be estimated
    // using the Haversine formula. This gives the shortest distance
    // between two points on the sphere. However, what we're after is
    // the distance from the left of the given extent and the right of
    // it. This is not necessarily the shortest distance between two
    // points on a sphere.
    //
    // The code below uses the Haversine formula, but with some changes
    // to cope with the above problem, and also to deal with the extent
    // possibly extending beyond +/-180 degrees:
    //
    // - Use the Halversine formula to calculate the distance from -90 to
    //   +90 degrees at the mean latitude.
    // - Scale this distance by the number of degrees between
    //   mapExtent.xMinimum() and mapExtent.xMaximum();
    // - For a slight improvemnt, allow for the ellipsoid shape of earth.
    
    
    // For a longitude change of 180 degrees
    double lat = ( mapExtent.yMax() + mapExtent.yMin() ) * 0.5;
    const static double rads = ( 4.0 * atan( 1.0 ) ) / 180.0;
    double a = pow( cos( lat * rads ), 2 );
    double c = 2.0 * atan2( sqrt( a ), sqrt( 1.0 - a ) );
    const static double ra = 6378000; // [m]
    // The eccentricity. This comes from sqrt(1.0 - rb*rb/(ra*ra)) with rb set
    // to 6357000 m.
    const static double e = 0.0810820288;
    double radius = ra * ( 1.0 - e * e ) /
                    pow( 1.0 - e * e * sin( lat * rads ) * sin( lat * rads ), 1.5 );
    double meters = ( mapExtent.xMax() - mapExtent.xMin() ) / 180.0 * radius * c;
    
    qDebug() <<  "Distance across map extent (m): " + QString::number( meters ) ;
    
    return meters;
}
