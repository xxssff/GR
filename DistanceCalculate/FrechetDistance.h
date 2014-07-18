#pragma once

#include "DistanceAlg.h"

class SpectralCurve;

class FrechetDistance :    public DistanceAlg
{
public:
    FrechetDistance( void );
    FrechetDistance( SpectralCurve* cur1, SpectralCurve* cur2 );
    ~FrechetDistance( void );
    
    virtual float CalculateDistance();
    
private:
    float Calculate ( float **cal, int i, int j );
    float Distance ( int i, int j );
    float Min3 ( float d1, float d2, float d3 );
};

