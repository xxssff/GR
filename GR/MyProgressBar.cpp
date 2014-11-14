#include "MyProgressBar.h"


MyProgressBar::MyProgressBar( QWidget *parent )
    : QDialog( parent )
{
    ui.setupUi( this );
    ui.progressBar->setRange( 0, 0 );
    connect( ui.CancelBtn, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
}


MyProgressBar::~MyProgressBar( void )
{
}

void MyProgressBar::Cancel()
{
    this->close();
    return;
}
