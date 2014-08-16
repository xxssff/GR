#include "ClassificationClient.h"
#include "../Classification/SVMClassification.h"
#include "MapCanvas.h"

#include <QtCore/QThread>
#include <gdal_priv.h>

ClassificationClient::ClassificationClient()
{
    this->myMap = NULL;
    this->claAlg = NULL;
}

ClassificationClient::ClassificationClient( MapCanvas *myMap, QString algName, GDALDataset *poDataset, QString roiFileName, QString modelFileName, svm_parameter parameter )
    : poDataset( poDataset ), roiFileName( roiFileName ), modelFileName( modelFileName ), parameter( parameter )
{
    this->myMap = myMap;
    if ( algName == "SVM" )
    {
        this->claAlg = new SVMClassification();
        claAlg->SetRoiFile( roiFileName.toStdString() );
        claAlg->SetParameter( parameter );
    }
}

ClassificationClient::~ClassificationClient()
{

}

void ClassificationClient::run()
{
    if ( this->claAlg == NULL || poDataset == NULL )
    {
        return;
    }
    
    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    
    claAlg->SetModelFile( modelFileName.toStdString() );
    claAlg->SetBandCount( bandCount );
    claAlg->SetPixelCount( dataWidth * dataHeight );
    
    
    int index = 0;
    float **srcData = new float*[dataWidth * dataHeight];
    float *poData = new float[bandCount];
    
    // intiailize the bandlist argument
    int *bandList = new int[bandCount];
    for ( int i = 0; i < bandCount; i++ )
    {
        bandList[i] = i + 1;
    }
    
    for ( int row = 0; row < dataHeight; row++ )
    {
        for ( int column = 0; column < dataWidth; column++ )
        {
            poDataset->RasterIO( GF_Read, column, row, 1, 1, poData, 1, 1, GDT_Float32, bandCount, bandList, 0, 0, 0 );
            srcData[index] = new float[bandCount];
            srcData[index++] = poData;
        }
    }
    float* resultData = claAlg->runAlg( srcData );
    this->myMap->CreateImg( resultData, dataWidth, dataHeight, 1 );
}


