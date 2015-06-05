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
    svm_problem svmPro;// ѵ������
    svm_parameter svmPara;// ѵ������
    svm_model *svmModel;// ģ��

    // ��ʼ�������б�
    void initialSvmPara();
    // ѵ��ģ��
    void trainModel( std::string modelPath );
    // ����
    void classification( std::string imgName, std::string saveName );
    // ��ʼ��ѵ��������ֱ�Ӵ�envi������roi�ı��ļ��г�ʼ��
    void intialSvmProFormSource( std::string roiFilePath, std::string imgName );

    // ��Ҫ�������㷨������������Ԫ������
    float majorityFilterAlg ( float * pafWindow, float fDstNoDataValue );
    //CPLErr filterProcessing  ( GDALDataset* poDataset, GDALDataset* pDstDataset );

    GR::utils::GREnviAsciiRoi* enviRoi;
};

}
}