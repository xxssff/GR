#include "SvmClasssificationDialog.h"
#include <QtCore/QObject>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include "ClassificationClient.h"
#include "../Classification/SVMClassification.h"
#include "MapCanvas.h"

SvmClasssificationDialog::SvmClasssificationDialog(  MapCanvas *map, QWidget *parent )
    : QDialog( parent )
{
    ui.setupUi( this );
    this->myMap = map;
    
    connect( ui.roiFileBrowseBtn, SIGNAL( clicked() ), this, SLOT( BrowseRoiFile() ) );
    connect( ui.modelFileBrowseBtn, SIGNAL( clicked() ), this, SLOT( BrowseModelFile() ) );
    connect( ui.resultFileBrowseBtn, SIGNAL( clicked() ), this, SLOT( BrowseDestFile() ) );
    connect( ui.ExecuteBtn, SIGNAL( clicked() ), this, SLOT( Execute() ) );
    connect( ui.CancelBtn, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
}

SvmClasssificationDialog::~SvmClasssificationDialog()
{

}

QString SvmClasssificationDialog::BrowseRoiFile()
{
    QString roiFile = QFileDialog::getOpenFileName(
                          this,
                          tr( "select the roi file, Only text file is supported..." ),
                          QDir::currentPath(),
                          tr( "txt(*.txt)::All Files(*.*)" ) );
    return roiFile;
}

QString SvmClasssificationDialog::BrowseModelFile()
{
    QString modelFile = QFileDialog::getOpenFileName(
                            this,
                            tr( "if there's a model trained before, you can select it..." ),
                            QDir::currentPath(),
                            tr( "txt(*.txt)::All Files(*.*)" ) );
    return modelFile;
}

QString SvmClasssificationDialog::BrowseDestFile()
{
    QString resultFile = QFileDialog::getSaveFileName(
                             this,
                             tr( "save file to..." ),
                             QDir::currentPath(),
                             tr( "jpg(*.jpg);;tiff(*.tif);;img(*.img);;All files(*.*)" ) );
    return resultFile;
}

void SvmClasssificationDialog::Execute()
{
    if ( myMap == NULL || roiFile == "" )
    {
        return;
    }
    ClassificationClient *client = new ClassificationClient( this->myMap, "SVM", this->myMap->GetDataset(), roiFile, modelFile );
    client->run();
    
}

void SvmClasssificationDialog::Cancel()
{
    this->close();
    return;
}
