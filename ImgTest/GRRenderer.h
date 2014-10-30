#pragma once

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMutex>

class QPainter;
class GRScaleCalculator;

#include "GRRect.h"
#include "GRRenderContext.h"

// Base class for all renderers
class GRRenderer : public QObject
{
    Q_OBJECT
    
public:

    // Output units for pen width and point marker width/height
    enum OutputUnits
    {
        Millimeters,
        Pixels
    };
    
    GRRenderer();
    ~GRRenderer();
    
    // getters and setters
    double mapUnitsPerPixel() const {return mMapUnitsPerPixel;};
    void setMapUnitsPerPixel( const double value ) {mMapUnitsPerPixel = value;};
    double scale() const {return mScale;};
    void setScale( const double value ) {mScale = value;};
    GRRect currentExtent() const {return mExtent;};
    void setCurrentExtent( const GRRect rect ) {mExtent = rect;};
    GRRect lastExtent() const {return mLastExtent;};
    void setLastExtent( const GRRect rect ) {mLastExtent = rect;};
    GRRect fullExtent() const {return mFullExtent;};
    void setFullExtent( const GRRect rect ) {mFullExtent = rect;};
    bool hasOverview()const {return mOverview;};
    void setOverview( const bool value ) {mOverview = value;};
    QStringList layerSet() const {return mLayerSet;};
    void setLayerSet( const QStringList newSet ) {mLayerSet = newSet;};
    
    void render( QPainter* painter, double *forceWidthScale = 0 );
    
private:
    double mMapUnitsPerPixel;
    double mScale;
    GRRect mExtent;
    GRRect mLastExtent;
    GRRect mFullExtent;
    bool mOverview;
    QStringList mLayerSet;
    QMutex mRenderMutex;
    GRRenderContext mRenderContext;
    bool mDrawing;
    OutputUnits mOutputUnits;
    GRScaleCalculator* mScaleCalculator;
};

