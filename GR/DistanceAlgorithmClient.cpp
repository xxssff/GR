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
/// ����MapCanvas��ʾ�ؼ�
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
/// ���þ����㷨���
/// </summary>
/// <param name="alg">The alg.</param>
void DistanceAlgorithmClient::SetDistanceAlg( DistanceAlg* alg )
{
    this->disAlg = alg;
}

/// <summary>
/// ִ���㷨������ִ����һ���㷨������ʵ�����ľ���disAlg��������
/// </summary>
/// <param name="map">The map.</param>
void DistanceAlgorithmClient::RunDisAlg( GDALDataset* poDataset )
{
    if ( this->disAlg == NULL || poDataset == NULL )
    {
        return;
    }
    // ���ȶ������ݼ��е�ÿ�����ε�������أ���ɹ�����������
    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    int *bandList = new int[bandCount];
    for ( int band = 1; band <= bandCount; band++ )
    {
        bandList[band - 1] = band;
    }
    
    SpectralCurve pixelCurve;// һ�����صĹ�������
    SpectralCurve targetCurve;// ����ƥ���Ŀ�����
    
    //.....just for test
    for ( int i = 0; i < bandCount; i++ )
    {
        curvePoint p;
        p.x = 1.5;
        p.y = 1.5;
        targetCurve.scVec.push_back( p );
    }
    this->disAlg->curve2 = &targetCurve;
    //.....just for test
    
    float *poData = new float[bandCount];
    float *poResultData = new float[dataWidth * dataHeight];// �������������
    int index = 0;
    for ( int height = 0; height < dataHeight; height++ )
    {
        for ( int width = 0; width < dataWidth; width++ )
        {
            poDataset->RasterIO( GF_Read, width, height,  1, 1, poData, 1, 1, GDT_Float32, bandCount, bandList, 0, 0, 0 );
            for ( int band = 0; band < bandCount; band++ )
            {
                curvePoint cp;
                cp.x = 0;
                cp.y = poData[band];
                pixelCurve.scVec.push_back( cp );
                
            }
            // �������ϴ���������pixelCurve����һ�����صĹ���������
            // ����������ȡ�����ݽ�����֯������Ӧ�ľ������
            this->disAlg->curve1 = &pixelCurve;
            
            float disValue = this->disAlg->CalculateDistance();
            pixelCurve.scVec.clear();
            poResultData[index++] = disValue;
        }
    }
    // now create the result image
    this->myMap->CreateImg( poResultData, dataWidth, dataHeight, 1 );
    
}