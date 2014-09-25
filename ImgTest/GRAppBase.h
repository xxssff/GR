#pragma once

#include <QtGui/QMainWindow>
#include "ui_GRAppBase.h"

class GRAppBase: public QMainWindow, public Ui_GRAppBase
{
public:
    GRAppBase( void );
    ~GRAppBase( void );
};

