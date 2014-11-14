#ifndef GRIFACE_H
#define GRIFACE_H

#include "GRInterface.h"

class GRApp;

class GRIface : public GRInterface
{
public:
    GRIface( GRApp* gr = 0, const char* name = 0 );
    ~GRIface();
    
    void zoomFull();
    void zoomPrevious();
    void zoomActiveLayer();
    int getInt();
private:
    GRApp *gr;
};

#endif // GRIFACE_H
