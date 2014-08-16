#ifndef CLASSIFICATIONCLIENT_H
#define CLASSIFICATIONCLIENT_H

#include <QObject>
#include <QtCore/QThread>
#include "ui_svmParaDialog.h"
#include <QtGui/QDialog>

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
    
    Ui::svmParaDialog svmDialog;
};

#endif // CLASSIFICATIONCLIENT_H
