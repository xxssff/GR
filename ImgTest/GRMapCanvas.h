// ***********************************************************************
// Assembly         :
// Author           : Jacory
// Created          : 10-11-2014
//
// Last Modified By : Jacory
// Last Modified On : 10-11-2014
// ***********************************************************************
// <copyright file="GRMapCanvas.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <map>
#include <vector>
#include <list>
#include <QtGui/QGraphicsView>
#include <QEvent>

#include "GRRect.h"
#include "GRPoint.h"

class QRect;
class GRCoordinateTransform;
class GRMapLayer;
class QMouseEvent;
class GRLegend;
class QColor;
class GRPoint;


/// <summary>
/// Class GRMapCanvas.
/// </summary>
class GRMapCanvas: public QGraphicsView
{
    Q_OBJECT
    
public:
    GRMapCanvas( QWidget* parent = 0, const char* name = 0 );
    ~GRMapCanvas( void );
    
    /// <summary>
    /// Sets the legend.
    /// </summary>
    /// <param name="legend">The legend.</param>
    void setLegend( GRLegend* legend );
    /// <summary>
    /// Extents this instance.
    /// </summary>
    /// <returns>GRRect.</returns>
    GRRect extent();
    /// <summary>
    /// Sets the extent.
    /// </summary>
    /// <param name="rec">The record.</param>
    void setExtent( GRRect rec );
    /// <summary>
    /// Sets the map tool.
    /// </summary>
    /// <param name="tool">The tool.</param>
    void setMapTool( int tool );
    /// <summary>
    /// Setbgs the color.
    /// </summary>
    /// <param name="_newVal">The _new value.</param>
    virtual void setbgColor( const QColor& _newVal );
    /// <summary>
    /// Updates the full extent to include the rectangle.
    /// </summary>
    /// <param name="rect">The rect.</param>
    void updateFullExtent( GRRect rect );
    /// <summary>
    /// Map units per pixel.
    /// </summary>
    /// <returns>double.</returns>
    double mupp();
    
    /// <summary>
    /// Adds the layer.
    /// </summary>
    /// <param name="layer">The layer.</param>
    void addLayer( GRMapLayer* layer );
    /// <summary>
    /// Renders this instance.
    /// </summary>
    void render();
    /// <summary>
    /// Clears this instance.
    /// </summary>
    void clear();
    
    /// <summary>
    /// Zooms the full extent.
    /// </summary>
    void zoomFullExtent();
    /// <summary>
    /// Zooms the previous extent.
    /// </summary>
    void zoomPreviousExtent();
    
    void refresh();
    /// <summary>
    /// Gets the zpos.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>GRMapLayer *.</returns>
    GRMapLayer* getZpos( int index );
    /// <summary>
    /// Gets the name of the layer by.
    /// </summary>
    /// <param name="name">The name.</param>
    /// <returns>GRMapLayer *.</returns>
    GRMapLayer* getLayerByName( QString name );
    /// <summary>
    /// Layers the count.
    /// </summary>
    /// <returns>int.</returns>
    int layerCount();
    /// <summary>
    /// Freezes the specified FRZ.
    /// </summary>
    /// <param name="frz">The FRZ.</param>
    void freeze( bool frz = true );
    /// <summary>
    /// Removes the specified key.
    /// </summary>
    /// <param name="key">The key.</param>
    void remove( QString key );
    /// <summary>
    /// Removes all.
    /// </summary>
    void removeAll();
    /// <summary>
    /// Sets the dirty.
    /// </summary>
    /// <param name="_dirty">The _dirty.</param>
    void setDirty( bool _dirty );
    
    friend class GRLegend;
    
public slots:
    void render2();
    /// <summary>
    /// Layers the state change.
    /// </summary>
    void layerStateChange();
    
signals:
    void xyCoordinates( GRPoint& p );
    
private:
    /// <summary>
    /// map containning the layers by name.
    /// </summary>
    std::map<QString, GRMapLayer*> layers;
    /// <summary>
    /// list containning the names of layer by zorder
    /// </summary>
    std::list<QString> zOrder;
    
    /// <summary>
    /// full extent of the map canvas
    /// </summary>
    GRRect fullExtent;
    /// <summary>
    /// The current extent
    /// </summary>
    GRRect currentExtent;
    /// <summary>
    /// The previous extent
    /// </summary>
    GRRect previousExtent;
    
    QRect* mapWindow;
    GRLegend* mapLegend;
    GRCoordinateTransform* coordXForm;
    
    /// <summary>
    /// current map tool
    /// </summary>
    int mapTool;
    /// <summary>
    /// map units per pixel
    /// </summary>
    double m_mupp;
    /// <summary>
    /// rubber band box for dynamic zoom
    /// </summary>
    QRect zoomBox;
    /// <summary>
    /// beginning point of a rubber band box
    /// </summary>
    QPoint boxStartPoint;
    /// <summary>
    /// pixmap used for restoring the canvas
    /// </summary>
    QPixmap* pmCanvas;
    /// <summary>
    /// background color for the map canvas
    /// </summary>
    QColor bgColor;
    std::vector<QColor> initialColor;
    
    /// <summary>
    /// flag to indicate the status of mouse button.
    /// </summary>
    bool mouseButtonDown;
    /// <summary>
    /// flag to indicate a map canvas drag operation is taking place
    /// </summary>
    bool dragging;
    /// <summary>
    /// flag to indicate a map canvas is drawing
    /// </summary>
    bool drawing;
    /// <summary>
    /// flag to indicate a map canvas is frozen
    /// </summary>
    bool frozen;
    /// <summary>
    /// flag to track the state of the map canvas.
    /// The canvas is flagged as dirty by any operation that changes the state of the layers
    /// or the view extent. If the canvas is not dirty, paint events are handled by bit-blitting
    /// the stored canvas bitmap to the canvas. This improves performance by not reading the data
    /// source when no real change has occurred.
    /// </summary>
    bool dirty;
    
    void incrementZpos();
    void updateZpos();
    
    void mouseMoveEvent( QMouseEvent *e );
    void mousePressEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *pe );
};

