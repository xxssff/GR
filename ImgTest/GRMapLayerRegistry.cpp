#include "GRMapLayerRegistry.h"
#include "GRMapLayer.h"

#include <QtCore/QtDebug>


GRMapLayerRegistry *GRMapLayerRegistry::mInstance = 0;

/// <summary>
/// Initializes a new instance of the <see cref="GRMapLayerRegistry"/> class.
/// </summary>
GRMapLayerRegistry::GRMapLayerRegistry( void )
{
}


/// <summary>
/// Finalizes an instance of the <see cref="GRMapLayerRegistry" /> class.
/// </summary>
GRMapLayerRegistry::~GRMapLayerRegistry( void )
{
    removeAllMapLayers();
}

/// <summary>
/// Return the instance of this class.
/// <summary>
GRMapLayerRegistry* GRMapLayerRegistry::instance()
{
    if ( mInstance == 0 )
    {
        mInstance = new GRMapLayerRegistry();
    }
    return mInstance;
}

/// <summary>
/// Maps the layers.
/// </summary>
/// <returns>QMap&lt;QString,GRMapLayer*&gt;&.</returns>
QMap<QString, GRMapLayer*>& GRMapLayerRegistry::mapLayers()
{
    return mMapLayers;
}

/// <summary>
/// Adds the map layers.
/// </summary>
/// <param name="theMapLayer">The map layer list.</param>
/// <param name="theEmitSignal">The flag indicates whether to emit signal or not.</param>
/// <returns>The list of the map registered.</returns>
QList<GRMapLayer*> GRMapLayerRegistry::addMapLayers(
    QList<GRMapLayer*> theMapLayer,
    bool theEmitSignal /*= true */ )
{
    QList<GRMapLayer*> myResultList;
    for ( int i = 0; i < theMapLayer.size(); i++ )
    {
        GRMapLayer* myLayer = theMapLayer.at( i );
        if ( !myLayer || !myLayer->isValid() )
        {
            qDebug() << "Cannot add invalid layers.";
            continue;
        }
        // check the layer is not already registered.
        QMap<QString, GRMapLayer*>::iterator myIter = mMapLayers.find( myLayer->getLayerID() );
        if ( myIter == mMapLayers.end() )
        {
            mMapLayers[myLayer->getLayerID()] = myLayer;
            myResultList.append( mMapLayers[myLayer->getLayerID()] );
            if ( theEmitSignal )
            {
                // this signal should be connected to map legend and/or map canvas.
                emit layersAdded( myResultList );
            }
        }
    }
    return myResultList;
}

/// <summary>
/// Removes the map layers.
/// </summary>
/// <param name="theLayerIds">The layer ids.</param>
/// <param name="theEmitSignal">The flag indicates whether to emit signal or not.</param>
void GRMapLayerRegistry::removeMapLayers( QStringList theLayerIds, bool theEmitSignal /*= true */ )
{
    if ( theEmitSignal )
    {
        emit layersWillBeRemoved( theLayerIds );
    }
    foreach( const QString & myId, theLayerIds )
    {
        if ( theEmitSignal )
        {
            emit layerWillBeRemoved( myId );
        }
        delete mMapLayers[myId];
        mMapLayers.remove( myId );
    }
    emit layersWillBeRemoved( theLayerIds );
}

/// <summary>
/// Removes all map layers.
/// </summary>
void GRMapLayerRegistry::removeAllMapLayers()
{
    // emit the signal before physically removing the layers
    emit removeAll();
    QStringList myList;
    QMap<QString, GRMapLayer*>::iterator iter;
    for ( iter = mMapLayers.begin(); iter != mMapLayers.end(); iter++ )
    {
        QString id = iter.key();
        myList << id;
    }
    removeMapLayers( myList, false );
    mMapLayers.clear();
}

/// <summary>
/// Clears all layer caches.
/// </summary>
void GRMapLayerRegistry::clearAllLayerCaches()
{
    QMap<QString, GRMapLayer*>::iterator iter;
    for ( iter = mMapLayers.begin(); iter != mMapLayers.end(); iter++ )
    {
        //iter.value()->setCacheImage(0);
    }
}

/// <summary>
/// Reloads all layers.
/// </summary>
void GRMapLayerRegistry::reloadAllLayers()
{
    QMap<QString, GRMapLayer*>::iterator iter;
    for ( iter = mMapLayers.begin(); iter != mMapLayers.end(); iter++ )
    {
        GRMapLayer* layer = iter.value();
        if ( layer )
        {
            //layer->reload();
        }
    }
}

void GRMapLayerRegistry::connectNotify( const char* signal )
{

}
