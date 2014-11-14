#include "GRlegend.h"
#include <QtCore/QString>
#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>

#include "GRMapLayer.h"
#include "GRMapCanvas.h"

GRLegend::GRLegend( QListView* lv, QWidget* parent /*= 0*/, const char* name /*= 0 */ )
    : QWidget( parent ),
      listView( lv )
{
    layerListModel = new QStandardItemModel;
    listView->setModel( layerListModel );
}

/// <summary>
/// Finalizes an instance of the <see cref="GRLegend"/> class.
/// </summary>
GRLegend::~GRLegend()
{

}

/// <summary>
/// Sets the map canvas.
/// </summary>
/// <param name="canvas">The canvas.</param>
void GRLegend::setMapCanvas( GRMapCanvas* canvas )
{
    map = canvas;
}

/// <summary>
/// Get name of the current layer.
/// </summary>
/// <returns>QString.</returns>
QString GRLegend::currentLayerName()
{
    QModelIndex index = listView->currentIndex();
    QString layerName = index.data().toString();
    return layerName;
}

/// <summary>
/// Updates this instance.
/// </summary>
void GRLegend::update()
{
    //listView->update();
}

/// <summary>
/// Currents the layer.
/// </summary>
/// <returns>GRMapLayer *.</returns>
GRMapLayer* GRLegend::currentLayer()
{
    QModelIndex index = listView->currentIndex();
    
    return new GRMapLayer();
}
