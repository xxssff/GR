#pragma once

#include <iostream>
#include <string>

namespace GR
{
enum GRDataType
{
    gr_undefined = 0,
    gr_8int = 1,
    gr_16int = 2,
    gr_32int = 3,
    gr_64int = 4,
    gr_8uint = 5,
    gr_16uint = 6,
    gr_32uint = 7,
    gr_64uint = 8,
    gr_32float = 9,
    gr_64float = 10

};

inline std::string getDataTypeAsStr( GRDataType dataType )
{
    std::string strDT = "Unknown";
    switch( dataType )
    {
    case gr_8int:
        strDT = "Integer 8 bit";
        break;
    case gr_16int:
        strDT = "Integer 16 bit";
        break;
    case gr_32int:
        strDT = "Integer 32 bit";
        break;
    case gr_64int:
        strDT = "Integer 64 bit";
        break;
    case gr_8uint:
        strDT = "Unsigned Integer 8 bit";
        break;
    case gr_16uint:
        strDT = "Unsigned Integer 16 bit";
        break;
    case gr_32uint:
        strDT = "Unsigned Integer 32 bit";
        break;
    case gr_64uint:
        strDT = "Unsigned Integer 64 bit";
        break;
    case gr_32float:
        strDT = "Float 32 bit";
        break;
    case gr_64float:
        strDT = "Float 64 bit";
        break;
    default:
        strDT = "Unknown";
    }
    return strDT;
}
}