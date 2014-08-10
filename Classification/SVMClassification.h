#pragma once
#include <string>
#include "ClassificationAlg.h"
#include "svm.h"

using namespace std;

class SVMClassification :
    public ClassificationAlg
{
public:
    SVMClassification( void );
    ~SVMClassification( void );
    
    svm_model* TrainModel( const string modelFileName = 0 );
    
};

