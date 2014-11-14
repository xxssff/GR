#include "GRRenderer.h"

#include <QtCore/QMutexLocker>
#include <QtCore/QDebug>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainter>
#include <QtCore/QCoreApplication>

#include "GRCoordinateTransform.h"
#include "GRScaleCalculator.h"

GRRenderer::GRRenderer()
{
    mOverview = false;
    mDrawing = false;
}


GRRenderer::~GRRenderer( void )
{
}

/// <summary>
/// Start rendering.
/// </summary>
/// <param name="painter">The painter.</param>
/// <param name="forceWidthScale">Force a specific scale factor for line widths and marker sizes.</param>
void GRRenderer::render( QPainter* painter, double *forceWidthScale /*= 0 */ )
{
    QMutexLocker renderLock( &mRenderMutex );
    qDebug() << "=====Rendering=========";
    
    QPaintDevice* thePaintDevice = painter->device();
    if ( !thePaintDevice )
    {
        return;
    }
    
    // wait
    if ( mDrawing )
    {
        qDebug() << "already rendering!";
        QCoreApplication::processEvents();
    }
    if ( mDrawing )
    {
        qDebug() << "still rendering - skipping";
        return;
    }
    mDrawing = true;
    
    GRCoordinateTransform* ct;
    
    if ( mOverview )
    {
        // mRenderContext.setDrawEditingInformation(!mOverview);
    }
    mRenderContext.setPainter( painter );
    mRenderContext.setCoordinateTransform( 0 );
    mRenderContext.setRenderingStopped( false );
    
    //calculate scale factor
    //use the specified dpi and not those from the paint device
    //because sometimes QPainter units are in a local coord sys (e.g. in case of QGraphicsScene)
    double sceneDpi = mScaleCalculator->dpi();
    double scaleFactor = 1.0;
    
    if ( mOutputUnits == GRRenderer::Millimeters )
    {
        if ( forceWidthScale )
        {
            scaleFactor = *forceWidthScale;
        }
        else
        {
            scaleFactor = sceneDpi / 25.4;
        }
    }
    double rasterScaleFactor = ( thePaintDevice->logicalDpiX() + thePaintDevice->logicalDpiY() ) / 2.0 / sceneDpi;
    // need to finish.................
}

