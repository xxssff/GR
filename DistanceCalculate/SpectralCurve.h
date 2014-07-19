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
    float x;
    /// <summary>
    /// The y
    /// </summary>
    float y;
};

class SpectralCurve
{
public:
    SpectralCurve( void ) {} ;
    ~SpectralCurve( void ) {};
    
    /// <summary>
    /// ������������
    /// </summary>
    vector<curvePoint> scVec;
};

