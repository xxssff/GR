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

/// <summary>
/// Initializes a new instance of the <see cref="ClassificationClient"/> class.
/// Use this method, we can pass the arguments needed to the instance, and then to the right algorithm.
/// </summary>
/// <param name="myMap">My map.</param>
/// <param name="algName">Name of the alg.</param>
/// <param name="poDataset">The po dataset.</param>
/// <param name="roiFileName">Name of the roi file.</param>
/// <param name="modelFileName">Name of the model file.</param>
/// <param name="parameter">The parameter.</param>
ClassificationClient::ClassificationClient( MapCanvas *myMap, QString algName, QString roiFileName, QString modelFileName, QString saveModelFile, svm_parameter *parameter )
    : roiFileName( roiFileName ), modelFileName( modelFileName ), parameter( *parameter ), saveModelFile( saveModelFile )
{
    this->myMap = myMap;
    poDataset = myMap->GetDataset();
    if ( algName == "SVM" ) // if the algorithm name is SVM, then roiFile\modelFile\modelFileSave\svmParameter should be initialized.
    {
        this->claAlg = new SVMClassification();
        claAlg->SetRoiFile( roiFileName.toStdString() );
        claAlg->SetParameter( *parameter );
        claAlg->SetModelFile( modelFileName.toStdString() );
        if ( saveModelFile != "" )
        {
            claAlg->SetModelFileSave( saveModelFile.toStdString() );
        }
    }
}

/// <summary>
/// Finalizes an instance of the <see cref="ClassificationClient"/> class.
/// </summary>
ClassificationClient::~ClassificationClient()
{

}

/// <summary>
/// Runs this instance. This instance is running in a new thread.
/// </summary>
void ClassificationClient::run()
{
    if ( this->claAlg == NULL || poDataset == NULL )
    {
        return;
    }
    
    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    
    claAlg->SetBandCount( bandCount );
    claAlg->SetPixelCount( dataWidth * dataHeight );
    
    int index = 0;
    float **srcData = new float*[dataWidth * dataHeight];
    float *poData = new float[bandCount];
    float temp;
    
    GDALRasterBand *rasterBand;
    double minmax[2];
    float *max = new float[bandCount];
    float *min = new float[bandCount];
    for( int i = 0; i < bandCount; i++ )
    {
        rasterBand = poDataset->GetRasterBand( i + 1 );
        rasterBand->ComputeRasterMinMax( 1, minmax );
        min[i] = minmax[0];
        max[i] = minmax[1];
        float noValue = rasterBand->GetNoDataValue();
        if( min[i] <= noValue && noValue <= max[i] )
        {
            min[i] = 0;
        }
    }
    
    for ( int row = 0; row < dataHeight; row++ )
    {
        for ( int column = 0; column < dataWidth; column++ )
        {
            srcData[index] = new float[bandCount];
            
            for ( int band = 0; band < bandCount; band++ )
            {
                rasterBand = poDataset->GetRasterBand( band + 1 );
                rasterBand->RasterIO( GF_Read, column, row, 1, 1, &temp, 1, 1, GDT_Float32, 0, 0 );
                poData[band] = Scale( temp , max[band], min[band] );
            }
            
            srcData[index++] = poData;
        }
    }
    
    float* resultData = claAlg->runAlg( srcData );
    this->myMap->CreateImg( resultData, dataWidth, dataHeight, 1 );
}

/// <summary>
/// Scales the src to range 0~1.
/// </summary>
/// <param name="src">The source.</param>
/// <param name="max">The maximum.</param>
/// <param name="min">The minimum.</param>
/// <returns>float.</returns>
float ClassificationClient::Scale( float src , float max, float min )
{
    float result = ( src - min ) / ( max - min );
    if ( src >= max )
    {
        result = 1;
    }
    if ( src <= min )
    {
        result = 0;
    }
    return result;
}


