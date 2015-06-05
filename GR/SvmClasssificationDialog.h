// ***********************************************************************
// Assembly         : ImgTest
// Author           : Jacory
// Created          : 08-16-2014
//
// Last Modified By : Jacory
// Last Modified On : 08-17-2014
// ***********************************************************************
// <copyright file="SvmClasssificationDialog.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>Support Vector Machine arguments dialog. It is used to send the user
//			defined arguments to the svm algorithm.
// </summary>
// ***********************************************************************
#ifndef SVMCLASSSIFICATIONDIALOG_H
#define SVMCLASSSIFICATIONDIALOG_H

#include <QDialog>
#include "ui_svmParaDialog.h"
#include "..\GRClassify\svm.h"
#include "MyProgressBar.h"

class MapCanvas;
class ProgressDialog;

/// <summary>
/// Class SvmClasssificationDialog.
/// </summary>
class SvmClasssificationDialog : public QDialog
{
    Q_OBJECT

public:
    SvmClasssificationDialog( QWidget *parent = 0 );
    ~SvmClasssificationDialog();

public slots:
    void BrowseRoiFile();
    void BrowseModelFile();
    void BrowseDestFile();
    void Execute();
    void Cancel();
    void SetSaveModelEnable();
    void BrowseSaveModel();
    void SetMap( MapCanvas *map );

private:
    void initialParameter();

    /// <summary>
    /// The dialog ui.
    /// </summary>
    Ui::svmParaDialog ui;
    /// <summary>
    /// The progress dialog.
    /// </summary>
    MyProgressBar *prog;
    /// <summary>
    /// The MapCanvas reference, it's used to get
    /// the raster data's information and create the new image.
    /// </summary>
    MapCanvas *myMap;
    /// <summary>
    /// The roi file path, used to train the model.
    /// </summary>
    QString roiFile;
    /// <summary>
    /// The model file path, if this is specified, it's no need to train the model.
    /// </summary>
    QString modelFile;
    /// <summary>
    /// The result file path.
    /// </summary>
    QString resultFile;
    /// <summary>
    /// The path to save the trained model to.
    /// </summary>
    QString saveModelFile;
    /// <summary>
    /// The parameter to train svm model.
    /// </summary>
    svm_parameter parameter;

};

#endif // SVMCLASSSIFICATIONDIALOG_H
