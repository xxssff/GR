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
#include <QtGui/QWorkspace>
#include <QtGui/QDockWidget>

GRApp::GRApp( QWidget *parent /*= 0*/, const char *name /*= 0 /*,WFlags fl = WType_TopLevel */ )
{
    OGRRegisterAll();
    CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );
    setupUi( this );
    
    QWorkspace *workSpace = new QWorkspace( this );
    QDockWidget *doc = new QDockWidget( this );
    
    // store startup location
    /*QDir *d = new QDir();
    startupPath = d->absolutePath();
    delete d;*/
    
    //QSplitter *split = new QSplitter( workSpace );
    legendView = new QListView( this );
    mapLegend = new GRLegend( legendView );
    QLayout *docLayout = new QVBoxLayout( doc );
    docLayout->addWidget( legendView );
    doc->setLayout( docLayout );
    
    mapCanvas = new GRMapCanvas( this );
    mapCanvas->setMinimumWidth( 400 );
    workSpace->addWindow( mapCanvas );
    
    this->setCentralWidget( workSpace );
    
    mapLegend->setMapCanvas( mapCanvas );
    mapCanvas->setLegend( mapLegend );
    
    connect( actionAdd_a_vector_layer, SIGNAL( triggered() ), this, SLOT( fileOpen() ) );
    connect( actionExit, SIGNAL( triggered() ), this, SLOT( exit() ) );
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
    addLayer();
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
