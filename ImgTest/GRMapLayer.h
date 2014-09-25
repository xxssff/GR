#pragma once

#include <QtCore/QObject>
#include <QtGui/QPainter>
#include "GRRect.h"

class GRCoordinateTransform;
class GRSymbol;

// Base class for all map layer types.
class GRMapLayer: public QObject
{
    Q_OBJECT
public:
    GRMapLayer( int type = 0, QString lyrname = QString::null, QString source = QString::null );
    virtual ~GRMapLayer( void );
    
    // Layers enum defining the types of layers that can be added to a map
    enum LAYERS
    {
        VECTOR,
        RASTER,
        DATABASE
    };
    
    QString m_labelField;
    
    const int type() {return layerType;};
    QString getLayerID() {return ID;};
    void setLayerName( const QString& name ) {layerName = name;};
    const QString getLayerName() {return layerName;};
    
    virtual GRRect calculateExtent();
    virtual void draw( QPainter* painter, GRRect* viewExtent, int yTransform );
    virtual void draw( QPainter* painter, GRRect *viewExtent, GRCoordinateTransform* cXf );
    // Identify the feature(s) in this layer that are contained in the search rectangle
    virtual void identify( GRRect* rect );
    virtual void table();
    const GRRect extent() {return layerExtent;};
    bool isValid() {return valid;};
    
    virtual void setSymbol( GRSymbol* newVal ) {layerSymbol = newVal;};
    virtual GRSymbol* symbol() {return layerSymbol;};
    virtual void setLableField( const QString& newVal ) {m_labelField = newVal;};
    
    void setZ( int zorder ) {zpos = zorder;};
    int z() {return zpos;};
    bool visible() {return m_visible;};
    void setVisible( bool vis ) {m_visible = vis;};
    QString source() {return datasource;};
    virtual void setFeatureType( const int &newVal ) {feature = newVal;};
    virtual const int& featureType() {return feature;};
    
signals:
    void visibilityChanged( void );
protected:
    GRRect layerExtent;
    int zpos;
    bool valid;
    QString datasource;
    int feature;
private:
    QString ID;
    QString layerName;
    int layerType;
    QString tag;
    GRSymbol *layerSymbol;
    bool m_visible;
};

