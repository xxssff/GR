#ifndef CLASSIFICATIONCLIENT_H
#define CLASSIFICATIONCLIENT_H

#include <QObject>
#include <QtCore/QThread>

class ClassificationAlg;
class MapCanvas;
class GDALDataset;

class ClassificationClient : public QThread
{

public:
    ClassificationClient();
    ClassificationClient( MapCanvas *myMap, QString algName, GDALDataset *poDataset, QString roiFileName, QString modelFileName );
    ~ClassificationClient();
    
    void run();
public slots:
    void executeALg();
    
private:
    MapCanvas *myMap;
    ClassificationAlg *claAlg;
    
    GDALDataset *poDataset;
    QString roiFileName;
    QString modelFileName;
};

#endif // CLASSIFICATIONCLIENT_H
