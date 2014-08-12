#pragma once
#include <string>
#include "ClassificationAlg.h"
#include "svm.h"
#include <vector>


using namespace std;


class SVMClassification : public ClassificationAlg
{
public:
    SVMClassification( void );
    ~SVMClassification( void );
    
    void TrainModel( const string roiFilename = 0, const string modelFileName = 0 );
    float* runAlg( float* srcData, int bandCount );
private:
    void initialSVMPro( string fileName );
    void initialSVMPara();
    vector<string> split( std::string str, std::string pattern );
    
    /// <summary>
    /// The SVM problem, for train data organization
    /// </summary>
    svm_problem svmPro;
    /// <summary>
    /// The SVM parameter
    /// </summary>
    svm_parameter svmPara;
    /// <summary>
    /// The SVM model
    /// </summary>
    svm_model *model;
};

