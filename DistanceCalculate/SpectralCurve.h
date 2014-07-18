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
    /// 光谱曲线向量
    /// </summary>
    vector<curvePoint> *scVec;
};

