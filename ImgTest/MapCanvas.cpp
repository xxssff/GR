#include "MapCanvas.h"
#include <QtGui/QMessageBox>
#include <QtCore/QFileInfo>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui/QGraphicsPixmapItem>

MapCanvas::MapCanvas( QWidget *parent /*= 0 */ )
    : QGraphicsView( parent )
{
    poDataset = NULL;
    m_scaleFactor = 1.0;
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
/// ��ȡͼ���ļ�
/// </summary>
/// <param name="imgPath">ͼ���ļ�</param>
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
    // ���ͼ���ļ������������Σ���Ĭ��ֻ��ʾ��һ���λҶ�ͼ��
    if ( poDataset->GetRasterCount() != 3 )
    {
        ShowBand( poDataset->GetRasterBand( 1 ) );
    }
    // ���ͼ�������������Σ���Ĭ����RGB��˳����ʾ��ɫͼ
    else
    {
        QList<GDALRasterBand*> bandList;
        bandList.append( poDataset->GetRasterBand( 1 ) );
        bandList.append( poDataset->GetRasterBand( 2 ) );
        bandList.append( poDataset->GetRasterBand( 3 ) );
        ShowImg( &bandList );
    }
    GDALClose( poDataset );
}

/// <summary>
/// �رյ�ǰͼ���ļ�
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
    
    QList<GDALRasterBand*> myBand;
    myBand.append( band );
    myBand.append( band );
    myBand.append( band );
    
    ShowImg( &myBand );
    
}

/// <summary>
/// ��ʾͼ��
/// </summary>
/// <param name="imgBand">ͼ�񲨶�</param>
void MapCanvas::ShowImg( QList<GDALRasterBand*> *imgBand )
{
    if ( imgBand->size() != 3 )
    {
        return;
    }
    
    int imgWidth = imgBand->at( 0 )->GetXSize();
    int imgHeight = imgBand->at( 0 )->GetYSize();
    
    int iScaleWidth = imgWidth;
    int iScaleHeight = imgHeight;
    
    GDALDataType dataType = imgBand->at( 0 )->GetRasterDataType();
    
    // ���ȷֱ��ȡRGB��������
    float* rBand = new float[iScaleWidth * iScaleHeight];
    float* gBand = new float[iScaleWidth * iScaleHeight];
    float* bBand = new float[iScaleWidth * iScaleHeight];
    imgBand->at( 0 )->RasterIO( GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight, GDT_Float32, 0, 0 );
    imgBand->at( 1 )->RasterIO( GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0 );
    imgBand->at( 2 )->RasterIO( GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0 );
    
    //// �ֱ�����ÿ������
    //unsigned char* rBandUC = ImgSketch( rBand, imgWidth, imgHeight, 1, imgBand->at( 0 )->GetNoDataValue() );
    //unsigned char* gBandUC = ImgSketch( gBand, imgWidth, imgHeight, 1, imgBand->at( 1 )->GetNoDataValue() );
    //unsigned char* bBandUC = ImgSketch( bBand, imgWidth, imgHeight, 1, imgBand->at( 2 )->GetNoDataValue() );
    //
    //// �����������������
    int bytePerLine = ( iScaleWidth * 24 + 31 ) / 8;
    unsigned char* allBandUC = new unsigned char[bytePerLine * iScaleHeight * 3];
    //for( int h = 0; h < iScaleHeight; h++ )
    //{
    //    for( int w = 0; w < iScaleWidth; w++ )
    //    {
    //        allBandUC[h * imgWidth + w * 3 + 0] = rBandUC[h * iScaleWidth + w];
    //        allBandUC[h * imgWidth + w * 3 + 1] = gBandUC[h * iScaleWidth + w];
    //        allBandUC[h * imgWidth + w * 3 + 2] = bBandUC[h * iScaleWidth + w];
    //    }
    //}
    
    
    double rminmax[2], gminmax[2], bminmax[2];
    double rmin, gmin, bmin, rmax, gmax, bmax;
    GDALComputeRasterMinMax( imgBand->at( 0 ), 1, rminmax );
    rmin = rminmax[0];
    rmax = rminmax[1];
    GDALComputeRasterMinMax( imgBand->at( 1 ), 1, gminmax );
    gmin = gminmax[0];
    gmax = gminmax[1];
    GDALComputeRasterMinMax( imgBand->at( 2 ), 1, bminmax );
    bmin = bminmax[0];
    bmax = bminmax[1];
    double rnovalue = GDALGetRasterNoDataValue( imgBand->at( 0 ), NULL );
    double gnovalue = GDALGetRasterNoDataValue( imgBand->at( 1 ), NULL );
    double bnovalue = GDALGetRasterNoDataValue( imgBand->at( 2 ), NULL );
    rmin = rmin <= rnovalue && rnovalue < rmax ? 0 : rmin;
    gmin = gmin <= gnovalue && gnovalue < gmax ? 0 : gmin;
    bmin = bmin <= bnovalue && bnovalue < bmax ? 0 : bmin;
    
    for( int h = 0; h < iScaleHeight; h++ )
    {
        for( int w = 0; w < iScaleWidth; w++ )
        {
            uchar rvalue = 0, gvalue = 0, bvalue = 0;
            int i = h * iScaleWidth + w;
            
            if( rBand[i] <= rmax && rBand[i] >= rmin )
            {
                rvalue = static_cast<uchar>( 255 - 255 * ( rmax - rBand[i] ) / ( rmax - rmin ) );
                
            }
            else if( rBand[i] > rmax )
            {
                rvalue = 255;
                
            }
            else
            {
                rvalue = 0;
            }
            
            if( gBand[i] <= gmax && gBand[i] >= gmin )
            {
                gvalue = static_cast<uchar>( 255 - 255 * ( gmax - gBand[i] ) / ( gmax - gmin ) );
                
            }
            else if( gBand[i] > gmax )
            {
                gvalue = 255;
                
            }
            else
            {
                gvalue = 0;
            }
            
            if( bBand[i] <= bmax && bBand[i] >= bmin )
            {
                bvalue = static_cast<uchar>( 255 - 255 * ( bmax - bBand[i] ) / ( bmax - bmin ) );
                
            }
            else if( bBand[i] > bmax )
            {
                bvalue = 255;
                
            }
            else
            {
                bvalue = 0;
            }
            
            allBandUC[h * bytePerLine + w * 3 + 0] = rvalue;
            allBandUC[h * bytePerLine + w * 3 + 1] = gvalue;
            allBandUC[h * bytePerLine + w * 3 + 2] = bvalue;
        }
    }
    
    
    // ����ͼ����ʾ
    QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem(  QPixmap::fromImage( QImage( allBandUC, iScaleWidth, iScaleHeight, bytePerLine, QImage::Format_RGB888  ) ) );
    QGraphicsScene *myScene = new QGraphicsScene();
    myScene->addItem( imgItem );
    this->setScene( myScene );
}

