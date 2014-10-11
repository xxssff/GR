#include "GRMapCanvas.h"
#include "Global.h"
#include "GRMapLayer.h"

GRMapCanvas::GRMapCanvas( QWidget* parent /*= 0*/, const char* name /*= 0 */ )
{

}


/// <summary>
/// Finalizes an instance of the <see cref="GRMapCanvas"/> class.
/// </summary>
GRMapCanvas::~GRMapCanvas( void )
{
}

void GRMapCanvas::setLegend( GRLegend* legend )
{
    mapLegend = legend;
}

GRRect GRMapCanvas::extent()
{
    return currentExtent;
}

void GRMapCanvas::setExtent( GRRect rec )
{
    currentExtent = rec;
}

void GRMapCanvas::setMapTool( int tool )
{
    mapTool = tool;
}

void GRMapCanvas::setbgColor( const QColor& _newVal )
{
    bgColor = _newVal;
}

void GRMapCanvas::updateFullExtent( GRRect rect )
{
    if ( rect.xMin() < fullExtent.xMin() )
    {
        fullExtent.setXmin( rect.xMin() );
    }
    if ( rect.xMax() > fullExtent.xMax() )
    {
        fullExtent.setXmax( rect.xMax() );
    }
    if ( rect.yMin() < fullExtent.yMin() )
    {
        fullExtent.setYmin( rect.yMin() );
    }
    if ( rect.yMax() > fullExtent.yMax() )
    {
        fullExtent.setYmax( rect.yMax() );
    }
}

double GRMapCanvas::mupp()
{
    return m_mupp;
}

void GRMapCanvas::addLayer( GRMapLayer* layer )
{

    //TODO: here need a symbol to paint the layer
    QColor *fill;
    int red, green, blue;
    switch ( layer->featureType() )
    {
    case GR::WKBPoint:
    case GR::WKBMultiPoint:
        break;
    case GR::WKBLineString:
    case GR::WKBMultiLineString:
        break;
    case GR::WKBPolygon:
    case GR::WKBMultiPolygon:
    
        red = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
        green =	1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
        blue = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
        fill = new QColor( red, green, blue );
        
        break;
    }
    red = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
    green =	1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
    blue = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
    
    // update the extent if warranted
    if ( layers.size() == 1 )
    {
        fullExtent = layer->extent();
        fullExtent.scale( 1.1 );
        currentExtent = fullExtent;
    }
    updateFullExtent( layer->extent() );
    incrementZpos();
    layer->setZ( layers.size() - 1 );
    updateZpos();
    zOrder.push_back( layer->getLayerID() );
    connect( layer, SIGNAL( visibilityChanged() ), this, SLOT( layerStateChange() ) );
    dirty = true;
}
