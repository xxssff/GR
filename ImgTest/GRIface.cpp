#include "GRIface.h"
#include "GRApp.h"

GRIface::GRIface( GRApp* gr /*= 0*/, const char* name /*= 0 */ )
{

}

GRIface::~GRIface()
{

}

void GRIface::zoomFull()
{
    gr->zoomFull();
}

void GRIface::zoomPrevious()
{
    gr->zoomPrevious();
}

void GRIface::zoomActiveLayer()
{
    //gr->zoom
}

int GRIface::getInt()
{
    return gr->getInt();
}
