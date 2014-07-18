// ***********************************************************************
// Assembly         : ImgTest
// Author           : Jacory
// Created          : 07-17-2014
//
// Last Modified By : Jacory
// Last Modified On : 07-17-2014
// ***********************************************************************
// <copyright file="DistanceAlgorithmClient.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>作为算法的调用接口，UI通过它调用距离算法。</summary>
// ***********************************************************************
#ifndef DISTANCEALGORITHMCLIENT_H
#define DISTANCEALGORITHMCLIENT_H

#include <QObject>

class MapCanvas;
class GDALDataset;
class DistanceAlg;

/// <summary>
/// Class DistanceAlgorithmClient.
/// </summary>
class DistanceAlgorithmClient : public QObject
{
    Q_OBJECT
    
public:
    DistanceAlgorithmClient( QObject *parent );
    ~DistanceAlgorithmClient();
    DistanceAlgorithmClient( MapCanvas* map, QString algName );
    
    void SetMapCavans( MapCanvas* map );
    void SetDistanceAlg( DistanceAlg* alg );
    MapCanvas* GetMapCanvas();
    
public slots:
    void RunDisAlg( GDALDataset* poDataset );
    
private:
    /// <summary>
    /// 为了算法的结果显示，需要MapCanvas的指针
    /// </summary>
    MapCanvas *myMap;
    /// <summary>
    /// 距离算法的抽象类对象
    /// </summary>
    DistanceAlg *disAlg;
};

#endif // DISTANCEALGORITHMCLIENT_H
