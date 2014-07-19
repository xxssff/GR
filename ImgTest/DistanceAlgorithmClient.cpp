#include "DistanceAlgorithmClient.h"
#include "../DistanceCalculate/DistanceAlg.h"
#include "MapCanvas.h"
#include "../DistanceCalculate/EuclideanDisntance.h"
#include "../DistanceCalculate/FrechetDistance.h"
#include "../DistanceCalculate/SpectralCurve.h"
#include <QtGui/QFileDialog>

DistanceAlgorithmClient::DistanceAlgorithmClient( QObject *parent )
    : QObject( parent )
{
    this->disAlg = NULL;
    this->myMap = NULL;
}

/// <summary>
/// Initializes a new instance of the <see cref="DistanceAlgorithmClient"/> class.
/// </summary>
/// <param name="map">The map.</param>
/// <param name="algName">Name of the alg.</param>
DistanceAlgorithmClient::DistanceAlgorithmClient( MapCanvas* map, QString algName )
{
    if ( algName == "Euclidean" )
    {
        this->disAlg = new EuclideanDisntance;
    }
    if ( algName == "Frechet" )
    {
        this->disAlg = new FrechetDistance;
    }
}

/// <summary>
/// Finalizes an instance of the <see cref="DistanceAlgorithmClient"/> class.
/// </summary>
DistanceAlgorithmClient::~DistanceAlgorithmClient()
{

}

/// <summary>
/// 设置MapCanvas显示控件
/// </summary>
/// <param name="map">The map.</param>
void DistanceAlgorithmClient::SetMapCavans( MapCanvas* map )
{
    this->myMap = map;
}

/// <summary>
/// Gets the map canvas.
/// </summary>
/// <returns>MapCanvas *.</returns>
MapCanvas* DistanceAlgorithmClient::GetMapCanvas()
{
    return this->myMap;
}

/// <summary>
/// 设置距离算法类别
/// </summary>
/// <param name="alg">The alg.</param>
void DistanceAlgorithmClient::SetDistanceAlg( DistanceAlg* alg )
{
    this->disAlg = alg;
}

/// <summary>
/// 执行算法，具体执行哪一个算法，在于实例化的具体disAlg对象的类别
/// </summary>
/// <param name="map">The map.</param>
void DistanceAlgorithmClient::RunDisAlg( GDALDataset* poDataset )
{
    if ( this->disAlg == NULL || poDataset == NULL )
    {
        return;
    }
    // 首先读出数据集中的每个波段的逐个像素，组成光谱曲线向量
    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    int *bandList = new int[bandCount];
    for ( int band = 1; band <= bandCount; band++ )
    {
        bandList[band - 1] = band;
    }
    
    SpectralCurve pixelCurve;// 一个像素的光谱曲线
    SpectralCurve targetCurve;// 用于匹配的目标光谱
    
    //.....just for test
    for ( int i = 0; i < bandCount; i++ )
    {
        curvePoint p;
        p.x = 1;
        p.y = 1;
        targetCurve.scVec.push_back( p );
    }
    this->disAlg->curve2 = &targetCurve;
    //.....just for test
    
    float *poData = new float[bandCount];
    float *poResultData = new float[dataWidth * dataHeight];// 距离计算结果数组
    int index = 0;
    for ( int width = 0; width < dataWidth; width++ )
    {
        for ( int height = 0; height < dataHeight; height++ )
        {
        
            poDataset->RasterIO( GF_Read, width, height, width + 1, height + 1, poData, 1, 1, GDT_Float32, bandCount, bandList, 0, 0, 0 );
            for ( int band = 0; band < bandCount; band++ )
            {
                curvePoint cp;
                cp.x = 0;
                cp.y = poData[band];
                pixelCurve.scVec.push_back( cp );
                
            }
            // 做了以上处理，现在pixelCurve就是一个像素的光谱曲线了
            // 接下来将读取的数据进行组织，做相应的距离计算
            this->disAlg->curve1 = &pixelCurve;
            
            float disValue = this->disAlg->CalculateDistance();
            pixelCurve.scVec.clear();
            poResultData[index++] = disValue;
        }
    }
    // now create the result image
    GDALDataset *pResultDataset;
    int *resultBandList = new int[1];
    resultBandList[0] = 1;
    
    GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName( "GTiff" );
    QString dstFileName = "E:\\result.tif";
    pResultDataset = pDriver->Create( dstFileName.toStdString().c_str(), dataWidth, dataHeight, 1, GDT_Float32, NULL );
    pResultDataset->RasterIO( GF_Write, 0, 0, dataWidth, dataHeight, poResultData, dataWidth, dataHeight, GDT_Float32, 1, resultBandList, 0, 0, 0 );
    GDALClose( pResultDataset );
}
