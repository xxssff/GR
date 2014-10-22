#include "GRShapeFileLayer.h"
#include "ogrsf_frmts.h"



GRShapeFileLayer::GRShapeFileLayer( QString baseName /*= 0*/, QString path /*= 0 */ )
    : GRMapLayer( VECTOR, baseName, path )
{
    //const char* filesour = ;
    ogrDataSource = OGRSFDriverRegistrar::Open( datasource.toStdString().c_str() );
    if ( ogrDataSource != NULL )
    {
        ogrLayer = ogrDataSource->GetLayer( 0 );
        OGREnvelope *ext = new OGREnvelope();
        ogrLayer->GetExtent( ext );
        layerExtent.setXmax( ext->MaxX );
        layerExtent.setXmin( ext->MinX );
        layerExtent.setYmax( ext->MaxY );
        layerExtent.setYmin( ext->MinY );
        // get the feature type
        OGRFeature *fType = ogrLayer->GetNextFeature();
        if ( fType )
        {
            OGRGeometry *geom = fType->GetGeometryRef();
            if ( geom )
            {
                feature = geom->getGeometryType();
            }
            else
            {
                valid = false;
            }
            delete fType;
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }
    
    if ( valid )
    {
        selected = new QVector<bool>( ogrLayer->GetFeatureCount(), false );
    }
    else
    {
        selected = 0;
    }
    // draw the selected feature in yellow
    selectionColor.setRgb( 255, 255, 0 );
}


GRShapeFileLayer::~GRShapeFileLayer( void )
{
}

bool GRShapeFileLayer::isValid()
{
    return true;
}

GRRect GRShapeFileLayer::bBoxOfSelected()
{
    double xmin = DBL_MAX; //edge coordinates of the bounding box
    double ymin = DBL_MAX;
    double xmax = DBL_MIN;
    double ymax = DBL_MIN;
    for( int i = 0; i < selected->count(); i++ )
    {
        if( ( *selected )[i] == true )
        {
            OGRFeature* fet = ogrLayer->GetFeature( i );
            OGRGeometry* geom = fet->GetGeometryRef();
            OGRwkbGeometryType type = geom->getGeometryType();
            
            OGREnvelope bbox;
            geom->getEnvelope( &bbox );
            if( bbox.MinX < xmin )
            {
                xmin = bbox.MinX;
            }
            if( bbox.MinY < ymin )
            {
                ymin = bbox.MinY;
            }
            if( bbox.MaxX > xmax )
            {
                xmax = bbox.MaxX;
            }
            if( bbox.MaxY > ymax )
            {
                ymax = bbox.MaxY;
            }
            
        }
    }
    
    GRRect rect( xmin, ymin, xmax, ymax );
    return rect;
}

int GRShapeFileLayer::endian()
{
    char *chkEndian = new char[4];
    memset( chkEndian, '\0', 4 );
    chkEndian[0] = 0xE8;
    int *ce = ( int * ) chkEndian;
    if ( 232 == *ce )
        return NDR;
    else
        return XDR;
}

void GRShapeFileLayer::identify( GRRect* rect )
{
    OGRGeometry *filter = new OGRPolygon();
    /*std::ostream wktExtent( 0 );
    wktExtent << "POLYGON((" << rect->stringRep() << "))" << std::ends;*/
    
    
}

void GRShapeFileLayer::select( int number )
{
    ( *selected )[number] = true;
}

void GRShapeFileLayer::select( GRRect* rect, bool lock )
{

}

void GRShapeFileLayer::removeSelection()
{
    for ( int i = 0; i < ( int )selected->size(); i++ )
    {
        ( *selected )[i] = false;
    }
}

void GRShapeFileLayer::triggerRepaint()
{
    emit repaintRequested();
}

void GRShapeFileLayer::registerFormats()
{

}

void GRShapeFileLayer::invalidateTableDisplay()
{

}

void GRShapeFileLayer::draw( QPainter* p, GRRect* viewExtent, GRCoordinateTransform* cXf )
{

}

void GRShapeFileLayer::table()
{

}
