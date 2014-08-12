#ifndef CLASSIFICATIONCLIENT_H
#define CLASSIFICATIONCLIENT_H

#include <QObject>
#include <QtCore/QThread>

class ClassificationAlg;
class MapCanvas;
class GDALDataset;

class ClassificationClient: QObject
{
    Q_OBJECT
    
public:
    ClassificationClient( QObject *parent );
    ClassificationClient( MapCanvas *myMap, QString algName );
    ~ClassificationClient();
    
    void executeALg( GDALDataset* poDataset );
    
private:
    MapCanvas *myMap;
    ClassificationAlg *claAlg;
};

#endif // CLASSIFICATIONCLIENT_H
