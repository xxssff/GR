#include "GRRenderContext.h"


GRRenderContext::GRRenderContext()
    : mPainter( 0 ),
      mCoordinateTransform( 0 ),
      mRenderingStopped( false ),
      mRasterScaleFactor( 1.0 ),
      mScaleFactor( 1.0 )
{
}


GRRenderContext::~GRRenderContext( void )
{
}
