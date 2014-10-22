#pragma once

class QPainter;
class GRRect;
class GRCoordinateTransform;
class OGRLayer;
class OGRDataSource;

#include "GRMapLayer.h"


class GRShapeFileLayer: public GRMapLayer
{
    Q_OBJECT
public:
    GRShapeFileLayer( QString baseName = 0, QString path = 0 );
    ~GRShapeFileLayer( void );
    // Returns the bounding box of the selected features. If there is no selection, the lower bounds are DBL_MAX and the upper bounds DBL_MIN
    GRRect bBoxOfSelected();
    // Identify feature found within the search rectangle
    void identify( GRRect* rect );
    // Select features found within the search rectangle
    void select( GRRect* rect, bool lock );
    // Display the attribute table
    void table();
    enum SHAPETYPE
    {
        Point,
        Line,
        Polygon
    };
    
public slots:
    void invalidateTableDisplay();
    void select( int number );
    void removeSelection();
    void triggerRepaint();
    bool isValid();
    
protected:
    QVector<bool> *selected;
    QColor selectionColor;
    
private:
    void draw( QPainter* p, GRRect* viewExtent, GRCoordinateTransform* cXf );
    OGRDataSource *ogrDataSource;
    OGRLayer *ogrLayer;
    bool registered;
    enum ENDIAN
    {
        NDR = 1,
        XDR = 0
    };
    enum WKBTYPE
    {
        WKBPoint = 1,
        WKBLineString,
        WKBPolygon,
        WKBMultiPoint,
        WKBMultiLineString,
        WKBMultiPolygon
    };
    
    void registerFormats();
    int endian();
    
signals:
    void repaintRequested();
};

