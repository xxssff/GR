#include "GRClassifier.h"

#include <iostream>

namespace GR
{
namespace classifier
{


GRClassifier::GRClassifier( ClassData **trainingData, int numClasses ) throw( GRClassificationException )
{
    this->trainingData = trainingData;
    this->classCount = numClasses;
    this->variableCount = trainingData[0]->data->n;
}


GRClassifier::~GRClassifier()
{
}

int GRClassifier::getVariableCount()
{
    return variableCount;
}

void GRClassifier::printClassIDs()
{
    for ( int i = 0 ; i < classCount; i++ )
    {
        std::cout << "Class " << trainingData[i]->className << " has ID " << trainingData[i]->classID << std::endl;
    }
}



}
}