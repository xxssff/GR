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


/// <summary>
/// Finalizes an instance of the <see cref="GRMapLayer"/> class.
/// </summary>
GRMapLayer::~GRMapLayer( void )
{
}

/// <summary>
/// Identifies the specified rect.
/// </summary>
/// <param name="rect">The rect.</param>
void GRMapLayer::identify( GRRect* rect )
{

}

/// <summary>
/// Tables this instance.
/// </summary>
void GRMapLayer::table()
{

}


/// <summary>
/// Calculates the extent.
/// </summary>
/// <returns>GRRect.</returns>
GRRect GRMapLayer::calculateExtent()
{
    return layerExtent;
}

/// <summary>
/// Draws the specified painter.
/// </summary>
/// <param name="painter">The painter.</param>
/// <param name="viewExtent">The view extent.</param>
/// <param name="yTransform">The y transform.</param>
void GRMapLayer::draw( QPainter* painter, GRRect* viewExtent, int yTransform )
{

}

/// <summary>
/// Draws the specified painter.
/// </summary>
/// <param name="painter">The painter.</param>
/// <param name="viewExtent">The view extent.</param>
/// <param name="cXf">The c xf.</param>
void GRMapLayer::draw( QPainter* painter, GRRect *viewExtent, GRCoordinateTransform* cXf )
{

}

