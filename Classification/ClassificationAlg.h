// ***********************************************************************
// Assembly         : Classification
// Author           : Jacory
// Created          : 08-10-2014
//
// Last Modified By : Jacory
// Last Modified On : 08-13-2014
// ***********************************************************************
// <copyright file="ClassificationAlg.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>所有分类算法的基类</summary>
// ***********************************************************************
#pragma once
#include <string>

using namespace std;

/// <summary>
/// Class ClassificationAlg.
/// </summary>
class ClassificationAlg
{
public:
    ClassificationAlg( void ) {};
    ~ClassificationAlg( void ) {};
    
    /// <summary>
    /// Runs the alg.
    /// </summary>
    /// <param name="srcData">The source data.</param>
    /// <param name="roiFileName">Name of the roi file.</param>
    /// <param name="bandCount">The band count.</param>
    /// <param name="modelFileName">Name of the model file.</param>
    /// <returns>float.</returns>
    virtual float* runAlg( float** srcData ) = 0;
};

