#ifndef GRINTERFACE_H
#define GRINTERFACE_H

#include <QWidget>

class GRApp;

// interface class for plugins
class GRInterface : public QWidget
{
    Q_OBJECT
    
public:
    GRInterface( GRApp* gr = 0, const char* name = 0 ) {};
    virtual ~GRInterface() {};
    
public slots:
    virtual void zoomFull() = 0;
    virtual void zoomPrevious() = 0;
    virtual void zoomActiveLayer() = 0;
    virtual int getInt() = 0;
    
private:
    //GRApp* gr;
};

#endif // GRINTERFACE_H
