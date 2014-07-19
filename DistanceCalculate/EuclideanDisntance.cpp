#include "EuclideanDisntance.h"
#include "SpectralCurve.h"
#include <math.h>

EuclideanDisntance::EuclideanDisntance( SpectralCurve* cur1, SpectralCurve* cur2 )
{
    this->curve1 = cur1;
    this->curve2 = cur2;
}

EuclideanDisntance::EuclideanDisntance( void )
{

}


EuclideanDisntance::~EuclideanDisntance( void )
{
}

float EuclideanDisntance::CalculateDistance()
{
    float disValue = 0;
    float tempdis = 0;
    float y = this->curve1->scVec.at( 0 ).y;
    for ( unsigned int i = 0; i < curve1->scVec.size(); i++ )
    {
        tempdis += pow ( this->curve1->scVec[i].y - this->curve2->scVec[i].y, 2 );
    }
    disValue = sqrt ( tempdis );
    
    return disValue;
    
}
