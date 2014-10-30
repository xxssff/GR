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

// Map units that supports
enum UnitType
{
    Meters = 0,
    Feet = 1,
    Degrees = 2, //for 1.0 api backwards compatibility
    DecimalDegrees = 2,
    DegreesMinutesSeconds = 4,
    DegreesDecimalMinutes = 5,
    UnknownUnit = 3
};
}