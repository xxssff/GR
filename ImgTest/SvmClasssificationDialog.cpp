#include "SvmClasssificationDialog.h"
#include <QtCore/QObject>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include "ClassificationClient.h"
#include "../Classification/SVMClassification.h"
#include "MapCanvas.h"
#include <QtGui/QMessageBox>

SvmClasssificationDialog::SvmClasssificationDialog( QWidget *parent )
    : QDialog( parent )
{
    ui.setupUi( this );
    prog = new MyProgressBar( this );
    ui.saveModelCheckBox->setCheckState( Qt::Unchecked );
    ui.saveModelLineEdit->setEnabled( false );
    ui.saveModelBtn->setEnabled( false );
    
    connect( ui.roiFileBrowseBtn, SIGNAL( clicked() ), this, SLOT( BrowseRoiFile() ) );
    connect( ui.modelFileBrowseBtn, SIGNAL( clicked() ), this, SLOT( BrowseModelFile() ) );
    connect( ui.resultFileBrowseBtn, SIGNAL( clicked() ), this, SLOT( BrowseDestFile() ) );
    connect( ui.ExecuteBtn, SIGNAL( clicked() ), this, SLOT( Execute() ) );
    connect( ui.CancelBtn, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
    connect( ui.saveModelCheckBox, SIGNAL( toggled( bool ) ), this, SLOT( SetSaveModelEnable() ) );
    connect( ui.saveModelBtn, SIGNAL( clicked() ), this, SLOT( BrowseSaveModel() ) );
}

/// <summary>
/// Finalizes an instance of the <see cref="SvmClasssificationDialog"/> class.
/// </summary>
SvmClasssificationDialog::~SvmClasssificationDialog()
{

}

/// <summary>
/// Browses the roi file.
/// </summary>
void SvmClasssificationDialog::BrowseRoiFile()
{
    QString roiFile = QFileDialog::getOpenFileName(
                          this,
                          tr( "select the roi file, Only text file is supported..." ),
                          QDir::currentPath(),
                          tr( "txt(*.txt)::All Files(*.*)" ) );
    ui.roiFilePath->setText( roiFile );
    this->roiFile = roiFile;
}

/// <summary>
/// Browses the model file.
/// </summary>
void SvmClasssificationDialog::BrowseModelFile()
{
    QString modelFile = QFileDialog::getOpenFileName(
                            this,
                            tr( "if there's a model trained before, you can select it..." ),
                            QDir::currentPath(),
                            tr( "txt(*.txt)::All Files(*.*)" ) );
    ui.modelFilePath->setText( modelFile );
    this->modelFile = modelFile;
}

/// <summary>
/// Browses the dest file.
/// </summary>
void SvmClasssificationDialog::BrowseDestFile()
{
    QString resultFile = QFileDialog::getSaveFileName(
                             this,
                             tr( "save file to..." ),
                             QDir::currentPath(),
                             tr( "tiff(*.tif);;img(*.img);;All files(*.*)" ) );
    ui.resultFilePath->setText( resultFile );
    this->resultFile = resultFile;
}

/// <summary>
/// Browses the save model.
/// </summary>
void SvmClasssificationDialog::BrowseSaveModel()
{
    QString saveModelFile = QFileDialog::getSaveFileName(
                                this,
                                tr( "you can save the trained model to a text file" ),
                                QDir::currentPath(),
                                tr( "txt(*.txt);;All Files(*.*)" ) );
    ui.saveModelLineEdit->setText( saveModelFile );
    this->saveModelFile = saveModelFile;
}

/// <summary>
/// Executes this instance. This method creates a new ClassificationClient object, and
/// passes the arguments needed to it. Then call the object's run function. The Classification class
/// is inherit from QThread, so it will run in a new thread.
/// </summary>
void SvmClasssificationDialog::Execute()
{
    if ( myMap == NULL || roiFile == "" || myMap->GetDataset() == NULL )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "there is no data or roi file..." ) );
        return;
    }
    
    prog->show();
    
    initialParameter();
    ClassificationClient *client = new ClassificationClient( this->myMap, "SVM", roiFile, modelFile, saveModelFile, &parameter );
    client->start();
}

/// <summary>
/// Cancels this instance.
/// </summary>
void SvmClasssificationDialog::Cancel()
{
    this->close();
    return;
}

/// <summary>
/// Sets the save model controls enable.
/// </summary>
void SvmClasssificationDialog::SetSaveModelEnable()
{
    if ( ui.saveModelCheckBox->checkState() == Qt::Checked )
    {
        ui.saveModelLineEdit->setEnabled( true );
        ui.saveModelBtn->setEnabled( true );
    }
    if ( ui.saveModelCheckBox->checkState() == Qt::Unchecked )
    {
        ui.saveModelLineEdit->setEnabled( false );
        ui.saveModelBtn->setEnabled( false );
    }
}

/// <summary>
/// Initials the parameter struct. These parameters are only used to train the svm model, if there's a model file that include
/// a model already been trained, these parameters will be ignored.
/// </summary>
void SvmClasssificationDialog::initialParameter()
{
    parameter.svm_type = C_SVC;
    switch( ui.kernelTypeComboBox->currentIndex() )
    {
    case 0:
        parameter.kernel_type = LINEAR;
        break;
    case 1:
        parameter.kernel_type = RBF;
        break;
    case 2:
        parameter.kernel_type = SIGMOID;
        break;
    case 3:
        parameter.kernel_type = POLY;
        break;
    }
    parameter.gamma = ui.GammaLineEdit->text().toDouble();
    parameter.degree = ui.degreeSpinBox->value();
    parameter.C = ui.PenaltyLineEdit->text().toDouble();
    
    parameter.coef0 = 0;
    parameter.nu = 0.5;
    parameter.cache_size = 1;
    parameter.eps = 1e-3;
    parameter.p = 0.1;
    parameter.shrinking = 1;
    parameter.probability = 0;
    parameter.nr_weight = 0;
    parameter.weight_label = NULL;
    parameter.weight = NULL;
    
}

/// <summary>
/// Sets the MapCanvas object pointer.
/// </summary>
/// <param name="map">The map.</param>
void SvmClasssificationDialog::SetMap( MapCanvas *map )
{
    this->myMap = map;
}


