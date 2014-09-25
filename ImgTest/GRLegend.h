#ifndef GRLEGEND_H
#define GRLEGEND_H

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>

class GRMapLayer;
class MapCanvas;
class QListView;

// The map legend is a worker class that controls the display of legend items.
class GRLegend : public QWidget
{
	Q_OBJECT
	
public:
	GRLegend( QListView* lv, QWidget* parent = 0, const char* name = 0 );
	~GRLegend();
	void setMapCanvas( MapCanvas* canvas );
	void update();
	
	QString currentLayerName();
	GRMapLayer* currentLayer();
	
private:
	QListView *listView;
	QStandardItemModel *layerListModel;
	MapCanvas *map;
};

#endif // GRLEGEND_H
