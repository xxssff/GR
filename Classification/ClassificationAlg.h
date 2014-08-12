#pragma once
class ClassificationAlg
{
public:
    ClassificationAlg( void );
    ~ClassificationAlg( void );
    
    virtual float* runAlg( float* srcData, int bandCount ) = 0;
};

