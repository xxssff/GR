#include "GRIsoDataClassifier.h"

#include "gdal_priv.h"
#include "gdal_rat.h"

#define RELEASE(x) if(x!=NULL) { delete []x; x = NULL; }

#ifndef FLT_ZERO
/*! 浮点数是否为0 */
#define FLT_ZERO(x)  (fabs(x)<FLT_EPSILON)
#endif

#ifndef M_SQUARE
# define M_SQUARE(x)  (x)*(x)
#endif

namespace GR
{
namespace classifier
{


/*! byte */
typedef unsigned char	byte;
/*! 8U */
typedef unsigned char	DT_8U;
/*! 16U */
typedef unsigned short	DT_16U;
/*! 16S */
typedef short			DT_16S;
/*! 32U */
typedef unsigned int	DT_32U;
/*! 32S */
typedef int				DT_32S;
/*! 32F */
typedef float			DT_32F;
/*! 64F */
typedef double			DT_64F;

class ISODATACalcPixelClusterCalcImageVal
{
public:
    ISODATACalcPixelClusterCalcImageVal( GDALDataset* poSrcDS, std::vector<ClusterCentreISO*> *clusterCentres )
    {
        this->clusterCentres = clusterCentres;
        this->numImageBands = numImageBands;
        this->poSrcDS = poSrcDS;

        nXSize = poSrcDS->GetRasterXSize();
        nYSize = poSrcDS->GetRasterYSize();
        numImageBands = poSrcDS->GetRasterCount();

        newClusterCentres = new std::vector<ClusterCentreISO*>();
        ClusterCentreISO *tmpCluster = NULL;
        std::vector<ClusterCentreISO*>::iterator iterCentres;
        for( iterCentres = clusterCentres->begin(); iterCentres != clusterCentres->end(); ++iterCentres )
        {
            tmpCluster = new ClusterCentreISO();
            tmpCluster->classID = ( *iterCentres )->classID;
            tmpCluster->data = std::vector<double>( numImageBands );
            tmpCluster->stddev = std::vector<double>( numImageBands );
            tmpCluster->numVals = 0;
            tmpCluster->avgDist = 0;
            tmpCluster->split = false;
            newClusterCentres->push_back( tmpCluster );
        }

        sumDist = 0;
        numVals = 0;
    }

    void CalcNewClusterCentres()
    {
        int *pBandMap = new int[numImageBands];
        for ( int i = 0; i < numImageBands; i++ )
        {
            pBandMap[i] = i + 1;
        }

        DT_32F *pBuffer = new DT_32F[nXSize * numImageBands];
        DT_32F *pBandValues = new DT_32F[numImageBands];

        for ( int i = 0; i < nYSize; i++ )
        {
            poSrcDS->RasterIO( GF_Read, 0, i, nXSize, 1, pBuffer, nXSize, 1, GDT_Float32, numImageBands, pBandMap,
                               numImageBands * sizeof( DT_32F ), nXSize * numImageBands * sizeof( DT_32F ), sizeof( DT_32F ) );

            for ( int j = 0; j < nXSize; j++ )
            {
                for( int k = 0; k < numImageBands; ++k )
                {
                    pBandValues[k] = pBuffer[j * numImageBands + k];
                }

                // 计算每一个点到各个聚类中心的距离
                double minDistance = 0;
                ClusterCentreISO *minClusterCentre = NULL;
                bool first = true;
                double sum = 0;
                double distance = 0;
                std::vector<ClusterCentreISO*>::iterator iterCentres;
                for( iterCentres = clusterCentres->begin(); iterCentres != clusterCentres->end(); ++iterCentres )
                {
                    sum = 0;
                    for( int k = 0; k < numImageBands; ++k )
                    {
                        sum += M_SQUARE( ( *iterCentres )->data[k] - pBandValues[k] );
                    }

                    distance = sum / numImageBands;

                    if( first )
                    {
                        minDistance = distance;
                        minClusterCentre = *iterCentres;
                        first = false;
                    }
                    else if( distance < minDistance )
                    {
                        minDistance = distance;
                        minClusterCentre = *iterCentres;
                    }
                }

                CPLDebug( "ISODATA", "Pixel assocaited with cluster %d\n", minClusterCentre->classID );

                // 更新当前像素所在的聚类中心的信息
                for( iterCentres = newClusterCentres->begin(); iterCentres != newClusterCentres->end(); ++iterCentres )
                {
                    if( ( *iterCentres )->classID == minClusterCentre->classID )
                    {
                        for( int k = 0; k < numImageBands; ++k )
                        {
                            ( *iterCentres )->data[k] += pBandValues[k];
                        }

                        ( *iterCentres )->numVals += 1;
                        ( *iterCentres )->avgDist += minDistance;
                        break;
                    }
                }

                sumDist += minDistance;
                ++numVals;
            }
        }

        RELEASE( pBandMap );
        RELEASE( pBandValues );
        RELEASE( pBuffer );
    }

