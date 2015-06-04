#include "..\GRUtils\GREnviAsciiRoi.h"
#include "..\GRMath\GRMatrices.h";

using namespace GR::math;

int main()
{
    GR::utils::GREnviAsciiRoi* roi = new GR::utils::GREnviAsciiRoi( "E:\\Jacory\\Code\\Github\\GF_Classification\\GF data\\roi\\clip.txt" );
    Matrix* newMatrix = roi->getENVIRoi( 1 )->data;
    GRMatrices *ss = new GRMatrices();

    ss->printMatrix( newMatrix );
    ss->saveMatrix2GridTxt( newMatrix, "E:\\Temp\\11" );

    Matrix* fileMat = ss->readMatrixFromGridTxt( "E:\\Temp\\11.gmtxt" );
    ss->printMatrix( fileMat );

    system( "pause" );
    return 0;
}