/// <summary>
/// ��ʾͼ�������Ϣ
/// </summary>
/// <param name="filename">�ļ���</param>
void MapCanvas::ShowImgInfor( const QString filename )
{
    if ( filename == "" || poDataset == NULL )
    {
        return;
    }
    int row = 0; // ������¼����ģ�͵��к�
    
    // ͼ��ĸ�ʽ��Ϣ
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Description" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetDescription() ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Meta Infor" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME ) ) ) ;
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Data Type" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( GDALGetDataTypeName( ( poDataset->GetRasterBand( 1 )->GetRasterDataType() ) ) ) );
    
    // ͼ��Ĵ�С�Ͳ��θ���
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "X Size" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterXSize() ) ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Y Size" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterYSize() ) ) );
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Band Count" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterCount() ) ) );
    
    // ͼ���ͶӰ��Ϣ
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Projection" ) ) );
    imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetProjectionRef() ) );
    
    // ͼ�������ͷֱ�����Ϣ
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
/// ��ʾ�ļ��ṹ��
/// </summary>
/// <param name="filename">�ļ���</param>
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
/// ͼ����������
/// </summary>
/// <param name="buffer">ͼ�񻺴�</param>
/// <param name="row">����</param>
/// <param name="colum">����</param>
/// <param name="bands">������</param>
/// <returns>���������8λͼ�񻺴�</returns>
unsigned char* MapCanvas::ImgSketch( float* buffer , int row, int column, int bands, double noValue )
{
    unsigned char* resBuffer = new unsigned char[row * column * bands];
    float max, min;
    double minmax[2];
    
    for ( int b = 0; b < bands; b++ )
    {
        poDataset->GetRasterBand( b + 1 )->ComputeRasterMinMax( b + 1, minmax );
        min = minmax[0];
        max = minmax[1];
        if( min <= noValue && noValue < max )
        {
            min = 0;
        }
        for ( int i = 0; i < row * column * bands; i++ )
        {
            if ( buffer[i] > max )
            {
                resBuffer[i] = 255;
            }
            else if ( buffer[i] < max && buffer[i] > min )
            {
                resBuffer[i] = static_cast<uchar>( 255 - 255 * ( max - buffer[i] ) / ( max - min ) );
            }
            else
            {
                resBuffer[i] = 0;
            }
        }
    }
    
    return resBuffer;
}

QSize MapCanvas::sizeHint() const
{
    return QSize( 1024, 768 );
}