    std::vector<ClusterCentreISO*>* getNewClusterCentres()
    {
        return newClusterCentres;
    }

    void reset( std::vector<ClusterCentreISO*> *clusterCentres )
    {
        // 清空newClusterCentres中的所有数据
        std::vector<ClusterCentreISO*>::iterator iterCentres;
        for( iterCentres = newClusterCentres->begin(); iterCentres != newClusterCentres->end(); )
        {
            ( *iterCentres )->data.clear();
            ( *iterCentres )->stddev.clear();
            delete ( *iterCentres );
            newClusterCentres->erase( iterCentres );
        }
        delete newClusterCentres;

        // 重新给newClusterCentres设置初始值等信息
        this->clusterCentres = clusterCentres;

        newClusterCentres = new std::vector<ClusterCentreISO*>();
        ClusterCentreISO *tmpCluster = NULL;
        for( iterCentres = clusterCentres->begin(); iterCentres != clusterCentres->end(); ++iterCentres )
        {
            tmpCluster = new ClusterCentreISO();
            tmpCluster->classID = ( *iterCentres )->classID;
            tmpCluster->data = std::vector<double>( numImageBands );
            tmpCluster->stddev = std::vector<double>( numImageBands );
            tmpCluster->numVals = 0;
            tmpCluster->avgDist = 0;
            tmpCluster->split = false;
            newClusterCentres->push_back( tmpCluster );
        }

        sumDist = 0;
        numVals = 0;
    }

    double getAverageDistance()
    {
        return sumDist / numVals;
    }

    ~ISODATACalcPixelClusterCalcImageVal()
    {
        std::vector<ClusterCentreISO*>::iterator iterCentres;
        for( iterCentres = newClusterCentres->begin(); iterCentres != newClusterCentres->end(); )
        {
            ( *iterCentres )->data.clear();
            ( *iterCentres )->stddev.clear();
            delete ( *iterCentres );
            newClusterCentres->erase( iterCentres );
            iterCentres = newClusterCentres->begin();
        }

        newClusterCentres->clear();
        delete newClusterCentres;
    }

protected:
    std::vector<ClusterCentreISO*> *clusterCentres;
    std::vector<ClusterCentreISO*> *newClusterCentres;
    double sumDist;
    unsigned long numVals;

    GDALDataset *poSrcDS;
    int nXSize;
    int nYSize;
    int numImageBands;
};

GRIsoDataClassifier::GRIsoDataClassifier( void )
{
    m_nMinClassesNumber = 5;
    m_nMaxClassesNumber = 10;
    m_dfChangeThreshold = 0.05;
    m_nMaxIterations = 1;
    m_nMinPixels = 1;
    m_dfMaxClassStdv = 1;
    m_dfMinClassDistance = 5.0;
    m_dfPropOverAvgDist = 1.0;

    m_dfMaxStddev = 1;
    m_dfMaxDistance = 1;

    m_pvClusterCentres = NULL;
    m_nClasserNumber = 7;

    inputFilename = "";
    outputFilename = "";

    GDALAllRegister();
    CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );
}

GRIsoDataClassifier::~GRIsoDataClassifier( void )
{
    if( m_pvClusterCentres != NULL )
    {
        std::vector<ClusterCentreISO*>::iterator iterCentres;
        for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); )
        {
            ( *iterCentres )->data.clear();
            ( *iterCentres )->stddev.clear();
            delete ( *iterCentres );
            m_pvClusterCentres->erase( iterCentres );
            iterCentres = m_pvClusterCentres->begin();
        }

        m_pvClusterCentres->clear();
        delete m_pvClusterCentres;
        m_pvClusterCentres = NULL;
    }
}



