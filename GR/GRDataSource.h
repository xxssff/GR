#pragma once

#include <QtCore/QString>

// Base class for spatial and tabular data
class GRDataSource
{
public:
    GRDataSource() {};
    ~GRDataSource() {};
protected:
    QString dataSource;
};