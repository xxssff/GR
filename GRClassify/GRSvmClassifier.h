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

    bool run( std::string roiFilePath, std::string imgName, std::string saveName );

private:
    svm_problem svmPro;// training sample variabel
    svm_parameter svmPara;// training parameters
    svm_model *svmModel;// model
    GR::utils::GREnviAsciiRoi* enviRoi; // to store envi rois

    /// <summary>
    /// initialize svm parametes.
    /// <summary>
    void initialSvmPara();
    // train model
    void trainModel();
    // classify algorithm
    void classification( std::string imgName, std::string saveName );
    // initialize svm problem form envi roi source file
    void intialSvmProFormSource( std::string roiFilePath, std::string imgName );

    // majority process, post classification processing
    float majorityFilterAlg ( float * pafWindow, float fDstNoDataValue );
    //CPLErr filterProcessing  ( GDALDataset* poDataset, GDALDataset* pDstDataset );


};

}
}