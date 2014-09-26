#pragma once

class GRPoint;
class QString;
class QPoint;

// This class is for doing transforms between map coordinates and device coordinates.
class GRCoordinateTransform
{
public:
    GRCoordinateTransform( double mupp = 0, double ymax = 0, double ymin = 0, double xmin = 0 );
    ~GRCoordinateTransform( void );
    
    GRPoint toDeviceCoordinates( GRPoint p );
    GRPoint toDeviceCoordinates( double x, double y );
    
    GRPoint toMapCoordinates( QPoint p );
    GRPoint toMapCoordinates( int x, int y );
    GRPoint toMapPoint( int x, int y );
    
    void setMapUnitsPerPixel( double mupp );
    void setYmax( double ymax ) {yMax = ymax;};
    void setYmin( double ymin ) {yMin = ymin;};
    void setXmax( double xmax ) {xMax = xmax;};
    void setXmin( double xmin ) {xMin = xmin;};
    // set parameters for use in transforming coordinates
    void setParameters( double mupp, double xmin, double ymin, double ymax );
    QString showParameters();
    
private:
    double mapUnitsPerPixel;
    double yMax;
    double yMin;
    double xMin;
    double xMax;
};