void GetClassColorArray( int *panColorArray )
{
    int anColorArray[150] =
    {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255,
        255, 255, 0,
        0, 255, 255,
        255, 0, 255,
        176, 48, 96,
        46, 139, 87,
        160, 32, 240,
        255, 127, 80,
        127, 255, 212,
        218, 112, 214,
        160, 82, 45,
        127, 255, 0,
        216, 191, 216,
        238, 0, 0,
        205, 0, 0,
        139, 0, 0,
        0, 238, 0,
        0, 205, 0,
        0, 139, 0,
        0, 0, 238,
        0, 0, 205,
        0, 0, 139,
        238, 238, 0,
        205, 205, 0,
        139, 139, 0,
        0, 238, 238,
        0, 205, 205,
        0, 139, 139,
        238, 0, 238,
        205, 0, 205,
        139, 0, 139,
        238, 48, 167,
        205, 41, 144,
        139, 28, 98,
        145, 44, 238,
        125, 38, 205,
        85, 26, 139,
        255, 165, 0,
        238, 154, 0,
        205, 133, 0,
        139, 90, 0,
        238, 121, 66,
        205, 104, 57,
        139, 71, 38,
        238, 210, 238,
        205, 181, 205,
        0, 0, 0,
        255, 255, 255
    };

    memcpy( panColorArray, anColorArray, sizeof( int ) * 150 );
}

double EuclideanDistance( const std::vector<double> &vecA, const std::vector<double> &vecB )
{
    if( vecA.size() != vecB.size() )
    {
        printf( "Vectors need to be of the same length for the distance to be calculated.\n" );
        return DBL_MAX;
    }

    double sum = 0;
    for( size_t i = 0; i < vecA.size(); ++i )
    {
        sum += M_SQUARE( vecA[i] - vecB[i] );
    }

    double distance = sqrt( sum / vecA.size() );
    return distance;
}

void CalcPixelClusterStdDevCalcImageVal( std::vector<ClusterCentreISO*> *clusterCentres, GDALDataset* poSrcDS )
{
    int nXSize = poSrcDS->GetRasterXSize();
    int nYSize = poSrcDS->GetRasterYSize();
    int nBandCount = poSrcDS->GetRasterCount();

    int *pBandMap = new int[nBandCount];
    for ( int i = 0; i < nBandCount; i++ )
    {
        pBandMap[i] = i + 1;
    }

    DT_32F *pBuffer = new DT_32F[nXSize * nBandCount];
    DT_32F *pBandValues = new DT_32F[nBandCount];

    for ( int i = 0; i < nYSize; i++ )
    {
        poSrcDS->RasterIO( GF_Read, 0, i, nXSize, 1, pBuffer, nXSize, 1, GDT_Float32, nBandCount, pBandMap,
                           nBandCount * sizeof( DT_32F ), nXSize * nBandCount * sizeof( DT_32F ), sizeof( DT_32F ) );

        for ( int j = 0; j < nXSize; j++ )
        {
            for( int k = 0; k < nBandCount; ++k )
            {
                pBandValues[k] = pBuffer[j * nBandCount + k];
            }

            // 计算每个像元值到聚类中心的信息
            double minDistance = 0;
            ClusterCentreISO *minClusterCentre = NULL;
            bool first = true;
            double sum = 0;
            double distance = 0;
            std::vector<ClusterCentreISO*>::iterator iterCentres;

            for( iterCentres = clusterCentres->begin(); iterCentres != clusterCentres->end(); ++iterCentres )
            {
                sum = 0;
                for( int k = 0; k < nBandCount; ++k )
                {
                    sum += ( M_SQUARE( ( *iterCentres )->data[k] - pBandValues[k] ) );
                }

                distance = sum / nBandCount;

                if( first )
                {
                    minDistance = distance;
                    minClusterCentre = *iterCentres;
                    first = false;
                }
                else if( distance < minDistance )
                {
                    minDistance = distance;
                    minClusterCentre = *iterCentres;
                }
            }

            CPLDebug( "ISODATA", "Pixel assocaited with cluster %d\n", minClusterCentre->classID );

            // 计算标准差，目前只是计算差的平方和，后续处理
            for( int k = 0; k < nBandCount; ++k )
            {
                minClusterCentre->stddev[k] += M_SQUARE( minClusterCentre->data[k] - pBandValues[k] );
            }
        }
    }

    RELEASE( pBandMap );
    RELEASE( pBandValues );
    RELEASE( pBuffer );
}

