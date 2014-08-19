#include "SVMClassification.h"
#include <fstream>

/// <summary>
/// Initializes a new instance of the <see cref="SVMClassification"/> class.
/// </summary>
SVMClassification::SVMClassification( void )
{
    svmModel = NULL;
    roiFile = "";
    modelFile = "";
    modelFileSave = "";
    bandCount = 0;
    pixelCount = 0;
}


/// <summary>
/// Finalizes an instance of the <see cref="SVMClassification"/> class.
/// </summary>
SVMClassification::~SVMClassification( void )
{
}

/// <summary>
/// Trains the model.If the model file exist, load the model, otherwise, train the model
/// </summary>
/// <param name="roiFilename">The roi filename.</param>
/// <param name="modelFileName">Name of the model file.</param>
void SVMClassification::TrainModel()
{
    if ( roiFile == "" )
    {
        return;
    }
    
    fstream in( modelFile );
    if ( in.fail() )
    {
        initialSVMPro();
        const char *error_msg;
        error_msg = svm_check_parameter( &svmPro, &svmPara );
        if ( error_msg )
        {
            return;
        }
        svmModel = svm_train( &svmPro, &svmPara );
    }
    else
    {
        svmModel = svm_load_model( modelFile.c_str() );
    }
}

/// <summary>
/// initial the SVM problem , construct the dataset that SVM uses
/// </summary>
/// <param name="fileName">Name of the file.</param>
void SVMClassification::initialSVMPro()
{
    int dataCount = 0;// the total count of samples
    int nodeIndex = 0;
    svm_node **node = new svm_node *[33669];
    
    ifstream in( roiFile.c_str() );
    if ( in.fail() )
    {
        return;
    }
    
    string line = "";
    getline( in, line );// ignore the first line
    getline( in, line );
    classCount = atoi( &line[line.size() - 1] );
    
    while( getline( in, line ) )
    {
        // ignore the empty lines
        if ( line == ";" || line == "" )
        {
            continue;
        }
        vector<string> tempLine = split( line, ":" );
        // store the names and num of each ROI
        if ( tempLine[0] == "; ROI name" )
        {
            string name = tempLine[1];
            roiName.push_back( name );
            getline( in, line );
            getline( in, line );
            tempLine = split( line, ":" );
            roiMap[name] = atoi( tempLine[1].c_str() );
        }
        // read the data line
        if ( tempLine.size() == 1 ) // this means to start read data
        {
            tempLine = split( line, " " );
            if ( tempLine[0] == ";" )
            {
                getline( in, line ); // ingore the head of the data table
            }
            tempLine = split( line, " " );
            
            
            svm_node *xSpace = new svm_node[5];
            for ( int i = 0; i < 5; i++ )
            {
                if ( i != 4 )
                {
                    xSpace[i].index = i + 1;
                    xSpace[i].value = atof( tempLine[tempLine.size() - 4 + i].c_str() );
                }
                else
                {
                    xSpace[i].index = -1;
                }
            }
            
            node[nodeIndex++] = xSpace;
        }
    }
    
    double *y1 = new double[nodeIndex];
    for ( int i = 0; i < nodeIndex; i++ )
    {
        if ( i < 7931 )
        {
            y1[i] = 1;
        }
        if ( i >= 7931 && i < 7931 + 17418 )
        {
            y1[i] = 2;
        }
        if ( i >= 7931 + 17418 && i < 7931 + 17418 + 3248 )
        {
            y1[i] = 3;
        }
        if ( i >= 7931 + 17418 + 3248 && i < 7931 + 17418 + 3248 + 4039 )
        {
            y1[i] = 4;
        }
        if ( i >= 7931 + 17418 + 3248 + 4039 &&  i < 7931 + 17418 + 3248 + 4039 + 1033 )
        {
            y1[i] = 5;
        }
    }
    
    Scale( node );
    svmPro.l = nodeIndex;
    svmPro.x = node;
    svmPro.y = y1;
}

/// <summary>
/// Runs the alg.
/// </summary>
/// <param name="srcData">The source data.</param>
/// <param name="roiFileName">Name of the roi file.</param>
/// <param name="bandCount">The band count.</param>
/// <param name="modelFileName">Name of the model file.</param>
/// <returns>float.</returns>
float* SVMClassification::runAlg( float** srcData )
{
    if ( svmModel == NULL || bandCount == 0 || pixelCount == 0 || srcData == NULL )
    {
        TrainModel();
    }
    
    float* resultData = new float[pixelCount];// create the resultData array, size is width*height of image
    svm_node *xSpace = new svm_node[bandCount + 1];
    for ( int n = 0; n < pixelCount; n++ )
    {
        for ( int i = 0; i < bandCount + 1; i++ )
        {
            if ( i != bandCount )
            {
                xSpace[i].index = i + 1;
                xSpace[i].value = srcData[n][i];
            }
            else
            {
                xSpace[i].index = -1;
            }
        }
        
        resultData[n] = svm_predict( svmModel, xSpace );
    }
    return resultData;
}

