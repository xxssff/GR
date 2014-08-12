#include "ClassificationClient.h"
#include "../Classification/SVMClassification.h"
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

void ClassificationClient::executeALg( GDALDataset* poDataset )
{
    if ( this->claAlg == NULL || poDataset == NULL )
    {
        return;
    }
    // 首先读出数据集中的每个波段的逐个像素，组成光谱曲线向量
    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    
    float* resultData = this->claAlg->runAlg( srcData, bandCount );
    
    this->myMap->CreateImg( resultData, )
}
