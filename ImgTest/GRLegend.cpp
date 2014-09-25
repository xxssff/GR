#include "GRlegend.h"
#include <QtCore/QString>
#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>

#include "MapCanvas.h"
#include "GRMapLayer.h"

GRLegend::GRLegend( QListView* lv, QWidget* parent /*= 0*/, const char* name /*= 0 */ )
	: QWidget( parent ),
	  listView( lv )
{
	layerListModel = new QStandardItemModel;
	listView->setModel( layerListModel );
}

GRLegend::~GRLegend()
{

}

void GRLegend::setMapCanvas( MapCanvas* canvas )
{
	map = canvas;
}

QString GRLegend::currentLayerName()
{
	QModelIndex index = listView->currentIndex();
	QString layerName = index.data().toString();
	return layerName;
}

void GRLegend::update()
{
	//listView->update();
}

GRMapLayer* GRLegend::currentLayer()
{
	QModelIndex index = listView->currentIndex();
	
	return new GRMapLayer();
}
