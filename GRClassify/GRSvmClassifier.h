#pragma once

#include "svm.h"

#include <string>

#include "..\GRUtils\GREnviAsciiRoi.h"

namespace GR
{
namespace classifier
{

/// <summary>
/// SVM classification algorithm.
/// </summary>
class __declspec( dllexport ) GRSvmClassifier
{
public:
    GRSvmClassifier();
    ~GRSvmClassifier();

    bool run( std::string roiFilePath, std::string modelPath, std::string imgName, std::string saveName );

private:
    svm_problem svmPro;// 训练样本
    svm_parameter svmPara;// 训练参数
    svm_model *svmModel;// 模型

    // 初始化参数列表
    void initialSvmPara();
    // 训练模型
    void trainModel( std::string modelPath );
    // 分类
    void classification( std::string imgName, std::string saveName );
    // 初始化训练样本，直接从envi导出的roi文本文件中初始化
    void intialSvmProFormSource( std::string roiFilePath, std::string imgName );

    // 主要类别分析算法，返回中心像元类别编码
    float majorityFilterAlg ( float * pafWindow, float fDstNoDataValue );
    //CPLErr filterProcessing  ( GDALDataset* poDataset, GDALDataset* pDstDataset );

    GR::utils::GREnviAsciiRoi* enviRoi;
};

}
}