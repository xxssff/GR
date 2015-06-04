#pragma once

namespace GR
{
namespace utils
{


class _declspec( dllexport ) GRColor
{

private:
    double red;
    double green;
    double blue;
    double alpha;

public:
    GRColor() {};
    GRColor( double r, double g, double b, double a )
        : red( r ), green( g ), blue( b ), alpha( a ) {};
    ~GRColor() {};
    double getRed() {return red;};

    double getGreen() {return green;};

    double getBlue() {return blue;};

    double getAlpha() {return alpha;};
};



class _declspec( dllexport ) GRColorInt
{
private:
    int red;
    int green;
    int blue;
    int alpha;

public:
    GRColorInt() {};
    GRColorInt( int r, int g, int b, int a )
        : red( r ), green( g ), blue( b ), alpha( a ) {};
    ~GRColorInt() {};

    int getRed() {return red;};

    int getGreen() {return green;};

    int getBlue() {return blue;};

    int getAlpha() {return alpha;};
};

}
}