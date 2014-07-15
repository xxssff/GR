#include "MapCanvas.h"
#include <QtGui/QMessageBox>
#include <QtCore/QFileInfo>

MapCanvas::MapCanvas( QWidget *parent /*= 0 */ )
    : QGraphicsView( parent )
{
    poDataset = NULL;
    imgMetaModel = new QStandardItemModel;
    imgMetaModel->setColumnCount( 2 );
    fileListModel = new QStandardItemModel;
    QSizePolicy policy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    this->setSizePolicy( policy );
}

/// <summary>
/// Finalizes an instance of the <see cref="MapCanvas"/> class.
/// </summary>
MapCanvas::~MapCanvas()
{

}

/// <summary>
/// 读取图像文件
/// </summary>
/// <param name="imgPath">图像文件</param>
void MapCanvas::ReadImg( const QString imgPath )
{
    GDALAllRegister();
    CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );
    poDataset = ( GDALDataset* )GDALOpen( imgPath.toStdString().c_str(), GA_ReadOnly );
    if ( poDataset == NULL )
    {
        QMessageBox::critical( this, tr( "Error!" ), tr( "Can not open file %1" ).arg( imgPath ) );
        return;
    }
    ShowFileList( imgPath );
    ShowImgInfor( imgPath );
    // 如果图像文件并非三个波段，则默认只显示第一波段灰度图像
    if ( poDataset->GetRasterCount() != 3 )
    {
        ShowBand( poDataset->GetRasterBand( 1 ) );
    }
    // 如果图像正好三个波段，则默认以RGB的顺序显示彩色图
    else
    {
        QList<GDALRasterBand*> bandList;
        bandList.append( poDataset->GetRasterBand( 1 ) );
        bandList.append( poDataset->GetRasterBand( 2 ) );
        bandList.append( poDataset->GetRasterBand( 3 ) );
        ShowColorImg( &bandList );
    }
    GDALClose( poDataset );
}

/// <summary>
/// 关闭当前图像文件
/// </summary>
void MapCanvas::CloseCurrentImg()
{
    poDataset = NULL;
    imgMetaModel->clear();
    fileListModel->clear();
}

/// <summary>
/// Shows the band.
/// </summary>
/// <param name="band">The band.</param>
void MapCanvas::ShowBand( GDALRasterBand* band )
{
    if ( band == NULL )
    {
        return;
    }
    int bandWidth = band->GetXSize();
    int bandHeight = band->GetYSize();
    
    int iScaleWidth = bandWidth;
    int iScaleHeight = bandHeight;
    
    GDALDataType dataType = band->GetRasterDataType();
    
    float* pData = new float[bandWidth * bandHeight];
    band->RasterIO( GF_Read, 0, 0, bandWidth, bandHeight, pData, iScaleWidth, iScaleHeight, dataType, 0, 0 );
}

/// <summary>
/// 显示彩色图像
/// </summary>
/// <param name="imgBand">图像波段</param>
void MapCanvas::ShowColorImg( QList<GDALRasterBand*> *imgBand )
{
    if ( imgBand->size() != 3 )
    {
        return;
    }
    // 首先分别读取RGB三个波段
    int imgWidth = imgBand->at( 0 )->GetXSize();
    int imgHeight = imgBand->at( 0 )->GetYSize();
    
    int iScaleWidth = imgWidth;
    int iScaleHeight = imgHeight;
    
    GDALDataType dataType = imgBand->at( 0 )->GetRasterDataType();
    
    float* rBand = new float[imgWidth * imgHeight];
    float* gBand = new float[imgWidth * imgHeight];
    float* bBand = new float[imgWidth * imgHeight];
    imgBand->at( 0 )->RasterIO( GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight, dataType, 0, 0 );
    imgBand->at( 1 )->RasterIO( GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight, dataType, 0, 0 );
    imgBand->at( 2 )->RasterIO( GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight, dataType, 0, 0 );
    
    unsigned char* rBandUC = ImgSketch( rBand, imgWidth, imgHeight, 1 );
    unsigned char* gBandUC = ImgSketch( gBand, imgWidth, imgHeight, 1 );
    unsigned char* bBandUC = ImgSketch( bBand, imgWidth, imgHeight, 1 );
}

/// <summary>
/// 显示图像基本信息
/// </summary>
/// <param name="filename">文件名</param>
void MapCanvas::ShowImgInfor( const QString filename )
{
    if ( filename == "" || poDataset == NULL )
    {
        return;
    }
    int row = 0; // 用来记录数据模型的行号
    
    // 图像的格式信息
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Description" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetDescription() ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Meta Infor" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME ) ) ) ;
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Data Type" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( GDALGetDataTypeName( ( poDataset->GetRasterBand( 1 )->GetRasterDataType() ) ) ) );
    
    // 图像的大小和波段个数
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "X Size" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterXSize() ) ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Y Size" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterYSize() ) ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Band Count" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterCount() ) ) );
    
    // 图像的投影信息
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Projection" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetProjectionRef() ) );
    
    // 图像的坐标和分辨率信息
    double adfGeoTransform[6];
    QString origin = "";
    QString pixelSize = "";
    if( poDataset->GetGeoTransform( adfGeoTransform ) == CE_None )
    {
        origin = QString::number( adfGeoTransform[0] ) + ", " + QString::number( adfGeoTransform[3] );
        pixelSize = QString::number( adfGeoTransform[1] ) + ", " + QString::number( adfGeoTransform[5] );
    }
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Origin" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( origin ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Pixel Size" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( pixelSize ) );
}

/// <summary>
/// 显示文件结构树
/// </summary>
/// <param name="filename">文件名</param>
void MapCanvas::ShowFileList( const QString filename )
{
    if ( filename == "" || poDataset == NULL )
    {
        return;
    }
    QFileInfo fileInfo( filename );
    QStandardItem *rootItem = new QStandardItem( fileInfo.fileName() );
    for ( int i = 0; i < poDataset->GetRasterCount(); i++ )
    {
        QStandardItem *childItem = new QStandardItem( tr( "Band %1" ).arg( i + 1 ) );
        rootItem->setChild( i, childItem );
    }
    fileListModel->setItem( 0, rootItem );
}

/// <summary>
/// 图像线性拉伸
/// </summary>
/// <param name="buffer">图像缓存</param>
/// <param name="row">行数</param>
/// <param name="colum">列数</param>
/// <param name="bands">波段数</param>
/// <returns>经过拉伸的8位图像缓存</returns>
unsigned char* MapCanvas::ImgSketch( float* buffer , int row, int column, int bands )
{
    unsigned char* resBuffer = new unsigned char[row * column, bands];
    float max, min, minmax[2];
    
    for ( int b = 0; b < bands; b++ )
    {
        poDataset->GetRasterBand( b + 1 )->ComputeRasterMinMax( b + 1, minmax );
        min = minmax[0];
        max = minmax[1];
        for ( int i = 0; i < row * column * bands; i++ )
        {
            resBuffer[i] = ( buffer[i] - min ) / ( max - min ) * 255;
        }
    }
    return resBuffer;
}

QSize MapCanvas::sizeHint() const
{
    return QSize( 1024, 768 );
}
