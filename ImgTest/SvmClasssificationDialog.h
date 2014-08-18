#ifndef SVMCLASSSIFICATIONDIALOG_H
#define SVMCLASSSIFICATIONDIALOG_H

#include <QDialog>
#include "ui_svmParaDialog.h"
#include "../Classification/svm.h"
#include "MyProgressBar.h"

class MapCanvas;
class ProgressDialog;

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
    
    Ui::svmParaDialog ui;
    MyProgressBar *prog;
    MapCanvas *myMap;
    
    QString roiFile;
    QString modelFile;
    QString resultFile;
    QString saveModelFile;
    svm_parameter parameter;
    
};

#endif // SVMCLASSSIFICATIONDIALOG_H
