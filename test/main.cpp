#include "..\GRUtils\GREnviAsciiRoi.h"
#include "..\GRMath\GRMatrices.h";
#include "..\GRClassify\GRSvmClassifier.h"
#include "..\GRClassify\GRIsoDataClassifier.h"

#include <time.h>
#include <iostream>

using namespace GR::math;
using namespace std;

int main()
{
    #pragma region test svm classification
    /*string base = "CLIP";
    string dir = "E:\\Jacory\\Code\\Github\\GF_Classification\\GF data\\";

    string ROIpath = dir + "roi\\" + base + ".txt";
    string Modelpath = dir + "model\\" + base + "_model";
    string InputPath = dir + "img\\" + base + ".tif";
    string OutputPath = dir + "res\\" + base + ".tif";

    bool res = false;

    time_t startTime = time( NULL );

    try
    {
        GR::classifier::GRSvmClassifier* svm = new GR::classifier::GRSvmClassifier();
        res = svm->run( ROIpath, Modelpath, InputPath, OutputPath );

    }
    catch ( const char* error )
    {
        cout << error << endl;
    }
    catch( ... )
    {
        cout << "something is wrong..." << endl;
    }
    if ( res == true )
    {
        cout << "Done!" << endl;
    }

    time_t endTime = time( NULL );

    cout << "time use:" << endTime - startTime << "s" << endl;*/
    #pragma endregion test svm classification


    #pragma region test isodata classification
    string inputFileName = "C:\\31954-106.jpg";
    string outputFileName = "E:\\ISO_class.tif";
    GR::classifier::GRIsoDataClassifier *isodata = new GR::classifier::GRIsoDataClassifier();
    isodata->setInputFilename( inputFileName );
    isodata->setOutputFilename( outputFileName );
    time_t startTime = time( NULL );
    try
    {
        isodata->ParametersCheck();
        isodata->Execute();
    }
    catch ( const char* error )
    {
        cout << error << endl;
    }

    time_t endTime = time( NULL );
    cout << "time use:" << endTime - startTime << "s" << endl;

    #pragma endregion test isodata classification



    //GR::utils::GREnviAsciiRoi* roi = new GR::utils::GREnviAsciiRoi( "E:\\Jacory\\Code\\Github\\GF_Classification\\GF data\\roi\\clip.txt" );

    //roi->printRois();
    //Matrix* newMatrix = roi->getENVIRoi( 0 )->data;
    //GRMatrices *ss = new GRMatrices();

//    ss->exportAsImage( newMatrix, "E:\\Temp\\11.img" );

    ////ss->printMatrix( newMatrix );
    //ss->saveMatrix2GridTxt( newMatrix, "E:\\Temp\\11" );
    //Matrix* fileMat = ss->readMatrixFromGridTxt( "E:\\Temp\\11.gmtxt" );
    //ss->printMatrix( fileMat );

    system( "pause" );
    return 0;
}