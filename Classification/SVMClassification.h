#pragma once
#include <string>
#include "ClassificationAlg.h"
#include "svm.h"
#include <vector>
#include <map>

using namespace std;


class SVMClassification : public ClassificationAlg
{
public:
    SVMClassification( void );
    ~SVMClassification( void );
    
    void TrainModel( const string roiFilename , const string modelFileName = "" );
    float runAlg( float* srcData, string roiFileName, int bandCount, string modelFileName = ""  );
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
    
    /// <summary>
    /// the total count of the classes
    /// </summary>
    int classCount;
    /// <summary>
    /// the name of each roi
    /// </summary>
    vector<string> roiName;
    /// <summary>
    /// The roi map
    /// </summary>
    map<std::string, int> roiMap;
};

