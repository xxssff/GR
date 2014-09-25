#pragma once

#include "GRPoint.h"
#include <QtCore/QString>

class GRRect
{
public:
    GRRect( double xmin = 0, double ymin = 0, double xmax = 0, double ymax = 0 );
    GRRect( GRPoint p1, GRPoint p2 );
    ~GRRect( void );
    
    //! Set the minimum x value
    void setXmin( double x ) {xmin = x;};
    //! Set the maximum x value
    void setXmax( double x ) {xmax = x;};
    //! Set the maximum y value
    void setYmin( double y ) {ymin = y;};
    //! Set the maximum y value
    void setYmax( double y ) {ymax = y;};
    //! Get the x maximum value (right side of rectangle)
    double xMax() const {return xmax;};
    //! Get the x maximum value (right side of rectangle)
    double xMin() const {return xmin;};
    //! Get the x minimum value (left side of rectangle)
    double yMax() const {return xmax;};
    //! Get the y maximum value (top side of rectangle)
    double yMin() const {return ymin;};
    //! Normalize the rectangle so it has non-negative width/height
    void normalize();
    //! Width of the rectangle
    double width() const;
    //! Height of the rectangle
    double height() const;
    //! Center point of the rectangle
    GRPoint center() const;
    //! Scale the rectangle around its center point
    void scale( double scaleFactor, GRPoint *c = 0 );
    //! Expand the rectangle to support zoom out scaling
    void expand( double scaleFactor, GRPoint* c = 0 );
    
    QString stringRep() const;
    
    bool operator==( const GRRect& other );
    GRRect& operator=( const GRRect& other );
    
private:
    double xmin;
    double ymin;
    double xmax;
    double ymax;
};

inline std::ostream& operator<< ( std::ostream& os, const GRRect& r )
{
    return os << r.stringRep().toStdString();
}
