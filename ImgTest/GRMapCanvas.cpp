#include "GRMapCanvas.h"
#include "Global.h"
#include "GRMapLayer.h"
#include "GRCoordinateTransform.h"
#include "GRSymbol.h"
#include "GRMarkerSymbol.h"
#include "GRLineSymbol.h"
#include "GRPolygonSymbol.h"


GRMapCanvas::GRMapCanvas( QWidget* parent /*= 0*/, const char* name /*= 0 */ )
    : QGraphicsView( parent )
{
    mapWindow = new QRect();
    coordXForm = new GRCoordinateTransform();
    bgColor = QColor( Qt::white );
    //setEraseColor( bgColor );
    setMouseTracking( true );
    drawing = false;
    dirty = true;
    pmCanvas = new QPixmap( width(), height() );
    setFocusPolicy( Qt::StrongFocus );
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
    GRSymbol *sym;
    QColor *fill;
    int red, green, blue;
    int d = layer->featureType();
    switch (  d )
    {
    case GR::WKBPoint:
    case GR::WKBMultiPoint:
        sym = new GRMarkerSymbol();
        break;
    case GR::WKBLineString:
    case GR::WKBMultiLineString:
        sym = new GRLineSymbol();
        break;
    case GR::WKBPolygon:
    case GR::WKBMultiPolygon:
        sym = new GRPolygonSymbol();
        red = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
        green =	1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
        blue = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
        fill = new QColor( red, green, blue );
        sym->setFillColor( *fill );
        break;
    }
    red = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
    green =	1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
    blue = 1 + ( int )( 255.0 * rand() / ( RAND_MAX + 1.0 ) );
    sym->setColor( QColor( red, green, blue ) );
    sym->setLineWidth( 1 );
    layers[layer->getLayerID()] = layer;
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

void GRMapCanvas::render()
{

}

void GRMapCanvas::clear()
{
    dirty = true;
    
}

void GRMapCanvas::zoomFullExtent()
{
    previousExtent = currentExtent;
    currentExtent = fullExtent;
    clear();
    render2();
}

void GRMapCanvas::zoomPreviousExtent()
{
    if ( previousExtent.width() > 0 )
    {
        GRRect tempRect = currentExtent;
        currentExtent = previousExtent;
        previousExtent = tempRect;
        clear();
        render2();
    }
}

GRMapLayer* GRMapCanvas::getZpos( int index )
{
    std::map<QString, GRMapLayer*>::iterator mi = layers.begin();
    while( mi != layers.end() )
    {
        GRMapLayer* ml = ( *mi ).second;
        if ( ml->z() == index )
        {
            return ml;
        }
        mi++;
    }
    return 0;
}

GRMapLayer* GRMapCanvas::getLayerByName( QString name )
{
    return layers[name];
}

int GRMapCanvas::layerCount()
{
    return layers.size();
}

void GRMapCanvas::freeze( bool frz /*= true */ )
{
    frozen = frz;
}

void GRMapCanvas::remove( QString key )
{
    std::map<QString, GRMapLayer*>::iterator mi = layers.begin();
    while( mi != layers.end() )
    {
        if ( ( *mi ).first == key )
        {
            layers.erase( mi );
            return;
        }
        mi++;
    }
}

void GRMapCanvas::removeAll()
{
    layers.empty();
}

void GRMapCanvas::setDirty( bool _dirty )
{
    dirty = _dirty;
}

void GRMapCanvas::render2()
{
    QString msg = frozen ? "frozen" : "thawed";
    if ( !frozen && dirty )
    {
        if ( !drawing )
        {
            drawing = true;
            QPainter *paint = new QPainter();
            pmCanvas->fill( bgColor );
            paint->begin( pmCanvas );
            double muppX, muppY;
            muppX = currentExtent.height() / height();
            muppY = currentExtent.width() / width();
            m_mupp = muppY > muppX ? muppY : muppX;
            double dxmin, dxmax, dymin, dymax, whitespace;
            if ( muppY > muppX )
            {
                dymin = currentExtent.yMin();
                dymax = currentExtent.yMax();
                whitespace = ( ( width() * m_mupp ) - currentExtent.width() ) / 2;
                dxmin = currentExtent.xMin() - whitespace;
                dxmax = currentExtent.xMax() + whitespace;
            }
            else
            {
                dxmin = currentExtent.xMin();
                dxmax = currentExtent.xMax();
                whitespace = ( ( height() * m_mupp ) - currentExtent.height() ) / 2;
                dymin = currentExtent.yMin() - whitespace;
                dymax = currentExtent.yMax() + whitespace;
            }
            coordXForm->setParameters( m_mupp, dxmin, dymin, height() );
            currentExtent.setXmin( dxmin );
            currentExtent.setXmax( dxmax );
            currentExtent.setYmin( dymin );
            currentExtent.setYmax( dymax );
            std::list < QString >::iterator li = zOrder.begin();
            while ( li != zOrder.end() )
            {
                GRMapLayer *ml = layers[*li];
                if ( ml )
                {
                    if ( ml->visible() )
                    {
                        ml->draw( paint, &currentExtent, coordXForm );
                    }
                    li++;
                }
                
            }
            paint->end();
            drawing = false;
        }
        dirty = false;
        repaint();
    }
}

void GRMapCanvas::layerStateChange()
{
    if ( !frozen )
    {
        clear();
        render2();
    }
}

void GRMapCanvas::incrementZpos()
{

}

void GRMapCanvas::updateZpos()
{

}

void GRMapCanvas::mouseMoveEvent( QMouseEvent *e )
{

}

void GRMapCanvas::mousePressEvent( QMouseEvent *e )
{

}

void GRMapCanvas::mouseReleaseEvent( QMouseEvent *e )
{

}

void GRMapCanvas::resizeEvent( QResizeEvent *e )
{

}

void GRMapCanvas::paintEvent( QPaintEvent *pe )
{
    if ( !dirty )
    {
        //bitBlt( this, pe->rect().topLeft(), pmCanvas, pe->rect() );
    }
    else
    {
        if ( !drawing )
        {
            render2();
        }
    }
}

void GRMapCanvas::refresh()
{
    dirty = true;
    render2();
}
