// ***********************************************************************
// Assembly         :
// Author           : Jacory
// Created          : 10-27-2014
//
// Last Modified By : Jacory
// Last Modified On : 10-28-2014
// ***********************************************************************
// <copyright file="GRMapLayerRegistry.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QMap>

class GRMapLayer;

/// <summary>
/// Class GRMapLayerRegistry. This class tracks map layers that are currently loaded, and provide
/// means to fetch a pointer to a map layer.
/// </summary>
class GRMapLayerRegistry : public QObject
{
    Q_OBJECT
    
public:
    static GRMapLayerRegistry* instance();
    /// <summary>
    /// The count of the map layers that currently loaded.
    /// </summary>
    /// <returns>int.</returns>
    int count() {return mMapLayers.count();};
    
    ~GRMapLayerRegistry();
    
    /// <summary>
    /// Get the map layer by layer id.
    /// </summary>
    /// <param name="theLayerId">The layer identifier.</param>
    /// <returns>GRMapLayer *.</returns>
    GRMapLayer* mapLayer( QString theLayerId ) {return mMapLayers.value( theLayerId );};
    // Get the QMap of the map layers.
    QMap<QString, GRMapLayer*>& mapLayers();
    // Add layers to the map.
    QList<GRMapLayer*> addMapLayers( QList<GRMapLayer*> theMapLayer,
                                     bool theEmitSignal = true );
    // Removes the map layers.
    void removeMapLayers( QStringList theLayerIds,
                          bool theEmitSignal = true );
    // Remove all the layers.
    void removeAllMapLayers();
    void clearAllLayerCaches();
    void reloadAllLayers();
    
signals:

    void layersWillBeRemoved( QStringList theLayerIds );
    void layerWillBeRemoved( QString theLayerId );
    void removeAll();
    void layersAdded( QList<GRMapLayer*> theMapLayers );
    //void layerWasAdded( GRMapLayer* theMapLayer );
    
protected:
    GRMapLayerRegistry();
    
private:

    /// <summary>
    /// The instance of this class.
    /// </summary>
    static GRMapLayerRegistry* mInstance;
    
    /// <summary>
    /// The Map layers registered.
    /// </summary>
    QMap<QString, GRMapLayer*> mMapLayers;
    
    /// <summary>
    /// Connects the notify.
    /// </summary>
    /// <param name="signal">The signal.</param>
    void connectNotify( const char* signal );
};

