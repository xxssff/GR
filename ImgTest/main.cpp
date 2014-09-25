#include "UIImgTest.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "GRApp.h"


int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    
    QTextCodec *codec = QTextCodec::codecForName( "GBK" );
    if( codec == NULL )
        codec = QTextCodec::codecForLocale();
        
    QTextCodec::setCodecForLocale( codec );
    QTextCodec::setCodecForTr( codec );
    QTextCodec::setCodecForCStrings( codec );
    
    /*UIImgTest w;
    w.show();*/
    
    GRApp gr;
    gr.show();
    return a.exec();
}
