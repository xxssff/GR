#include "GRMapLayer.h"
#include <QtCore/QDateTime>

GRMapLayer::GRMapLayer( int type /*= 0*/, QString lyrname /*= QString::null*/, QString source /*= QString::null */ )
    : layerType( type ),
      layerName( lyrname ),
      datasource( source )
{
    valid = true;
    m_visible = true;
    
    // Generate the unique ID of this layer
    QDateTime dt = QDateTime::currentDateTime();
    ID = lyrname + dt.toString( "yyyyMMddhhmmsszzz" );
}


GRMapLayer::~GRMapLayer( void )
{
}

void GRMapLayer::identify( GRRect* rect )
{

}

void GRMapLayer::table()
{

}


GRRect GRMapLayer::calculateExtent()
{
    return layerExtent;
}

void GRMapLayer::draw( QPainter* painter, GRRect* viewExtent, int yTransform )
{

}

void GRMapLayer::draw( QPainter* painter, GRRect *viewExtent, GRCoordinateTransform* cXf )
{

}

