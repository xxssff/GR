#pragma once

#include "DistanceAlg.h"

class SpectralCurve;

class EuclideanDisntance: public DistanceAlg
{
public:
    EuclideanDisntance( void );
    EuclideanDisntance( SpectralCurve* cur1, SpectralCurve* cur2 );
    
    ~EuclideanDisntance( void );
    
    virtual float CalculateDistance();
};

