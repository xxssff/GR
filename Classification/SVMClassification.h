#pragma once
#include <string>

using namespace std;

class SVMClassification :
    public ClassificationAlg
{
public:
    SVMClassification( void );
    ~SVMClassification( void );
    
    svm_model* TrainModel( const string modelFileName = 0 );
    
};

