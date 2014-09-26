#include "GRRenderer.h"


GRRenderer::GRRenderer( int _type, QString _field )
    : type( _type ),
      field( _field )
{

}


GRRenderer::~GRRenderer( void )
{
}

void GRRenderer::addItem( QString key, GRRenderItem ri )
{
    items[key] = ri;
}
