#pragma once

#include <string>
#include <vector>

namespace GR
{
namespace classifier
{


/**
   * ISODATA����ṹ��
   */
struct ClusterCentreISO
{
    std::string className;
    int classID;
    std::vector<double> data;
    std::vector<double> stddev;
    int numVals;
    bool split;
    double avgDist;
};


class __declspec( dllexport ) GRIsoDataClassifier
{
public:
    GRIsoDataClassifier();
    ~GRIsoDataClassifier();
public:
    // ���÷������
    inline void setClustersCnt( int minclustersCnt, int maxclustersCnt )
    {
        m_nMinClassesNumber = minclustersCnt;
        m_nMaxClassesNumber = maxclustersCnt;
        m_nClasserNumber = ( m_nMinClassesNumber + m_nMaxClassesNumber ) / 2;
    }

    inline void setThreshold( double threshold ) {m_dfChangeThreshold = threshold;}
    inline void setMaxIter( int maxIter ) {m_nMaxIterations = maxIter;}
    inline void setMinPixelClass( int nValue ) {m_nMinPixels = nValue;}
    inline void setMaxClassStdv( double dValue ) {m_dfMaxClassStdv = dValue;}
    inline void setMinClassDistance( double dValue ) {m_dfMinClassDistance = dValue;}
    inline void setMaxMergePairs( int nValue ) {m_dfPropOverAvgDist = nValue;}
    inline void setInputFilename( std::string nValue ) {inputFilename = nValue;}
    inline void setOutputFilename( std::string nValue ) {outputFilename = nValue;}

    bool ParametersCheck();
    bool Execute();
private:
    const char* m_pszInFile;
    const char* m_pszOutFile;
    const char* m_pszFormat;

    int m_nMinClassesNumber;	//��С�������
    int m_nMaxClassesNumber;	//���������
    double m_dfChangeThreshold;
    int m_nMaxIterations ;	//����������
    int m_nMinPixels;		//�������С��Ԫ����
    double m_dfMaxClassStdv;
    double m_dfMinClassDistance;
    double m_dfPropOverAvgDist;

    double m_dfMaxStddev;
    double m_dfMaxDistance;

    std::vector<ClusterCentreISO*> *m_pvClusterCentres;
    int m_nClasserNumber;	//�������

    std::string inputFilename;
    std::string outputFilename;

};

}
}