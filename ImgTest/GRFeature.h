#pragma once

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>

class GRGeometry;

class GRFeature
{
public:
    GRFeature();
    GRFeature( GRFeature const& rhs );
    ~GRFeature();
    
    GRGeometry* geometry() const {return mGeometry;};
    bool isValid() const {return mValid;};
    void setValid( const bool value ) {mValid = value;};
    bool isDirty() const {return mDirty;};
    void setDirty( const bool value ) {mDirty = value;};
    QString typeName() const {return mTypeName;};
    void setTypeName( const QString value ) {mTypeName = value;};
private:

    // pointer to geometry in binary WKB format.
    // This is usually set by a call to OGRGeometry::exportToWkb()
    GRGeometry* mGeometry;
    
    // Flag to indicate if this feature is valid
    bool mValid;
    
    // Flag to indicate if this feature is dirty (e.g. geometry has been modified in-memory)
    bool mDirty;
    
    /// feature type name
    QString mTypeName;
};

// feature list.
typedef QList<GRFeature> GRFeatureList;

// key = field index, value = field name.
typedef QMap<int, QString> GRFieldNameMap;