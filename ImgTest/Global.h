#pragma once
namespace GR
{
enum MapTools
{
    ZoomIn,
    ZoomOut,
    Pan,
    Distance,
    Identify,
    Table
};
//! Used for symbology operations
enum WKBTYPE
{
    WKBPoint = 1,
    WKBLineString,
    WKBPolygon,
    WKBMultiPoint,
    WKBMultiLineString,
    WKBMultiPolygon
};
}