void CalcPixelClusterCalcImageVal( std::vector<ClusterCentreISO*> *clusterCentres, GDALDataset* poSrcDS, GDALDataset* poDstDS )
{
    int nXSize = poSrcDS->GetRasterXSize();
    int nYSize = poSrcDS->GetRasterYSize();
    int nBandCount = poSrcDS->GetRasterCount();

    int *pBandMap = new int[nBandCount];
    for ( int i = 0; i < nBandCount; i++ )
    {
        pBandMap[i] = i + 1;
    }

    DT_32F *pBuffer = new DT_32F[nXSize * nBandCount];
    DT_32F *pBandValues = new DT_32F[nBandCount];

    DT_8U *pOut = new DT_8U[nXSize];

    GDALRasterBand *pDstBand = poDstDS->GetRasterBand( 1 );

    for ( int i = 0; i < nYSize; i++ )
    {
        poSrcDS->RasterIO( GF_Read, 0, i, nXSize, 1, pBuffer, nXSize, 1, GDT_Float32, nBandCount, pBandMap,
                           nBandCount * sizeof( DT_32F ), nXSize * nBandCount * sizeof( DT_32F ), sizeof( DT_32F ) );

        for ( int j = 0; j < nXSize; j++ )
        {
            for( int k = 0; k < nBandCount; ++k )
            {
                pBandValues[k] = pBuffer[j * nBandCount + k];
            }

            double minDistance = 0;
            unsigned int minIdx = 0;
            bool first = true;
            double sum = 0;
            double distance = 0;
            std::vector<ClusterCentreISO*>::iterator iterCentres;

            for( iterCentres = clusterCentres->begin(); iterCentres != clusterCentres->end(); ++iterCentres )
            {
                sum = 0;
                for( int k = 0; k < nBandCount; ++k )
                {
                    sum += M_SQUARE( ( *iterCentres )->data[k] - pBandValues[k] );
                }

                distance = sum / nBandCount;

                if( first )
                {
                    minDistance = distance;
                    minIdx = ( *iterCentres )->classID;
                    first = false;
                }
                else if( distance < minDistance )
                {
                    minDistance = distance;
                    minIdx = ( *iterCentres )->classID;
                }
            }

            pOut[j] = minIdx;
        }

        pDstBand->RasterIO( GF_Write, 0, i, nXSize, 1, pOut, nXSize, 1, GDT_Byte, 0, 0 );
    }

    RELEASE( pBandMap );
    RELEASE( pOut );
    RELEASE( pBandValues );
    RELEASE( pBuffer );

    // 设置颜色表和类别信息
    GDALDefaultRasterAttributeTable oRAT;
    oRAT.CreateColumn( "ClassID", GFT_Integer, GFU_Generic );
    oRAT.CreateColumn( "Name", GFT_String, GFU_Name );

    GDALColorTable *pCT = new GDALColorTable( GPI_RGB );

    int anColorArray[150] = {0};
    GetClassColorArray( anColorArray );

    int nColorIndex = 0;
    char** papszCategoryNames = NULL;
    for ( size_t i = 0; i < clusterCentres->size(); i++ )
    {
        if( nColorIndex >= 150 )
        {
            nColorIndex = 0;
        }

        GDALColorEntry Entry;
        Entry.c1 = anColorArray[nColorIndex++];
        Entry.c2 = anColorArray[nColorIndex++];
        Entry.c3 = anColorArray[nColorIndex++];

        pCT->SetColorEntry( i, &Entry );

        oRAT.SetValue( i, 0, ( *clusterCentres )[i]->classID );
        oRAT.SetValue( i, 1, ( *clusterCentres )[i]->className.c_str() );
        papszCategoryNames = CSLAppendPrintf( papszCategoryNames, "Class %d", i );
    }

    pDstBand->SetDefaultRAT( &oRAT );
    pDstBand->SetColorTable( pCT );
    pDstBand->SetCategoryNames( papszCategoryNames );
    CSLDestroy( papszCategoryNames );

    poDstDS->SetDescription( "ISODATA Classification Result" );
}

