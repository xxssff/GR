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
// <summary>图像显示窗口类，负责图像的读取和显示等功能。</summary>
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
    /// 返回图像元数据信息模型.
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
    /// 返回文件列表数据模型
    /// </summary>
    /// <returns>QStandardItemModel *.</returns>
    QStandardItemModel* FileListModel()
    {
        return fileListModel;
    };
    /// <summary>
    /// 设置fileListModel图像文件列表数据模型
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
    /// 图像元数据模型
    /// </summary>
    QStandardItemModel *imgMetaModel;
    /// <summary>
    /// 图像数据集
    /// </summary>
    GDALDataset *poDataset;
    
    /// <summary>
    /// 文件列表数据模型
    /// </summary>
    QStandardItemModel *fileListModel;
};

#endif // MAPCANVAS_H
