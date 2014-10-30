#pragma once

class QPainter;
class GRCoordinateTransform;

#include "GRRect.h"


class GRRenderContext
{
public:
    GRRenderContext();
    ~GRRenderContext();
    
    // getters and setters
    QPainter* painter() {return mPainter;};
    const QPainter* constPainter() const {return mPainter;};
    void setPainter( QPainter* painter ) {mPainter = painter;};
    GRCoordinateTransform* coordinateTransform() const {return mCoordinateTransform;};
    void setCoordinateTransform( GRCoordinateTransform* trans ) {delete mCoordinateTransform; mCoordinateTransform = trans;};
    const GRRect& extent() const {return mExtent;};
    void setExtent( const GRRect extent ) {mExtent = extent;}
    bool renderingStopped() const {return mRenderingStopped;};
    void setRenderingStopped( bool stopped ) {mRenderingStopped = stopped;}
    bool scaleFactor() const {return mScaleFactor;};
    void setScaleFactor( double factor ) {mScaleFactor = factor;}
    bool renderScale() const {return mRendererScale;};
    void setRasterScaleFactor( double factor ) {mRasterScaleFactor = factor;}
    bool rasterScaleFactor() const {return mRasterScaleFactor;};
    void setRendererScale( double scale ) {mRendererScale = scale;}
private:
    QPainter* mPainter;
    GRCoordinateTransform* mCoordinateTransform;
    GRRect mExtent;
    bool mRenderingStopped;
    double mScaleFactor;
    double mRendererScale;
    double mRasterScaleFactor;
    
};

