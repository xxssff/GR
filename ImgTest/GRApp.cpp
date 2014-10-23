#include "GRApp.h"
#include "MapCanvas.h"
#include "GRlegend.h"
#include "GRMapCanvas.h"
#include "GRShapeFileLayer.h"

#include <QtGui/QPixmap>
#include <QtGui/QLayout>
#include <QtGui/QBitmap>
#include <QtCore/QObject>
#include <QtGui/QFileDialog>
#include <ogrsf_frmts.h>
#include <QtGui/QSplitter>
#include <QtGui/QListView>
#include <QtGui/QMessageBox>
#include <QtGui/QMdiArea>
#include <QtGui/QDockWidget>

GRApp::GRApp( QWidget *parent /*= 0*/, const char *name /*= 0 /*,WFlags fl = WType_TopLevel */ )
{
    OGRRegisterAll();
    CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );
    setupUi( this );
    
    // add plugin doc widget
    QDockWidget *pluginDoc = new QDockWidget( this );
    pluginDoc->setAllowedAreas( Qt::AllDockWidgetAreas );
    pluginDoc->setWindowTitle( tr( "Plugin" ) );
    addDockWidget( Qt::RightDockWidgetArea, pluginDoc );
    
    // add legend doc widget
    QDockWidget *legendDoc = new QDockWidget( this );
    legendDoc->setAllowedAreas( Qt::AllDockWidgetAreas );
    legendView = new QListView( this );
    mapLegend = new GRLegend( legendView );
    legendDoc->setWidget( legendView );
    legendDoc->setWindowTitle( tr( "Legend" ) );
    addDockWidget( Qt::RightDockWidgetArea, legendDoc );
    
    // add work space to have MDI mode
    mdiArea = new QMdiArea( this );
    
    mapCanvas = new GRMapCanvas( this );
    mapCanvas->setMinimumWidth( 400 );
    mdiArea->addSubWindow( mapCanvas );
    
    this->setCentralWidget( mdiArea );
    
    mapLegend->setMapCanvas( mapCanvas );
    mapCanvas->setLegend( mapLegend );
    
    toolBar->setAllowedAreas( Qt::LeftToolBarArea );
    
    connect( actionAdd_a_vector_layer, SIGNAL( triggered() ), this, SLOT( addVectorLayer() ) );
    connect( actionAdd_new_window, SIGNAL( triggered() ), this, SLOT( addNewWindow() ) );
    connect( actionExit, SIGNAL( triggered() ), this, SLOT( exit() ) );
    
    menuView->addAction( legendDoc->toggleViewAction() );
    menuView->addAction( pluginDoc->toggleViewAction() );
    
    createConnections();
}

GRApp::~GRApp()
{

}

GRIface* GRApp::getInterface()
{
    return grInterface;
}

void GRApp::addLayer()
{
    mapCanvas->freeze( true );
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "open files dialog",
                            0,
                            "Shapefiles (*.shp);;All files (*.*)",
                            0
                        );
    QApplication::setOverrideCursor( Qt::WaitCursor );
    QStringList::Iterator it = files.begin();
    while ( it != files.end() )
    {
        QFileInfo fi( *it );
        QString base = fi.baseName();
        // create the layer
        GRShapeFileLayer *lyr = new GRShapeFileLayer( base, *it );
        connect( lyr, SIGNAL( repaintRequested() ), mapCanvas, SLOT( refresh() ) );
        
        if ( lyr->isValid() )
        {
            // add it to the mapcanvas collection
            mapCanvas->addLayer( lyr );
        }
        else
        {
            QString msg = *it;
            msg += " is not a valid or recognized data source";
            QMessageBox::critical( this, "Invalid Data Source", msg );
        }
        
        ++it;
    }
    mapLegend->update();
    qApp->processEvents();
    mapCanvas->freeze( false );
    mapCanvas->render2();
    QApplication::restoreOverrideCursor();
    statusBar()->showMessage( mapCanvas->extent().stringRep() );
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

void GRApp::exit()
{
    this->close();
}

void GRApp::addVectorLayer()
{
    addLayer();
}

void GRApp::addNewWindow()
{
    GRMapCanvas* map = new GRMapCanvas( this );
    map->setWindowTitle( tr( "new window" ) );
    mdiArea->addSubWindow( map );
    map->show();
}

void GRApp::createConnections()
{
    connect( actionTile, SIGNAL( triggered() ), mdiArea, SLOT( tileSubWindows() ) );
    connect( actionCascade, SIGNAL( triggered() ), mdiArea, SLOT( cascadeSubWindows() ) );
}
