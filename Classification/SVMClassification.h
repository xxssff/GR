// ***********************************************************************
// Assembly         : Classification
// Author           : Jacory
// Created          : 08-10-2014
//
// Last Modified By : Jacory
// Last Modified On : 08-13-2014
// ***********************************************************************
// <copyright file="SVMClassification.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>Support Vector Machine分类方法类</summary>
// ***********************************************************************
#pragma once
#include <string>
#include "ClassificationAlg.h"
#include "svm.h"
#include <vector>
#include <map>

using namespace std;


/// <summary>
/// Class SVMClassification.
/// </summary>
class SVMClassification : public ClassificationAlg
{
public:
    SVMClassification( void );
    ~SVMClassification( void );
    float* runAlg( float** srcData );
    
    //setters and getters
    void SetRoiFile( const string rFile );
    void SetModelFile( const string mFile );
    void SetModelFileSave( const string msFile );
    void SetBandCount( int count );
    void SetPixelCount( int count );
    void SetParameter( svm_parameter &para );
    string GetRoiFile();
    string GetModelFile();
    string GetModelFileSave();
    int GetBandCount();
    int GetPixelCount();
    
private:
    void initialSVMPro();
    void initialParameter();
    vector<string> split( string str, string pattern );
    void TrainModel();
    void SaveModel();
    void Scale( svm_node** srcData );
    
    string roiFile;
    string modelFile;
    string modelFileSave;
    int bandCount;
    int pixelCount;
    
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
    svm_model *svmModel;
    
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

