#include "DistanceAlgorithmClient.h"
#include "../DistanceCalculate/DistanceAlg.h"
#include "MapCanvas.h"
#include "../DistanceCalculate/EuclideanDisntance.h"
#include "../DistanceCalculate/FrechetDistance.h"
#include "../DistanceCalculate/SpectralCurve.h"

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
    
    float *poData = new float[bandCount];
    
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
            this->disAlg->curve2 = &pixelCurve;
            float disValue = this->disAlg->CalculateDistance();
        }
    }
}
