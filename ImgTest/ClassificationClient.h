// ***********************************************************************
// Assembly         : ImgTest
// Author           : Jacory
// Created          : 08-16-2014
//
// Last Modified By : Jacory
// Last Modified On : 08-18-2014
// ***********************************************************************
// <copyright file="ClassificationClient.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>This class is a client of classification algorithm classes, it is inherited from
// QThread, for running the algorithm in a new thread. And the strategy design pattern is applied here.</summary>
// ***********************************************************************
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

/// <summary>
/// Class ClassificationClient.
/// </summary>
class ClassificationClient : public QThread
{
public:
    ClassificationClient();
    ClassificationClient( MapCanvas *myMap, QString algName, QString roiFileName = "", QString modelFileName = "", QString saveModelFile = "", svm_parameter *parameter = NULL );
    ~ClassificationClient();
    void run();
    
private:
    float Scale( float src , float max, float min );
    
    /// <summary>
    /// The MapCanvas reference, it's used to get
    /// the raster data's information and create the new image.
    /// </summary>
    MapCanvas *myMap;
    /// <summary>
    /// classification algorithm pointer.
    /// </summary>
    SVMClassification *claAlg;
    /// <summary>
    /// The GDALDataset variable
    /// </summary>
    GDALDataset *poDataset;
    /// <summary>
    /// The roi file path
    /// </summary>
    QString roiFileName;
    /// <summary>
    /// The svm model file path
    /// </summary>
    QString modelFileName;
    /// <summary>
    /// The svm parameter
    /// </summary>
    svm_parameter parameter;
    /// <summary>
    /// The file path to save the model to
    /// </summary>
    QString saveModelFile;
};

#endif // CLASSIFICATIONCLIENT_H
