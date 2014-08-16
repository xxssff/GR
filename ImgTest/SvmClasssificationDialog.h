#ifndef SVMCLASSSIFICATIONDIALOG_H
#define SVMCLASSSIFICATIONDIALOG_H

#include <QDialog>
#include "ui_svmParaDialog.h"

class MapCanvas;

class SvmClasssificationDialog : public QDialog
{
    Q_OBJECT
    
public:
    SvmClasssificationDialog( MapCanvas *map, QWidget *parent = 0 );
    ~SvmClasssificationDialog();
    
public slots:
    QString BrowseRoiFile();
    QString BrowseModelFile();
    QString BrowseDestFile();
    void Execute();
    void Cancel();
    
private:
    Ui::svmParaDialog ui;
    MapCanvas *myMap;
    
    QString roiFile;
    QString modelFile;
    QString resultFile;
};

#endif // SVMCLASSSIFICATIONDIALOG_H
