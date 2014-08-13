#include "ClassificationClient.h"
#include "../Classification/SVMClassification.h"
#include "MapCanvas.h"

#include <QtCore/QThread>
#include <gdal_priv.h>

ClassificationClient::ClassificationClient( QObject *parent )
{
    this->myMap = NULL;
    this->claAlg = NULL;
}

ClassificationClient::ClassificationClient( MapCanvas *myMap, QString algName )
{
    this->myMap = myMap;
    if ( algName == "SVM" )
    {
        this->claAlg = new SVMClassification();
    }
}

ClassificationClient::~ClassificationClient()
{

}

void ClassificationClient::executeALg( GDALDataset* poDataset, QString roiFileName, QString modelFileName )
{
    if ( this->claAlg == NULL || poDataset == NULL )
    {
        return;
    }
    // 首先读出数据集中的每个波段的逐个像素，组成光谱曲线向量
    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    
    int index = 0;
    float* resData = new float[dataHeight * dataWidth];
    
    float *srcData = new float[bandCount];
    int bandList[4] = {1, 2, 3, 4};
    
    for ( int row = 0; row < dataHeight; row++ )
    {
        for ( int column = 0; column < dataWidth; column++ )
        {
            poDataset->RasterIO( GF_Read, column, row, 1, 1, srcData, 1, 1, GDT_Float32, bandCount, bandList, 0, 0, 0 );
            
            std::string file = roiFileName.toStdString();
            
            float res = claAlg->runAlg( srcData, file , bandCount );
            resData[index++] = res;
        }
    }
    this->myMap->CreateImg( resData, dataWidth, dataHeight, 1 );
    
}
