#include "UIImgTest.h"
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include "MapCanvas.h"
#include <QtGui/QHBoxLayout>
#include "DistanceAlgorithmClient.h"
#include "SvmClasssificationDialog.h"
#include <QtCore/QThread>
#include <QtGui/QProgressBar>

/// <summary>
/// Initializes a new instance of the <see cref="ImgTest"/> class.
/// </summary>
/// <param name="ILogic &">业务逻辑类引用.</param>
UIImgTest::UIImgTest( QWidget *parent, Qt::WFlags flags )
    : QMainWindow( parent, flags )
{
    ui.setupUi( this );
    this->showMaximized();
    
    this->myDisAlgClient = NULL;
    
    myMap = new MapCanvas( this );
    myMap->setMinimumSize( 1024, 768 );
    this->setCentralWidget( myMap );
    
    ui.tableView->setModel( myMap->ImgMetaModel() );// 初始化图像元数据模型
    ui.tableView->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui.fileTreeView->setModel( myMap->FileListModel() );// 初始化文件列表
    ui.fileTreeView->setEditTriggers( QAbstractItemView::NoEditTriggers );
    
    // 连接信号、槽
    connect( ui.actionAbout, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );
    connect( ui.actionImage, SIGNAL( triggered() ), this, SLOT( PickOpenFile() ) );
    connect( ui.actionExit, SIGNAL( triggered() ), this, SLOT( Exit() ) );
    connect( ui.actionFile_List, SIGNAL( triggered() ), this, SLOT( ShowFileListWindow() ) );
    connect( ui.actionInformation, SIGNAL( triggered() ), this, SLOT( ShowInforWindow() ) );
    connect( ui.actionZoom_In, SIGNAL( triggered() ), this->myMap, SLOT( ZoomIn() ) );
    connect( ui.actionZoom_Out, SIGNAL( triggered() ), this->myMap, SLOT( ZoomOut() ) );
    connect( ui.actionFit_Window, SIGNAL( triggered() ), this->myMap, SLOT( ZoomToFitWindow() ) );
    connect( ui.actionNormal_Size, SIGNAL( triggered() ), this->myMap, SLOT( ZoomToNormalSize() ) );
    connect( ui.actionEuclidean_Distance, SIGNAL( triggered() ), this, SLOT( CalculateEuclieanDistance() ) );
    connect( ui.actionFrechet_Distance, SIGNAL( triggered() ), this, SLOT( CalculateFrechetDistance() ) );
    connect( ui.actionSVM_Classification, SIGNAL( triggered() ), this, SLOT( SvmClassification() ) );
}

/// <summary>
/// Finalizes an instance of the <see cref="ImgTest" /> class.
/// </summary>
UIImgTest::~UIImgTest()
{

}

/// <summary>
/// 退出
/// </summary>
void UIImgTest::Exit()
{
    this->close();
}

/// <summary>
/// 选择文件
/// </summary>
void UIImgTest::PickOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(
                           this,
                           tr( "Pick a image file to open..." ),
                           QDir::currentPath(),
                           tr( "jpg(*.jpg);;tiff(*.tif);;img(*.img);;All files(*.*)" ) );
    if ( !fileName.isNull() )
    {
        myMap->ReadImg( fileName );
    }
    ui.fileTreeView->expandAll();
}

/// <summary>
/// Shows the file list window
/// </summary>
void UIImgTest::ShowFileListWindow()
{
    ui.FileListDockWidget->toggleViewAction();
}

/// <summary>
/// Shows the information window.
/// </summary>
void UIImgTest::ShowInforWindow()
{
    ui.inforDockWidget->toggleViewAction();
}

/// <summary>
/// Calculates the eucliean distance.
/// </summary>
void UIImgTest::CalculateEuclieanDistance()
{
    this->myDisAlgClient = new DistanceAlgorithmClient( this->myMap, "Euclidean" );
    this->myDisAlgClient->RunDisAlg( myMap->GetDataset() );
    if ( QMessageBox::information( this, tr( "show result?" ), tr( "show result?" ) ) )
    {
        PickOpenFile();
    }
    
}

/// <summary>
/// Calculates the frechet distance.
/// </summary>
void UIImgTest::CalculateFrechetDistance()
{
    this->myDisAlgClient = new DistanceAlgorithmClient( this->myMap, "Frechet" );
    this->myDisAlgClient->RunDisAlg( myMap->GetDataset() );
}

void UIImgTest::SvmClassification()
{

    SvmClasssificationDialog svmDialog;
    svmDialog.show();
    
    //this->myClaClent = new ClassificationClient( this->myMap, "SVM", this->myMap->GetDataset(), roiFile, modelFile );
    
    //this->myClaClent->start();
    //QProgressBar *proBar = new QProgressBar;
    //proBar->setWindowTitle( tr( "Processing..." ) );
    //proBar->setRange( 0, 0 );
    // proBar->setWindowModality( Qt::ApplicationModal );
    //proBar->show();
    
}
