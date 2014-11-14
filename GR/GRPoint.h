// ***********************************************************************
// Assembly         :
// Author           : Jacory
// Created          : 09-25-2014
//
// Last Modified By : Jacory
// Last Modified On : 09-25-2014
// ***********************************************************************
// <copyright file="GRPoint.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>GR is for GIS and Remote Sensing, this program is made for
//           some basic functions of the GIS and RS.</summary>
// ***********************************************************************
#pragma once

#include <iostream>
#include <QtCore/QString>

/// <summary>
/// Class GRPoint.The simple 2D point of x and y coordinate.
/// </summary>
class GRPoint
{
public:
    // constructors and destruactor
    GRPoint();
    GRPoint( double x, double y );
    ~GRPoint();
    
    //getters and setters
    /// <summary>
    /// Sets the x.
    /// </summary>
    /// <param name="x">The x.</param>
    void setX( double x ) {m_x = x;};
    /// <summary>
    /// Xs this instance.
    /// </summary>
    /// <returns>double.</returns>
    double x() const {return m_x;};
    /// <summary>
    /// Sets the y.
    /// </summary>
    /// <param name="y">The y.</param>
    void setY( double y ) {m_y = y;};
    /// <summary>
    /// Ys this instance.
    /// </summary>
    /// <returns>double.</returns>
    double y() const {return m_y;};
    
    int xToInt();
    int yToInt();
    
    //! string representation of the point (x,y)
    QString stringRep() const;
    
    bool operator==( const GRPoint &other );
    bool operator!=( const GRPoint &other );
    
    GRPoint& operator=( const GRPoint &other );
    
private:
    /// <summary>
    /// The M_X
    /// </summary>
    double m_x;//! x coordinate
    /// <summary>
    /// The m_y
    /// </summary>
    double m_y;//! y coordinate
};

/// <summary>
/// Operator==s the specified p1.
/// </summary>
/// <param name="p1">The p1.</param>
/// <param name="p2">The p2.</param>
/// <returns>bool.</returns>
inline bool operator==( const GRPoint &p1, const GRPoint &p2 )
{
    if( ( p1.x() == p2.x() ) && ( p1.y() == p2.y() ) )
        return true;
    else
        return false;
}

/// <summary>
/// Operators the specified os.
/// </summary>
/// <param name="os">The os.</param>
/// <param name="p">The p.</param>
/// <returns>std.ostream &.</returns>
inline std::ostream& operator << ( std::ostream& os, const GRPoint &p )
{
    os << p.stringRep().toStdString();
    return os;
}