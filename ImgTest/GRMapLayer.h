// ***********************************************************************
// Assembly         :
// Author           : Jacory
// Created          : 09-25-2014
//
// Last Modified By : Jacory
// Last Modified On : 09-26-2014
// ***********************************************************************
// <copyright file="GRMapLayer.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <QtCore/QObject>
#include <QtGui/QPainter>
#include "GRRect.h"

class GRCoordinateTransform;
class GRSymbol;

/// <summary>
/// Class GRMapLayer.Base class for all map layer types.
/// </summary>
class GRMapLayer: public QObject
{
    Q_OBJECT
public:
    GRMapLayer( int type = 0, QString lyrname = QString::null, QString source = QString::null );
    virtual ~GRMapLayer( void );
    
    /// <summary>
    /// Layers enum defining the types of layers that can be added to a map
    /// </summary>
    enum LAYERS
    {
        VECTOR,
        RASTER,
        DATABASE
    };
    
    /// <summary>
    /// The m_label field
    /// </summary>
    QString m_labelField;
    
    /// <summary>
    /// Types this instance.
    /// </summary>
    /// <returns>const int.</returns>
    const int type() {return layerType;};
    /// <summary>
    /// Gets the layer identifier.
    /// </summary>
    /// <returns>QString.</returns>
    QString getLayerID() {return ID;};
    /// <summary>
    /// Sets the name of the layer.
    /// </summary>
    /// <param name="name">The name.</param>
    void setLayerName( const QString& name ) {layerName = name;};
    /// <summary>
    /// Gets the name of the layer.
    /// </summary>
    /// <returns>const QString.</returns>
    const QString getLayerName() {return layerName;};
    
    virtual GRRect calculateExtent();
    virtual void draw( QPainter* painter, GRRect* viewExtent, int yTransform );
    virtual void draw( QPainter* painter, GRRect *viewExtent, GRCoordinateTransform* cXf );
    // Identify the feature(s) in this layer that are contained in the search rectangle
    virtual void identify( GRRect* rect );
    virtual void table();
    /// <summary>
    /// Extents this instance.
    /// </summary>
    /// <returns>const GRRect.</returns>
    const GRRect extent() {return layerExtent;};
    /// <summary>
    /// Determines whether this instance is valid.
    /// </summary>
    bool isValid() {return valid;};
    
    /// <summary>
    /// Sets the symbol.
    /// </summary>
    /// <param name="newVal">The new value.</param>
    virtual void setSymbol( GRSymbol* newVal ) {layerSymbol = newVal;};
    /// <summary>
    /// Symbols this instance.
    /// </summary>
    /// <returns>GRSymbol *.</returns>
    virtual GRSymbol* symbol() {return layerSymbol;};
    /// <summary>
    /// Sets the lable field.
    /// </summary>
    /// <param name="newVal">The new value.</param>
    virtual void setLableField( const QString& newVal ) {m_labelField = newVal;};
    
    /// <summary>
    /// Sets the z.
    /// </summary>
    /// <param name="zorder">The zorder.</param>
    void setZ( int zorder ) {zpos = zorder;};
    /// <summary>
    /// Zs this instance.
    /// </summary>
    /// <returns>int.</returns>
    int z() {return zpos;};
    /// <summary>
    /// Visibles this instance.
    /// </summary>
    /// <returns>bool.</returns>
    bool visible() {return m_visible;};
    /// <summary>
    /// Sets the visible.
    /// </summary>
    /// <param name="vis">The vis.</param>
    void setVisible( bool vis ) {m_visible = vis;};
    /// <summary>
    /// Sources this instance.
    /// </summary>
    /// <returns>QString.</returns>
    QString source() {return datasource;};
    /// <summary>
    /// Sets the type of the feature.
    /// </summary>
    /// <param name="newVal">The new value.</param>
    virtual void setFeatureType( const int &newVal ) {feature = newVal;};
    /// <summary>
    /// Get features' type.
    /// </summary>
    /// <returns>const int &.</returns>
    virtual const int& featureType() {return feature;};
    
signals:
    void visibilityChanged( void );
protected:
    /// <summary>
    /// The layer extent
    /// </summary>
    GRRect layerExtent;
    /// <summary>
    /// The zpos
    /// </summary>
    int zpos;
    /// <summary>
    /// The valid
    /// </summary>
    bool valid;
    /// <summary>
    /// The source of the layer
    /// </summary>
    QString datasource;
    /// <summary>
    /// The features type in the layer
    /// </summary>
    int feature;
private:
    /// <summary>
    /// The identifier
    /// </summary>
    QString ID;
    /// <summary>
    /// The layer name
    /// </summary>
    QString layerName;
    /// <summary>
    /// The layer type, vector, raster or database
    /// </summary>
    int layerType;
    /// <summary>
    /// The tag
    /// </summary>
    QString tag;
    /// <summary>
    /// The layer symbol
    /// </summary>
    GRSymbol *layerSymbol;
    /// <summary>
    /// The visible
    /// </summary>
    bool m_visible;
};

