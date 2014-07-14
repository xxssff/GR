// ***********************************************************************
// Assembly         : ImgTest
// Author           : Jacory
// Created          : 07-10-2014
//
// Last Modified By : Jacory
// Last Modified On : 07-10-2014
// ***********************************************************************
// <copyright file="MapCanvas.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>ͼ����ʾ�����࣬����ͼ��Ķ�ȡ����ʾ�ȹ��ܡ�</summary>
// ***********************************************************************
#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QtGui/QGraphicsView>
#include <QStandardItemModel>
#include <gdal_priv.h>


/// <summary>
/// Class MapCanvas.
/// </summary>
class MapCanvas : public QGraphicsView
{
    Q_OBJECT
    
public:
    MapCanvas( QWidget *parent = 0 );
    ~MapCanvas();
    void ReadImg( const QString imgPath );
    void CloseCurrentImg();
    /// <summary>
    /// ����ͼ��Ԫ������Ϣģ��.
    /// </summary>
    /// <returns>QStandardItemModel *.</returns>
    QStandardItemModel* ImgMetaModel()
    {
        return imgMetaModel;
    };
    /// <summary>
    /// Sets the meta model.
    /// </summary>
    /// <param name="model">The model.</param>
    void SetMetaModel( QStandardItemModel* model )
    {
        this->imgMetaModel = model;
    };
    /// <summary>
    /// �����ļ��б�����ģ��
    /// </summary>
    /// <returns>QStandardItemModel *.</returns>
    QStandardItemModel* FileListModel()
    {
        return fileListModel;
    };
    /// <summary>
    /// ����fileListModelͼ���ļ��б�����ģ��
    /// </summary>
    /// <param name="model">The model.</param>
    void SetFileListModel( QStandardItemModel* model )
    {
        this->fileListModel = model;
    };
    
    QSize sizeHint() const;
private:
    void ShowBand( GDALRasterBand* band );
    void ShowColorImg( QList<GDALRasterBand*> *imgBand );
    void ShowImgInfor( const QString filename );
    void ShowFileList( const QString filename );
    unsigned char* ImgSketch( float* buffer , int row, int colum, int bands );
    
    /// <summary>
    /// ͼ��Ԫ����ģ��
    /// </summary>
    QStandardItemModel *imgMetaModel;
    /// <summary>
    /// ͼ�����ݼ�
    /// </summary>
    GDALDataset *poDataset;
    
    /// <summary>
    /// �ļ��б�����ģ��
    /// </summary>
    QStandardItemModel *fileListModel;
};

#endif // MAPCANVAS_H