/// <summary>
/// Sets the roiFile.
/// </summary>
/// <param name="rFile">The r file.</param>
void SVMClassification::SetRoiFile( const string rFile )
{
    this->roiFile = rFile;
}

/// <summary>
/// Sets the modelFile.
/// </summary>
/// <param name="mFile">The m file.</param>
void SVMClassification::SetModelFile( const string mFile )
{
    this->modelFile = mFile;
}

/// <summary>
/// Sets the modelFileSave.
/// </summary>
/// <param name="msFile">The modelFileSave.</param>
void SVMClassification::SetModelFileSave( const string msFile )
{
    this->modelFileSave = msFile;
}

/// <summary>
/// Sets the bandCount.
/// </summary>
/// <param name="count">The count.</param>
void SVMClassification::SetBandCount( int count )
{
    this->bandCount = count;
}

/// <summary>
/// Sets the pixelCount.
/// </summary>
/// <param name="count">The count.</param>
void SVMClassification::SetPixelCount( int count )
{
    this->pixelCount = count;
}

/// <summary>
/// Gets the roiFile.
/// </summary>
/// <returns>string.</returns>
string SVMClassification::GetRoiFile()
{
    return roiFile;
}

/// <summary>
/// Gets the modelFile.
/// </summary>
/// <returns>string.</returns>
string SVMClassification::GetModelFile()
{
    return modelFile;
}

/// <summary>
/// Gets the modelFile save.
/// </summary>
/// <returns>string.</returns>
string SVMClassification::GetModelFileSave()
{
    return modelFileSave;
}

/// <summary>
/// Gets the bandCount.
/// </summary>
/// <returns>int.</returns>
int SVMClassification::GetBandCount()
{
    return bandCount;
}

/// <summary>
/// Gets the pixelCount.
/// </summary>
/// <returns>int.</returns>
int SVMClassification::GetPixelCount()
{
    return pixelCount;
}

/// <summary>
/// Saves the model.
/// </summary>
void SVMClassification::SaveModel()
{
    if ( modelFileSave == "" )
    {
        return;
    }
    svm_save_model( modelFileSave.c_str(), svmModel );
}

/// <summary>
/// Sets the parameter.
/// </summary>
/// <param name="para">The para.</param>
void SVMClassification::SetParameter( svm_parameter &para )
{
    svmPara = para;
}


/// <summary>
/// Scales the specified source data.
/// </summary>
/// <param name="srcData">The source data.</param>
void SVMClassification::Scale( svm_node** srcData )
{
    double max = 0;
    double min = 0;
    for ( int k = 0; k < bandCount; k++ )
    {
        for ( int i = 0; i < 33669; i++ )
        {
            if ( min >= srcData[i][k].value )
            {
                min = srcData[i][k].value;
            }
            if ( max <= srcData[i][k].value )
            {
                max = srcData[i][k].value;
            }
        }
        
        for ( int i = 0; i < 33669; i++ )
        {
            srcData[i][k].value = ( srcData[i][k].value - min ) * 1.0 / ( max - min );
            if ( srcData[i][k].value >= max )
            {
                srcData[i][k].value = 1.0;
            }
            if ( srcData[i][k].value <= min )
            {
                srcData[i][k].value = 0.0;
            }
        }
    }
}

/// <summary>
/// Splits the specified string.
/// </summary>
/// <param name="str">The string.</param>
/// <param name="pattern">The pattern.</param>
/// <returns>std.vector{_Ty, _Ax}.</returns>
vector<string> SVMClassification::split( std::string str, std::string pattern )
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size = str.size();
    
    for ( int i = 0; i < size; i++ )
    {
        pos = str.find ( pattern, i );
        if ( pos < size )
        {
            std::string s = str.substr ( i, pos - i );
            result.push_back ( s );
            i = pos + pattern.size() - 1;
        }
    }
    
    vector<string>::iterator iter;
    for ( iter = result.begin(); iter != result.end(); )
    {
        if ( *iter == " " || *iter == "" )
        {
            iter = result.erase( iter );
        }
        else
        {
            iter++;
        }
    }
    
    return result;
}