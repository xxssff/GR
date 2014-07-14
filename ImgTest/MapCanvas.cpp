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
/// ��ȡͼ���ļ�
/// </summary>
/// <param name="imgPath">ͼ���ļ�</param>
void MapCanvas::ReadImg( const QString imgPath )
{
    GDALAllRegister();
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
        ShowColorImg( &bandList );
    }
    GDALClose( poDataset );
}

/// <summary>
/// Closes the current img.
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

}

/// <summary>
/// Shows the img.
/// </summary>
/// <param name="imgBand">The img band.</param>
void MapCanvas::ShowColorImg( QList<GDALRasterBand*> *imgBand )
{

}

/// <summary>
/// Shows the img infor.
/// </summary>
/// <param name="filename">The filename.</param>
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
    imgMetaModel->setItem( row, 0, new QStandardItem( tr( "GDAL Data Type" ) ) );
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
/// Shows the file list.
/// </summary>
/// <param name="filename">The filename.</param>
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
/// Imgs the sketch.
/// </summary>
/// <param name="buffer">The buffer.</param>
/// <param name="row">The row.</param>
/// <param name="colum">The colum.</param>
/// <param name="bands">The bands.</param>
/// <returns>unsigned char *.</returns>
unsigned char* MapCanvas::ImgSketch( float* buffer , int row, int column, int bands )
{
    unsigned char* resBuffer = new unsigned char[row * column, bands];
    
    return resBuffer;
}

QSize MapCanvas::sizeHint() const
{
    return QSize( 1024, 768 );
}
