#include "FrechetDistance.h"
#include <math.h>
#include "SpectralCurve.h"

using namespace std;

/// <summary>
/// Initializes a new instance of the <see cref="FrechetDistance"/> class.
/// </summary>
FrechetDistance::FrechetDistance( void )
{
}

/// <summary>
/// Initializes a new instance of the <see cref="FrechetDistance"/> class.
/// </summary>
/// <param name="cur1">��������1.</param>
/// <param name="cur2">��������2.</param>
FrechetDistance::FrechetDistance( SpectralCurve* cur1, SpectralCurve* cur2 )
{
    this->curve1 = cur1;
    this->curve2 = cur2;
}

/// <summary>
/// Finalizes an instance of the <see cref="FrechetDistance"/> class.
/// </summary>
FrechetDistance::~FrechetDistance( void )
{
}


/// <summary>
/// ����Frechet������Ҫ�ݹ���õļ��㺯��
/// </summary>
/// <param name="cal">The cal.</param>
/// <param name="i">The i.</param>
/// <param name="j">The j.</param>
/// <returns>double.</returns>
float FrechetDistance::Calculate ( float **cal, int i, int j )
{
    if ( cal[i][j] > -1.0 )
    {
        return cal[i][j];
    }
    else if ( i == 0 && j == 0 )
    {
        cal[i][j] = Distance ( 0, 0 );
    }
    else if ( i > 0 && j == 0 )
    {
        cal[i][j] = max ( Calculate ( cal, i - 1, 0 ), Distance ( i, 0 ) );
    }
    else if ( i == 0 && j > 0 )
    {
        cal[i][j] = max ( Calculate ( cal, 0, j - 1 ), Distance ( 0, j ) );
    }
    else if ( i > 0 && j > 0 )
    {
        cal[i][j] = max ( Min3 ( Calculate ( cal, i - 1, j ), Calculate ( cal, i - 1, j - 1 ), Calculate ( cal, i, j - 1 ) ), Distance ( i, j ) );
    }
    else
    {
        cal[i][j] = 0xFFFFFFFF;
    }
    
    return cal[i][j];
}

/// <summary>
/// ŷʽ����
/// </summary>
/// <param name="i">The i.</param>
/// <param name="j">The j.</param>
/// <returns>double.</returns>
float FrechetDistance::Distance ( int i, int j )
{
    return ( float )sqrt ( pow ( curve1->scVec->at( i ).x - curve2->scVec->at( j ).x, 2 ) + pow ( curve1->scVec->at( i ).y - curve2->scVec->at( j ).y, 2 ) );
}

/// <summary>
/// ����ֵ����Сֵ
/// </summary>
/// <param name="v1">The v1.</param>
/// <param name="v2">The v2.</param>
/// <param name="v3">The v3.</param>
/// <returns>float.</returns>
float FrechetDistance::Min3 ( float v1, float v2, float v3 )
{
    float minv = ( v1 < v2 ) ? v1 : v2;
    minv = ( minv < v3 ) ? minv : v3;
    return minv;
}

/// <summary>
/// ����������ߵ�Frechet����
/// </summary>
/// <returns>float.</returns>
float FrechetDistance::CalculateDistance()
{
    // if two spectral curves are initialized correctly
    if ( this->curve1 == NULL || this->curve2 == NULL )
    {
        return -1;
    }
    float disValue = 0.0;
    // Here is your Frechet distance algoritm codes
    
    // init cal[][]
    float **cal = new float *[curve1->scVec->size()];
    for ( unsigned int i = 0; i < curve2->scVec->size(); i++ )
    {
        cal[i] = new float[curve2->scVec->size()];
    }
    
    for ( unsigned int i = 0; i < curve1->scVec->size(); i++ )
    {
        for ( unsigned int j = 0; j < curve2->scVec->size(); j++ )
        {
            cal[i][j] = -1.0;
        }
    }
    
    //calculate distance
    disValue = Calculate ( cal, curve1->scVec->size() - 1, curve2->scVec->size() - 1 );
    
    //delete cal[][] pointer
    for ( unsigned int i = 0 ; i < curve1->scVec->size(); i++ )
    {
        delete []cal[i];
    }
    delete []cal;
    
    return disValue;
}
