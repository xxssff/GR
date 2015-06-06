#include "GRSvmClassifier.h"

#include <iostream>
#include <fstream>
#include "gdal_priv.h"
#include "gdal_rat.h"

using namespace std;

namespace GR
{
namespace classifier
{


GRSvmClassifier::GRSvmClassifier()
{
    GDALAllRegister();
    CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );

    svmModel = NULL;
    enviRoi = NULL;
}


GRSvmClassifier::~GRSvmClassifier()
{
    delete svmModel;
    delete enviRoi;
}


bool GRSvmClassifier::run( std::string roiFilePath, std::string imgName, std::string saveName )
{

    intialSvmProFormSource( roiFilePath, imgName );
    initialSvmPara();
    trainModel();

    classification( imgName , saveName );

    return true;
}

void GRSvmClassifier::initialSvmPara()
{
    cout << "config parameters..." << endl;

    svmPara.svm_type = C_SVC;
    svmPara.kernel_type = RBF;
    svmPara.degree = 3;
    svmPara.gamma = 0.25;
    svmPara.coef0 = 0;
    svmPara.nu = 0.5;
    svmPara.cache_size = 1;
    svmPara.C = 100;
    svmPara.eps = 1e-3;
    svmPara.p = 0.1;
    svmPara.shrinking = 1;
    svmPara.nr_weight = 0;
    svmPara.weight_label = NULL;
    svmPara.weight = NULL;
    svmPara.probability = 0;
}

void GRSvmClassifier::trainModel()
{
    cout << "train model..." << endl;

    const char *error_msg;
    error_msg = svm_check_parameter( &svmPro, &svmPara );
    if ( error_msg )
    {
        cout << "error: " << error_msg << endl;
        exit( 1 );
    }
    svmModel = svm_train( &svmPro, &svmPara );

    cout << "model trainning done!" << endl;
}

void GRSvmClassifier::classification( std::string imgName, std::string saveName )
{
    GDALDataset* poDataset = ( GDALDataset* )GDALOpen( imgName.c_str(), GA_ReadOnly );
    if ( poDataset == NULL ) { throw "cannot open input file..."; }

    GDALRasterBand *pBand = poDataset->GetRasterBand( 1 );
    GDALDataType eDT = pBand->GetRasterDataType(); //获取数据类型

    int dataWidth = poDataset->GetRasterXSize();
    int dataHeight = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();
    int *bandList = new int[bandCount];
    for ( int band = 1; band <= bandCount; band++ ) { bandList[band - 1] = band; }

    int MAXINTBYTE = 1800000; //最大处理能力
    int rows = MAXINTBYTE / ( bandCount * dataWidth ); //单次处理行数
    int times = 0;

    // 创建输出图像
    const char* pszFormat = "ENVI";
    GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName( pszFormat );
    GDALDataset* poDS = poDriver->Create( saveName.c_str(), dataWidth, dataHeight, 1, GDT_Float32, NULL );
    GDALRasterBand* pand = poDS->GetRasterBand( 1 );

    // 获取坐标信息
    double adfGeoTransform[6];
    poDataset->GetGeoTransform( adfGeoTransform );
    int re = poDS->SetGeoTransform( adfGeoTransform );
    if ( re != 0 ) { cout << "设置坐标信息失败！" << endl; }
    // 获取投影信息
    const char *project = poDataset->GetProjectionRef();
    int c = poDS->SetProjection( project );
    if ( c != 0 ) { cout << "设置投影信息失败！" << endl; }

    // 设置图像颜色表等分类信息
    GDALDefaultRasterAttributeTable oRat;

    oRat.CreateColumn( "ClassID", GFT_Integer, GFU_Generic );
    oRat.CreateColumn( "Name", GFT_String, GFU_Name );

    GDALColorTable* pCT = new GDALColorTable( GPI_RGB );

    char** papszCategoryNames = NULL;
    for ( size_t i = 0; i < enviRoi->getRoiCounts(); i++ )
    {
        GDALColorEntry Entry;

        Entry.c1 = enviRoi->getENVIRoi( i )->color->getRed();
        Entry.c1 = enviRoi->getENVIRoi( i )->color->getGreen();
        Entry.c1 = enviRoi->getENVIRoi( i )->color->getBlue();

        pCT->SetColorEntry( i, &Entry );

        oRat.SetValue( i, 0, 1 );
        oRat.SetValue( i, 1, enviRoi->getENVIRoi( i )->name.c_str() );
        papszCategoryNames = CSLAppendPrintf( papszCategoryNames, enviRoi->getENVIRoi( i )->name.c_str(), i );
    }

    pand->SetDefaultRAT( &oRat );
    pand->SetColorTable( pCT );
    pand->SetCategoryNames( papszCategoryNames );
    CSLDestroy( papszCategoryNames );

    poDS->SetMetadataItem( "file_type", "ENVI Classification", "ENVI" );
    char strClassCount[64];
    itoa( enviRoi->getRoiCounts(), strClassCount, 10 ); //加上未分类的数目
    poDS->SetMetadataItem( "classes", strClassCount, "ENVI" );

    if( dataHeight % rows == 0 ) { times = dataHeight / rows; }
    else { times = dataHeight / rows + 1; }

    cout << "classify start..." << endl;

    for	( int i = 0; i < times; i++ )
    {
        int cliprow = 0;
        if( ( i + 1 )*rows < dataHeight ) { cliprow = rows; }
        else { cliprow = dataHeight - i * rows; }

        float *poDataRead = new float[bandCount * dataWidth * cliprow];
        float *poDataWrite = new float[dataWidth * cliprow];

        poDataset->RasterIO( GF_Read,  0, 0 + i * rows, dataWidth, cliprow, poDataRead,  dataWidth, cliprow, GDT_Float32, bandCount, bandList, 0, 0, 0 );

        for( int j = 0; j < dataWidth * cliprow; j++ )
        {
            svm_node *xSpace = new svm_node[bandCount + 1];
            for ( int k = 0; k < bandCount; k++ )
            {
                xSpace[k].index = k + 1;
                xSpace[k].value = poDataRead[k * dataWidth * cliprow + j];
            }
            xSpace[bandCount].index = -1;

            if ( xSpace != NULL ) { poDataWrite[j] = svm_predict( svmModel, xSpace ); }

            delete xSpace;

        }
        pand->RasterIO( GF_Write, 0, 0 + i * rows, dataWidth, cliprow, poDataWrite, dataWidth, cliprow, GDT_Float32, 0, 0 );

        delete poDataRead;
        delete poDataWrite;


        //// 分类后处理，主要性分析
        //GDALDataset* ds = poDriver->Create( ( saveName.substr( 0, saveName.size() - 4 ) + "_with_post.tif" ).c_str(),
        //                                    dataWidth, dataHeight, 1, GDT_Float32, NULL );
        //filterProcessing( poDS, ds );
        //GDALClose( ds );

        GDALClose( poDataset );
        GDALClose( poDS );
    }

}

void GRSvmClassifier::intialSvmProFormSource( std::string roiFilePath, std::string imgName )
{
    enviRoi = new GR::utils::GREnviAsciiRoi( roiFilePath );
    int totalRoiSamplesCount = enviRoi->getTotalRoiSamplesCount();
    int varCount = enviRoi->getVariableCount();
    int nodeIndex = 0;
    int roiID = 0;

    svm_node **node = new svm_node *[totalRoiSamplesCount];
    double* y1 = new double[totalRoiSamplesCount];

    // 初始化样本标签
    for ( int i = 0; i < enviRoi->getRoiCounts(); i++ )
    {
        for ( int k = 0; k < enviRoi->getENVIRoi( i )->samples; k++ )
        {
            svm_node *xSpace = new svm_node[varCount + 1];
            for ( int j = 0; j < varCount; j++ )
            {
                xSpace[j].index = j + 1;
                xSpace[j].value = 0;// make sure its initial value is 0.
                double val = enviRoi->getENVIRoi( i )->data->matrix[k * varCount + j];
                xSpace[i].value = val;
            }
            xSpace[varCount].index = -1;
            node[nodeIndex++] = xSpace;
        }

        for ( int j = 0; j < enviRoi->getENVIRoi( i )->samples; j++ )
        {
            y1[j] = roiID++;
        }
    }

    svmPro.l = nodeIndex;
    svmPro.x = node;
    svmPro.y = y1;
}

float GRSvmClassifier::majorityFilterAlg( float * pafWindow, float fDstNoDataValue )
{
    return 0;
}


}
}