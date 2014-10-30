// ***********************************************************************
// Assembly         :
// Author           : Jacory
// Created          : 10-22-2014
//
// Last Modified By : Jacory
// Last Modified On : 10-22-2014
// ***********************************************************************
// <copyright file="GRLegend.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef GRLEGEND_H
#define GRLEGEND_H

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>

class GRMapLayer;
class GRMapCanvas;
class QListView;

/// <summary>
/// The map legend is a worker class that controls the display of legend items.
/// </summary>
class GRLegend : public QWidget
{
    Q_OBJECT
    
public:
    GRLegend( QListView* lv, QWidget* parent = 0, const char* name = 0 );
    ~GRLegend();
    void setMapCanvas( GRMapCanvas* canvas );
    void update();
    
    QString currentLayerName();
    GRMapLayer* currentLayer();
    
private:
    /// <summary>
    /// The list view to display the layers added.
    /// </summary>
    QListView *listView;
    /// <summary>
    /// The layer list model.
    /// </summary>
    QStandardItemModel *layerListModel;
    /// <summary>
    /// The map canvas.
    /// </summary>
    GRMapCanvas *map;
};

#endif // GRLEGEND_H
