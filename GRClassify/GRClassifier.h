#pragma once


#include <string>
#include <vector>

#include "..\GRMath\GRMatrices.h"
#include "..\GRCommons\GRClassificationException.h"

namespace GR
{
namespace classifier
{

struct ClassData
{
    std::string className;
    int classID;
    GR::math::Matrix* data;
};

struct ClusterCentre
{
    std::string className;
    int classID;
    std::vector<double> *data;
    unsigned int numVals;
};

struct ClusterCentreISO
{
    std::string className;
    int classID;
    std::vector<double> *data;
    std::vector<double> *stddev;
    unsigned int numVals;
    bool split;
    double avgDist;
};

class __declspec( dllexport ) GRClassifier
{
public:
    GRClassifier( ClassData **trainingData, int numClasses ) throw( GRClassificationException );
    virtual ~GRClassifier();

    virtual int getClassID( float *variables, int numVars ) throw( GRClassificationException );
    virtual std::string getClassName( float* variables, int numVars ) throw( GRClassificationException );
    int getVariableCount();
    void printClassIDs();

protected:
    ClassData** trainingData;
    int classCount;
    int variableCount;

};

}