bool GRIsoDataClassifier::ParametersCheck()
{
    //// 输入参数
    //if ( mInImgDataArr.size() != 1 )
    //{
    //    return false;
    //}

    //GDALDataset *pImgDataSet_In = mInImgDataArr[0]->mpGdalDataSet;
    //int bandCnt = pImgDataSet_In->GetRasterCount();
    //if ( bandCnt < 2 )
    //{
    //    mMsg = "band counts less than 2";
    //    //mMsg="波段数太少";
    //    return false;
    //}

    //// 输出参数
    //if ( mOutImgDataArr.size() != 1 )
    //{
    //    mMsg = "out file is not setting";
    //    //mMsg="未设置输出参数";
    //    return false;
    //}
    return true;
}

bool GRIsoDataClassifier::Execute()
{
    try
    {
        float fTotalStep = m_nMaxIterations + 2.0;


//        CImageData *pImgDt_In = mInImgDataArr[0];
        // CImageData *pImgDt_Out = mOutImgDataArr[0];
        //GDALDataset *poSrcDS = pImgDt_In->mpGdalDataSet;// ?

        GDALDataset *poSrcDS = ( GDALDataset * )GDALOpen( inputFilename.c_str(), GA_ReadOnly );

        int imgXSize = poSrcDS->GetRasterXSize();
        int imgYSize = poSrcDS->GetRasterYSize();
        int nBandCount = poSrcDS->GetRasterCount();
        GDALDataType gdalDataType = poSrcDS->GetRasterBand( 1 )->GetRasterDataType();

        /*if ( pImgDt_Out->mDataOpenForm == DOF_MemTemp )
        {
            pImgDt_Out->mpGdalDataSet =
                CUtility::createMemDataset( poSrcDS, imgXSize, imgYSize, 1, GDT_Byte, NullPointer );
        }
        else
        {
            pImgDt_Out->mpGdalDataSet =
                CUtility::createGeneralDataset( poSrcDS, pImgDt_Out->mFullFileName.c_str(), imgXSize, imgYSize, 1, GDT_Byte, "ENVI" );
        }*/

        //GDALDataset *poDstDS = pImgDt_Out->mpGdalDataSet;

        const char* pszFormat = "ENVI";
        // 创建结果图像数据集
        GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName( pszFormat );
        GDALDataset* poDstDS = poDriver->Create( outputFilename.c_str(), imgXSize, imgYSize, 1, GDT_Byte, NULL );
        GDALRasterBand* pand = poDstDS->GetRasterBand( 1 );

        // 设置投影
        poDstDS->SetProjection( poSrcDS->GetProjectionRef() );
        double dfGeotransform[6] = {0};
        poSrcDS->GetGeoTransform( dfGeotransform );
        poDstDS->SetGeoTransform( dfGeotransform );

        //初始化聚类中心
        m_pvClusterCentres = new std::vector<ClusterCentreISO*>();
        ClusterCentreISO *tmpCluster = NULL;
        int nClusterIDVal = 0;	//分类后的像素值
        for( int i = 0; i < m_nClasserNumber; ++i )
        {
            tmpCluster = new ClusterCentreISO();
            tmpCluster->classID = nClusterIDVal++;
            tmpCluster->data = std::vector<double>( nBandCount );
            tmpCluster->stddev = std::vector<double>( nBandCount );
            tmpCluster->numVals = 0;
            tmpCluster->avgDist = 0;
            tmpCluster->split = false;
            m_pvClusterCentres->push_back( tmpCluster );
        }

        //计算原始图像的统计信息
        double *padfMinMax = new double[nBandCount * 2];
        for ( int i = 0; i < nBandCount; i++ )
        {
            poSrcDS->GetRasterBand( i + 1 )->ComputeRasterMinMax( FALSE, padfMinMax + i * 2 );
        }

        //boost::mt19937 randomGen; // 需要找方法代替 生成随机数

        std::vector<ClusterCentreISO*>::iterator iter;
        for( int i = 0; i < nBandCount; ++i )
        {
            //boost::uniform_int<> randomDist( ( int )padfMinMax[i * 2], ( int )padfMinMax[i * 2 + 1] );
            // boost::variate_generator<boost::mt19937&, boost::uniform_int<> > randomVal( randomGen, randomDist );

            double ran_numf = 0.0;
            srand( ( unsigned )time( 0 ) );

            // 随机设置聚类中心的像素值
            for( iter = m_pvClusterCentres->begin(); iter != m_pvClusterCentres->end(); ++iter )
            {
                //( *iter )->data[i] = randomVal();
                ( *iter )->data[i] = rand() / ( double )( padfMinMax[i * 2 + 1] / 10 );
            }
        }

        RELEASE( padfMinMax );

        // 下面开始进行分类处理
        ISODATACalcPixelClusterCalcImageVal *pCalcClusterCentre = NULL;
        pCalcClusterCentre = new ISODATACalcPixelClusterCalcImageVal( poSrcDS, m_pvClusterCentres );

        std::vector<ClusterCentreISO*> *newClusterCentres = NULL;
        double centreMoveDistanceSum = 0;
        double centreMoveDistance = 0;
        double averageDistance = 0;
        bool continueIterating = true;
        int iterNum = 0;

        std::vector<ClusterCentreISO*>::iterator iterCentres;
        std::vector<ClusterCentreISO*>::iterator iterCentres2;
        std::vector<ClusterCentreISO*>::iterator iterNewCentres;

        //if ( mpProgressBar )
        //{
        //    mpProgressBar->setValue( 1.0 / fTotalStep );
        //    //mpProgressBar->setMessage("正在执行ISODATA分类...");
        //    mpProgressBar->setMessage( "ISODATA Classify Processing..." );
        //}

        while( continueIterating && ( iterNum < m_nMaxIterations ) )
        {
            CPLDebug( "ISODATA", "Iteration %d:\t", iterNum );

            centreMoveDistanceSum = 0;
            centreMoveDistance = 0;
            averageDistance = 0;

            // 计算新的聚类中心
            pCalcClusterCentre->CalcNewClusterCentres();		//计算每一个像素，然后更新聚类信息
            newClusterCentres = pCalcClusterCentre->getNewClusterCentres();	//获取新的聚类信息

            // 计算新的聚类中心和老的聚类中心的距离
            iterNewCentres = newClusterCentres->begin();
            iterCentres = m_pvClusterCentres->begin();

            // 计算新的聚类中心的均值等信息
            for( size_t i = 0; i < m_pvClusterCentres->size(); ++i )
            {
                CPLDebug( "ISODATA", "Cluster %d has %d associated\n", ( *iterNewCentres )->classID, ( *iterNewCentres )->numVals );

                for( int j = 0; j < nBandCount; ++j )
                {
                    if( ( *iterNewCentres )->numVals == 0 )
                    {
                        ( *iterNewCentres )->data[j] = ( *iterCentres )->data[j];
                    }
                    else
                    {
                        ( *iterNewCentres )->data[j] = ( *iterNewCentres )->data[j] / ( *iterNewCentres )->numVals;
                    }
                }

                if( ( *iterNewCentres )->numVals != 0 )
                {
                    ( *iterNewCentres )->avgDist = ( *iterNewCentres )->avgDist / ( *iterNewCentres )->numVals;
                }

                centreMoveDistanceSum += EuclideanDistance( ( *iterNewCentres )->data, ( *iterCentres )->data );
                ++iterCentres;
                ++iterNewCentres;
            }

            centreMoveDistance = centreMoveDistanceSum / m_pvClusterCentres->size();
            CPLDebug( "ISODATA", "Distance Moved = %.6f from %d clusters\n", centreMoveDistance, newClusterCentres->size() );

            if( centreMoveDistance < m_dfChangeThreshold )
            {
                continueIterating = false;
                ++iterNum;

                /*if ( mpProgressBar )
                {
                    mpProgressBar->setValue( ( iterNum + 1.0 ) / fTotalStep );
                }*/

                continue;
            }

            // 计算聚类中心的标准差
            CalcPixelClusterStdDevCalcImageVal( newClusterCentres, poSrcDS ); //计算每一个像素

            for( iterNewCentres = newClusterCentres->begin(); iterNewCentres != newClusterCentres->end(); ++iterNewCentres )
            {
                for( int i = 0; i < nBandCount; ++i )
                {
                    if( ( *iterNewCentres )->numVals != 0 )
                    {
                        ( *iterNewCentres )->stddev[i] = sqrt( ( *iterNewCentres )->stddev[i] / ( *iterNewCentres )->numVals );
                    }
                    else
                    {
                        ( *iterNewCentres )->stddev[i] = 0;
                    }
                }
            }

            // 先清空老的聚类信息m_pvClusterCentres
            for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); )
            {
                ( *iterCentres )->data.clear();
                ( *iterCentres )->stddev.clear();
                delete ( *iterCentres );
                m_pvClusterCentres->erase( iterCentres );
                iterCentres = m_pvClusterCentres->begin();
            }

            // 再将新的聚类信息添加到m_pvClusterCentres中
            for( iterNewCentres = newClusterCentres->begin(); iterNewCentres != newClusterCentres->end(); )
            {
                m_pvClusterCentres->push_back( *iterNewCentres );
                newClusterCentres->erase( iterNewCentres );
                iterNewCentres = newClusterCentres->begin();
            }

            // 移除聚类中数量小于给定最小分类个数的聚类
            for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); )
            {
                if( ( *iterCentres )->numVals < m_nMinPixels )
                {
                    ( *iterCentres )->data.clear();
                    ( *iterCentres )->stddev.clear();
                    delete ( *iterCentres );
                    m_pvClusterCentres->erase( iterCentres );
                    iterCentres = m_pvClusterCentres->begin();
                }
                else
                {
                    ++iterCentres;
                }
            }

            // 对聚类中心的距离小于指定的距离则进行合并
            double distance = 0;
            for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); ++iterCentres )
            {
                CPLDebug( "ISODATA", "Checking %d\n", ( *iterCentres )->classID );

                for( iterCentres2 = m_pvClusterCentres->begin(); iterCentres2 != m_pvClusterCentres->end(); ++iterCentres2 )
                {
                    distance = EuclideanDistance( ( *iterCentres2 )->data, ( *iterCentres )->data );
                    CPLDebug( "ISODATA", "\tAgainst %d distance = %.6f\n", ( *iterCentres2 )->classID, distance );

                    if( ( distance != 0 ) & ( distance < m_dfMinClassDistance ) )
                    {
                        if( ( *iterCentres )->numVals < ( *iterCentres2 )->numVals )
                        {
                            ( *iterCentres )->data.clear();
                            ( *iterCentres )->stddev.clear();
                            delete ( *iterCentres );
                            m_pvClusterCentres->erase( iterCentres );
                        }
                        else
                        {
                            ( *iterCentres2 )->data.clear();
                            ( *iterCentres2 )->stddev.clear();
                            delete ( *iterCentres2 );
                            m_pvClusterCentres->erase( iterCentres2 );
                        }

                        iterCentres = m_pvClusterCentres->begin();
                        break;
                    }
                }
            }

            averageDistance = pCalcClusterCentre->getAverageDistance();	//获取均值
            CPLDebug( "ISODATA", "Overall Average distance = %.6f\n", averageDistance );

            for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); ++iterCentres )
            {
                ( *iterCentres )->split = false;
                CPLDebug( "ISODATA", "Checking %d Avg Dist = %.6f\n", ( *iterCentres )->classID, ( *iterCentres )->avgDist );

                if( ( *iterCentres )->avgDist > ( averageDistance * m_dfPropOverAvgDist ) )
                {
                    ( *iterCentres )->split = true;
                }
                else
                {
                    for( int i = 0; i < nBandCount; ++i )
                    {
                        CPLDebug( "ISODATA", "\tStddev band %d = %.6f\n", i, ( *iterCentres )->stddev[i] );

                        if( ( *iterCentres )->stddev[i] > m_dfMaxClassStdv )
                        {
                            ( *iterCentres )->split = true;
                        }
                    }
                }
            }

            ClusterCentreISO *tmpCluster2Split = NULL;
            ClusterCentreISO *tmpClusterNew1 = NULL;
            ClusterCentreISO *tmpClusterNew2 = NULL;
            for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); ++iterCentres )
            {
                if( ( *iterCentres )->split )
                {
                    tmpCluster2Split = *iterCentres;
                    m_pvClusterCentres->erase( iterCentres );

                    tmpClusterNew1 = new ClusterCentreISO();
                    tmpClusterNew1->classID = nClusterIDVal++;
                    tmpClusterNew1->data = std::vector<double>( nBandCount );
                    tmpClusterNew1->stddev = std::vector<double>( nBandCount );
                    tmpClusterNew1->numVals = 0;
                    tmpClusterNew1->avgDist = 0;
                    tmpClusterNew1->split = false;

                    tmpClusterNew2 = new ClusterCentreISO();
                    tmpClusterNew2->classID = nClusterIDVal++;
                    tmpClusterNew2->data = std::vector<double>( nBandCount );
                    tmpClusterNew2->stddev = std::vector<double>( nBandCount );
                    tmpClusterNew2->numVals = 0;
                    tmpClusterNew2->avgDist = 0;
                    tmpClusterNew2->split = false;

                    for( int i = 0; i < nBandCount; ++i )
                    {
                        tmpClusterNew1->data[i] = tmpCluster2Split->data[i] + tmpCluster2Split->stddev[i];
                        tmpClusterNew2->data[i] = tmpCluster2Split->data[i] - tmpCluster2Split->stddev[i];
                    }

                    tmpCluster2Split->data.clear();
                    tmpCluster2Split->stddev.clear();
                    delete tmpCluster2Split;

                    m_pvClusterCentres->push_back( tmpClusterNew1 );
                    m_pvClusterCentres->push_back( tmpClusterNew2 );

                    iterCentres = m_pvClusterCentres->begin();
                }
            }

            CPLDebug( "ISODATA", "Num cluster centres in new cluster centres  = %d\n", newClusterCentres->size() );

            newClusterCentres = NULL;
            pCalcClusterCentre->reset( m_pvClusterCentres );

            //int nCurrentSize = m_pvClusterCentres->size();
            //if(nCurrentSize >= m_nMinClassesNumber && m_nMaxClassesNumber >= nCurrentSize)
            //	continueIterating = false;

            ++iterNum;

            /*if ( mpProgressBar )
            {
            mpProgressBar->setValue( ( iterNum + 1.0 ) / fTotalStep );
            }*/
        }

        delete pCalcClusterCentre;

        //输出图像
        /*if ( mpProgressBar )
        {
        mpProgressBar->setMessage( "正在输出ISODATA分类结果..." );
        }*/

        int i = 0;
        for( iterCentres = m_pvClusterCentres->begin(); iterCentres != m_pvClusterCentres->end(); ++iterCentres )
        {
            ( *iterCentres )->classID = i++;
        }

        CPLDebug( "ISODATA", "%d clusters have been identified.\n", m_pvClusterCentres->size() );
        CalcPixelClusterCalcImageVal( m_pvClusterCentres, poSrcDS, poDstDS ); //计算每一个像素

        /* if ( mpProgressBar )
         {
             mpProgressBar->setValue( 1.0 );
         }*/

        // 设置文件类型为分类文件

        poDstDS->SetMetadataItem( "file_type", "ENVI Classification", "ENVI" );
        // 设置分类数目
        char strClassCount[64];
        itoa( m_nMinClassesNumber + 1, strClassCount, 10 ); //加上未分类的数目
        poDstDS->SetMetadataItem( "classes", strClassCount, "ENVI" );
        // 设置分类名
        std::string classNames = "{";
        classNames += "Unclassified,";
        for ( int i = 1; i <= m_nMinClassesNumber - 1; ++i )
        {
            classNames += "Class ";
            itoa( i, strClassCount, 10 );
            classNames += strClassCount;
            classNames += ",";
        }
        classNames += "Class ";
        itoa( m_nMinClassesNumber, strClassCount, 10 );
        classNames += strClassCount;
        classNames += "}";
        //char **papszClassNames = CUtility::gdalDataset_SplitList( classNames.c_str() );
        /*char **papszClassNames = NULL;
        poDstDS->GetRasterBand( 1 )->SetCategoryNames( papszClassNames );*/
        // CUtility::gdalCSLDestroy( papszClassNames );

        //if ( pImgDt_Out->getDataOpenForm() == DOF_General )
        //{
        //    pImgDt_Out->SaveImageData();
        //    //pImgDataSet_Out->FlushCache();
        //}
        GDALClose( poSrcDS );
        GDALClose( poDstDS );
        return true;
    }
    catch ( std::exception const &ex )
    {
        /*mMsg = ex.what();*/
    }
    return false;
}

}
}