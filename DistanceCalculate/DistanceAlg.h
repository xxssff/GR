// ***********************************************************************
// Assembly         : DistanceCalculate
// Author           : Jacory
// Created          : 07-17-2014
//
// Last Modified By : Jacory
// Last Modified On : 07-17-2014
// ***********************************************************************
// <copyright file="DistanceAlg.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>�����㷨������</summary>
// ***********************************************************************
#pragma once

#include "SpectralCurve.h"


/// <summary>
/// Class DistanceAlg.
/// </summary>
class DistanceAlg
{
public:
    /// <summary>
    /// Initializes a new instance of the <see cref="DistanceAlg"/> class.
    /// </summary>
    DistanceAlg( void )
    {
        this->curve1 = NULL;
        this->curve2 = NULL;
    };
    /// <summary>
    /// Finalizes an instance of the <see cref="DistanceAlg"/> class.
    /// </summary>
    ~DistanceAlg( void ) {};
    
    /// <summary>
    /// ��������1
    /// </summary>
    SpectralCurve *curve1;
    /// <summary>
    /// ��������2
    /// </summary>
    SpectralCurve *curve2;
    
    /// <summary>
    /// Sets the curve.
    /// </summary>
    /// <param name="cur1">The cur1.</param>
    /// <param name="cur2">The cur2.</param>
    void SetCurve( SpectralCurve* cur1, SpectralCurve *cur2 )
    {
        this->curve1 = cur1;
        this->curve2 = cur2;
    };
    
    /// <summary>
    /// ����������������֮��ľ���
    /// </summary>
    /// <returns>float.</returns>
    virtual float CalculateDistance() = 0;
};

