#ifndef GRAPP_H
#define GRAPP_H

#include "GRAppBase.h"
#include "GRIface.h"

class QCanvas;
class QRect;
class QCanvasView;
class QStringList;
class QScrollView;
class GRLegend;
class QVBox;
class QCursor;
class QListView;
class QListViewItem;
class GRMapLayer;
class QSocket;
class GRPoint;

class MapCanvas;

class GRApp : public GRAppBase
{
    Q_OBJECT
    
public:
    // constructors and destructor
    GRApp( QWidget *parent = 0, const char *name = 0 /*,WFlags fl = WType_TopLevel */ );
    ~GRApp();
    
    GRIface *getInterface();
    int getInt();
    
    //! add a layer to the map
    void addLayer();
#ifdef PGDB
    //! Add a databaselayer to the map
    void addDatabaseLayer();
#endif
    //! Exit GR;
    void fileExit();
    
    //! set map tool to zoom out
    void zoomOut();
    void zoomIn();
    void zoomFull();
    void zoomPrevious();
    void pan();
    void identify();
    void attributeTable();
    void drawPoint( double x, double y );
    void drawLayers();
    void testButton();
    void about();
    
    
private slots:
    void showMouseCoordinate( GRPoint& point );
    void layerProperties( QListViewItem* viewItem );
    void layerProperties();
    void rightClickLegendMenu( QListViewItem* viewItem );
    void removeLayer();
    void zoomToLayerExtent();
    void testPluginFunctions();
    void actionPluginManager_activated();
    void saveWindowState();
    void restoreWindowState();
    void fileSave();
    void fileSaveAs();
    void fileOpen();
    void fileNew();
    void checkGrVersion();
    void socketConnected();
    void socketConnectionClosed();
    void socketReadyRead();
    void socketError( int e );
    
private:
    //QPopupMenu* popMenu;
    QListView* legendView;
    MapCanvas* mapCanvas;
    GRLegend* mapLegend;
    QCursor* mapCursor;
    double scaleFactor;
    QRect* mapWindow;
    int mapTool;
    QCursor* cursorZoomIn;
    QString startupPath;
    QString fullPath;
    GRIface* grInterface;
    QSocket* socket;
    QString versionMessage;
    
    friend class GRIface;
};

#endif // GRAPP_H
