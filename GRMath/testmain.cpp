#include <iostream>

#include "GRMatrices.h"

using namespace GR::math;
using namespace std;

int main()
{

    Matrix* newMatrix = new Matrix();
    GRMatrices *ss = new GRMatrices();
    newMatrix = ss->createMatrix( 10, 3 );

    ss->printMatrix( newMatrix );
    ss->saveMatrix2GridTxt( newMatrix, "E:\\Temp\\11" );

    Matrix* fileMat = ss->readMatrixFromGridTxt( "E:\\Temp\\11.gmtxt" );
    ss->printMatrix( fileMat );

    system( "pause" );
    return 0;
}