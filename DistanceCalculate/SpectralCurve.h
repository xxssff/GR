#pragma once
#include <vector>

using namespace std;

/// <summary>
/// Struct CurvePoint
/// </summary>
struct curvePoint
{
    /// <summary>
    /// The x
    /// </summary>
    double x;
    /// <summary>
    /// The y
    /// </summary>
    double y;
};

class SpectralCurve
{
public:
    SpectralCurve( void );
    ~SpectralCurve( void );
    
    /// <summary>
    /// ������������
    /// </summary>
    vector<curvePoint> *scVec;
};

