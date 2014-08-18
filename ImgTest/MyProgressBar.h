#pragma once
#include "ui_ProgressDialog.h"
#include <QtCore/QObject>

class MyProgressBar: public QDialog
{
    Q_OBJECT
public:
    MyProgressBar( QWidget* parent = 0 );
    ~MyProgressBar( void );
public slots:
    void Cancel();
private:
    Ui::ProgressDialog ui;
};

