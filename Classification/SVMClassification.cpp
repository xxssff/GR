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
            //cout << nodeIndex << endl;
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
    
    svmPro.l = nodeIndex;
    svmPro.x = node;
    svmPro.y = y1;
}

/// <summary>
/// initial SVM parameters , this one should be configed, I don't know the default setting parameters
/// for remote sensing classification...
/// </summary>
void SVMClassification::initialParameter()
{
    //svmPara.svm_type = C_SVC;
    //svmPara.kernel_type = LINEAR;
    ////svmPara.degree = 3;
    //svmPara.gamma = 0.2;
    ////svmPara.coef0 = 0;
    //
    //svmPara.nu = 0.5;
    //svmPara.cache_size = 1;
    //svmPara.C = 1;
    //svmPara.eps = 1e-3;
    //svmPara.p = 0.1;
    //svmPara.shrinking = 1;
    //svmPara.nr_weight = 0;
    //svmPara.weight_label = NULL;
    //svmPara.weight = NULL;
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

void SVMClassification::SetRoiFile( const string rFile )
{
    this->roiFile = rFile;
}

void SVMClassification::SetModelFile( const string mFile )
{
    this->modelFile = mFile;
}

void SVMClassification::SetModelFileSave( const string msFile )
{
    this->modelFileSave = msFile;
}

void SVMClassification::SetBandCount( int count )
{
    this->bandCount = count;
}

void SVMClassification::SetPixelCount( int count )
{
    this->pixelCount = count;
}

string SVMClassification::GetRoiFile()
{
    return roiFile;
}

string SVMClassification::GetModelFile()
{
    return modelFile;
}

string SVMClassification::GetModelFileSave()
{
    return modelFileSave;
}

int SVMClassification::GetBandCount()
{
    return bandCount;
}

int SVMClassification::GetPixelCount()
{
    return pixelCount;
}

void SVMClassification::SaveModel()
{
    if ( modelFileSave == "" )
    {
        return;
    }
    svm_save_model( modelFileSave.c_str(), svmModel );
}

void SVMClassification::SetParameter( svm_parameter &para )
{
    svmPara = para;
}
