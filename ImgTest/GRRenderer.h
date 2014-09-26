#pragma once

#include <QtCore/QString>
#include <map>

class GRRenderItem;

// Base class for all renderers
class GRRenderer
{
public:
    GRRenderer( int _type, QString _field );
    void addItem( QString key, GRRenderItem ri );
    ~GRRenderer( void );
private:
    int type;
    QString field;
    std::map<QString, GRRenderItem> items;
    
};

