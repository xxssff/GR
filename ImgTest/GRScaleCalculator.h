#pragma once

#include "Global.h"
#include "GRRect.h"


class GRScaleCalculator
{
public:
    GRScaleCalculator( double dpi = 0, GR::UnitType mapUnits = GR::Meters );
    ~GRScaleCalculator( void );
    
    // Getter and setter
    double dpi() {return mDpi;};
    void setDpi( const double dpi ) {mDpi = dpi;};
    GR::UnitType mapUnits() const {return mMapUnits;}
    void setMapUnits( const GR::UnitType mapUnits ) {mMapUnits = mapUnits;};
    // Calculate the scale
    double calculate( const GRRect& mapExtent, int canvasWidth );
    // Calculate the distance between two points in geographic coordinates.
    // Used to calculate scale for map views with geographic ( decimal degree ) data.
    double calculateGeographicDistance( const GRRect& mapExtent );
private:

    double mDpi;
    
    GR::UnitType mMapUnits;
    
};

