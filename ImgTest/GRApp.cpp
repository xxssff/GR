#include "GRApp.h"
#include "MapCanvas.h"
#include "GRlegend.h"

#include <QtGui/QPixmap>
#include <QtGui/QLayout>
#include <QtGui/QBitmap>
#include <QtCore/QObject>
#include <QtGui/QFileDialog>
#include <ogrsf_frmts.h>
#include <QtGui/QSplitter>
#include <QtGui/QListView>

GRApp::GRApp( QWidget *parent /*= 0*/, const char *name /*= 0 /*,WFlags fl = WType_TopLevel */ )
{
    OGRRegisterAll();
    setupUi( this );
    //QPixmap icon( qgis_xpm );
    //setIcon(icon);
    
    // store startup location
    QDir *d = new QDir();
    startupPath = d->absolutePath();
    delete d;
    
    /*QBitmap zoomInCur;
    QBitmap zoomInCurMask;*/
    
    // QGridLayout *frameLayout = new QGridLayout( frameMain, 1, 2, 4, 6, "mainFrameLayout" );
    QSplitter *split = new QSplitter( frameMain );
    legendView = new QListView( split );
    
    mapLegend = new GRLegend( legendView );
    mapCanvas = new MapCanvas( split );
    mapCanvas->setMidLineWidth( 400 );
    mapLegend->setMapCanvas( mapCanvas );
    
    
    connect( actionAdd_a_vector_layer, SIGNAL( triggered() ), this, SLOT( fileOpen() ) );
}

GRApp::~GRApp()
{

}

GRIface * GRApp::getInterface()
{
    return grInterface;
}

void GRApp::addLayer()
{

}

#ifdef PGDB
void GRApp::addDatabaseLayer()
{

}
#endif

void GRApp::fileExit()
{
    this->close();
}

void GRApp::zoomOut()
{

}

void GRApp::zoomIn()
{

}

void GRApp::zoomFull()
{

}

void GRApp::zoomPrevious()
{

}

void GRApp::pan()
{

}

void GRApp::identify()
{

}

void GRApp::attributeTable()
{

}

void GRApp::drawPoint( double x, double y )
{

}

void GRApp::drawLayers()
{

}

void GRApp::testButton()
{

}

void GRApp::about()
{

}

void GRApp::showMouseCoordinate( GRPoint& point )
{

}

void GRApp::layerProperties( QListViewItem* viewItem )
{

}

void GRApp::layerProperties()
{

}

void GRApp::rightClickLegendMenu( QListViewItem* viewItem )
{

}

void GRApp::removeLayer()
{

}

void GRApp::zoomToLayerExtent()
{

}

void GRApp::testPluginFunctions()
{

}

void GRApp::actionPluginManager_activated()
{

}

void GRApp::saveWindowState()
{

}

void GRApp::restoreWindowState()
{

}

void GRApp::fileSave()
{

}

void GRApp::fileSaveAs()
{

}

void GRApp::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
                           this,
                           tr( "Pick a image file to open..." ),
                           QDir::currentPath(),
                           tr( "tiff(*.tif);;img(*.img);;All files(*.*)" ) );
    if ( !fileName.isNull() )
    {
        mapCanvas->ReadImg( fileName );
    }
}

void GRApp::fileNew()
{

}

void GRApp::checkGrVersion()
{

}

void GRApp::socketConnected()
{

}

void GRApp::socketConnectionClosed()
{

}

void GRApp::socketReadyRead()
{

}

void GRApp::socketError( int e )
{

}

int GRApp::getInt()
{
    return 1;
}
