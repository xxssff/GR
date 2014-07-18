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
// <summary>��Ϊ�㷨�ĵ��ýӿڣ�UIͨ�������þ����㷨��</summary>
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
    /// Ϊ���㷨�Ľ����ʾ����ҪMapCanvas��ָ��
    /// </summary>
    MapCanvas *myMap;
    /// <summary>
    /// �����㷨�ĳ��������
    /// </summary>
    DistanceAlg *disAlg;
};

#endif // DISTANCEALGORITHMCLIENT_H
