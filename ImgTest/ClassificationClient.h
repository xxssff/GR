#ifndef CLASSIFICATIONCLIENT_H
#define CLASSIFICATIONCLIENT_H

#include <QObject>
#include <QtCore/QThread>
#include "ui_svmParaDialog.h"
#include <QtGui/QDialog>
#include "../Classification/svm.h"

class SVMClassification;
class MapCanvas;
class GDALDataset;

class ClassificationClient : public QThread
{
public:
    ClassificationClient();
    ClassificationClient( MapCanvas *myMap, QString algName, GDALDataset *poDataset, QString roiFileName, QString modelFileName, svm_parameter parameter );
    ~ClassificationClient();
    void run();
    
private:
    MapCanvas *myMap;
    SVMClassification *claAlg;
    
    GDALDataset *poDataset;
    QString roiFileName;
    QString modelFileName;
    svm_parameter parameter;
};

#endif // CLASSIFICATIONCLIENT_H
