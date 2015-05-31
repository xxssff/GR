#include "GRMatrices.h"
#include <iostream>
#include <fstream>
#include <string>

#include "gdal_priv.h"

namespace GR
{

namespace math
{

GRMatrices::GRMatrices()
{
}


GRMatrices::~GRMatrices()
{
}

/// <summary>
/// Check if the value is NaN.
/// </summary>
/// <param name="var">The variable.</param>
/// <returns>bool.</returns>
bool custom_isnan( double var )
{
    volatile double d = var;
    return d != d;
}

/// <summary>
/// Creates the matrix.
/// </summary>
/// <param name="m">The row number.</param>
/// <param name="n">The column number.</param>
/// <returns>Matrix * . an 0 matrix.</returns>
Matrix* GRMatrices::createMatrix( int m, int n ) throw( GRMatriceException )
{
    // create matrix m rows by n columns
    if ( m < 1 | n < 1 )
    {
        throw GRMatriceException( "Sizes of m and n must be at least 1." );
    }
    Matrix* matrix = new Matrix();
    matrix->m = m;
    matrix->n = n;
    matrix->matrix = new double[m * n];

    int length = m * n;

    for ( int i = 0; i < length; i++ )
    {
        matrix->matrix[i] = 0;
    }
    return matrix;
}

/// <summary>
/// Creates the matrix.
/// </summary>
/// <param name="matrix">The matrix, just to provide row and column numbers.</param>
/// <returns>Matrix * . an 0 matrix.</returns>
Matrix* GRMatrices::createMatrix( Matrix* matrix ) throw( GRMatriceException )
{
    if( matrix == NULL )
    {
        throw GRMatriceException( "The matrix to be copied is NULL." );
    }

    Matrix *newMatrix = new Matrix();
    newMatrix->m = matrix->m;
    newMatrix->n = matrix->n;
    newMatrix->matrix = new double[matrix->m * matrix->n];

    int length = newMatrix->m * newMatrix->n;

    for( int i = 0; i < length; i++ )
    {
        newMatrix->matrix[i] = 0;
    }

    return newMatrix;
}

/// <summary>
/// Copies the matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::copyMatrix( Matrix* matrix ) throw( GRMatriceException )
{
    if ( matrix == NULL )
    {
        throw GRMatriceException( "The matrix to be copied is NULL." );
    }

    Matrix* newMatrix = new Matrix();
    newMatrix->m = matrix->m;
    newMatrix->n = matrix->n;
    newMatrix->matrix = new double[matrix->m * matrix->n];

    int numPTS = matrix->m * matrix->n;

    for ( int i = 0; i < numPTS; i++ )
    {
        newMatrix->matrix[i] = matrix->matrix[i];
    }
    return newMatrix;
}

/// <summary>
/// Frees the matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
void GRMatrices::freeMatrix( Matrix* matrix )
{
    if( matrix != NULL )
    {
        if( matrix->matrix != NULL )
        {
            delete matrix->matrix;
        }
        delete matrix;
    }
}

/// <summary>
/// Sets the matrix values to a single value.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="val">The value.</param>
void GRMatrices::setValues( Matrix* matrix, double val ) throw( GRMatriceException )
{
    int totalElements = matrix->m * matrix->n;
    for( int i = 0; i < totalElements; i++ )
    {
        matrix->matrix[i] = val;
    }
}

/// <summary>
/// Calculate the determinant of the matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <returns>double  .</returns>
double GRMatrices::determinant( Matrix *matrix ) throw( GRMatriceException )
{
    double sum = 0;
    if ( matrix->m != matrix->n )
    {
        throw GRMatriceException( "To calculate a determinant the matrix needs to be symatical." );
    }

    if ( matrix->m == 2 )
    {
        sum = ( matrix->matrix[0] * matrix->matrix[3] ) - ( matrix->matrix[1] * matrix->matrix[2] );
    }
    else
    {
        Matrix* tempMatrix = NULL;
        double value = 0;
        int index = 0;
        for ( int i = 0; i < matrix->m; i++ )
        {
            index = 0;
            tempMatrix = this->createMatrix( ( matrix->m - 1 ), ( matrix->n - 1 ) );

            // populate new matrix
            for ( int m = 1; m < matrix->m; m++ )
            {
                for ( int n = 0; n < matrix->n; n++ )
                {
                    if ( i == n ) { continue;}
                    tempMatrix->matrix[index] = matrix->matrix[m * matrix->m + n];
                    index++;
                }
            }
            // Calculate the determinant of the new matrix
            value = this->determinant( tempMatrix );

            // add to sum
            sum = sum + ( pow( -1.0, i ) * value * matrix->matrix[i] );

            this->freeMatrix( tempMatrix );
        }
    }

    return sum;
}

/// <summary>
/// Cofactorses the specified matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::cofactors( Matrix *matrix ) throw( GRMatriceException )
{
    if ( matrix->m != matrix->n )
    {
        throw GRMatriceException( "To calculate a determinant the matrix needs to be symatical." );
    }

    Matrix* newMatrix = NULL;
    newMatrix = this->createMatrix( matrix->m, matrix->n );

    int index = 0;
    Matrix* tempMatrix = this->createMatrix( matrix->m - 1, matrix->n - 1 );
    for ( int i = 0; i < matrix->m; i++ )
    {
        for ( int j = 0; j < matrix->n; j++ )
        {
            index = 0;
            for ( int m = 0; m < matrix->m; m++ )
            {
                if( i == m ) { continue; }
                for ( int n = 0; n < matrix->n; n++ )
                {
                    if( j == n ) { continue; }
                    tempMatrix->matrix[index] = matrix->matrix[n * matrix->m + n];
                    index++;
                }
            }
            newMatrix->matrix[i * matrix->m + j] = ( pow( -1.0, ( ( i * matrix->n ) + j ) ) ) * this->determinant( tempMatrix );
        }
    }
    this->freeMatrix( tempMatrix );
    return newMatrix;

}

/// <summary>
/// Transposes the specified matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::transpose( Matrix *matrix ) throw( GRMatriceException )
{
    Matrix *newMatrix = NULL;
    newMatrix = this->createMatrix( matrix->n, matrix->m );
    for( int i = 0; i < matrix->m; i++ )
    {
        for( int j = 0; j < matrix->n; j++ )
        {
            newMatrix->matrix[i + ( j * matrix->m )] = matrix->matrix[( i * matrix->m ) + j];
        }
    }
    return newMatrix;
}

/// <summary>
/// Multiples a single value.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="multiple">The multiple value.</param>
void GRMatrices::multipleSingle( Matrix *matrix, double multiple ) throw( GRMatriceException )
{
    int numElements = matrix->m * matrix->n;
    for ( int i = 0; i < numElements; i++ )
    {
        matrix->matrix[i] = matrix->matrix[i] * multiple;
    }
}

/// <summary>
/// Multiplications of two matrices.
/// </summary>
/// <param name="matrixA">The matrix A.</param>
/// <param name="matrixB">The matrix B.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::multiplication( Matrix *matrixA, Matrix *matrixB ) throw( GRMatriceException )
{
    Matrix* matrix1 = NULL;
    Matrix* matrix2 = NULL;
    if ( matrixA->m == matrixB->n )
    {
        matrix1 = matrixA;
        matrix2 = matrixB;
    }
    if ( matrixA->n == matrixB->m )
    {
        matrix1 = matrixB;
        matrix2 = matrixA;
    }
    else
    {
        throw GRMatriceException( "Multipication required the number of columns to match the number of rows." );
    }

    Matrix* newMatrix = this->createMatrix( matrix2->m, matrix1->n );
    double value = 0;
    int row = 0;
    int col = 0;
    int index = 0;
    for ( int i = 0; i < matrix1->n; i++ )
    {
        for ( int j = 0; j < matrix2->m; j++ )
        {
            value = 0;
            for ( int m = 0; m < matrix1->m; m++ )
            {
                row = i * matrix1->m + m;
                col = m * matrix2->m + j;
                value += matrix1->matrix[row] * matrix2->matrix[col];
            }
            newMatrix->matrix[index] = value;
            index++;
        }
    }
    return newMatrix;
}

/// <summary>
/// Prints the matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
void GRMatrices::printMatrix( Matrix *matrix )
{
    int index = 0;
    for ( int i = 0; i < matrix->m; i++ )
    {
        for ( int j = 0; j < matrix->n; j++ )
        {
            std::cout << matrix->matrix[index++] << " ";
        }
        std::cout << std::endl;
    }
}

/// <summary>
/// Saves the matrix to grid text.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="filepath">The filepath.</param>
void GRMatrices::saveMatrix2GridTxt( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException )
{
    std::string outputFilename = filepath + std::string( ".gmtxt" );
    std::ofstream outTxtFile;
    outTxtFile.open( outputFilename.c_str(), std::ios::out | std::ios::trunc );
    if( outTxtFile.is_open() )
    {
        outTxtFile << "m=" << matrix->m << std::endl;
        outTxtFile << "n=" << matrix->n << std::endl;

        int totalElements = matrix->m * matrix->n;
        int lastElement = totalElements - 1;
        for( int i = 0; i < totalElements; i++ )
        {
            if( ( i + 1 ) %  matrix->n == 0 )
            {
                outTxtFile << matrix->matrix[i] << std::endl;
            }
            else if( i == lastElement )
            {
                outTxtFile << matrix->matrix[i];
            }
            else
            {
                outTxtFile << matrix->matrix[i] << ",";
            }
        }
        outTxtFile.flush();
        outTxtFile.close();
    }
    else
    {
        throw GRMatriceException( "Could not open text file." );
    }

}

/// <summary>
/// Saves the matrix to CSV file.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="filepath">The filepath.</param>
void GRMatrices::saveMatrix2CSV( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException )
{
    std::string outputFilename = filepath + std::string( ".csv" );
    std::ofstream outTxtFile;
    outTxtFile.open( outputFilename.c_str(), std::ios::out | std::ios::trunc );

    if( outTxtFile.is_open() )
    {
        int totalElements = matrix->m * matrix->n;
        for( int i = 0; i < totalElements; i++ )
        {
            if( i == 0 ) // Don't start firstline with comma or newline
            {
                outTxtFile  << matrix->matrix[i];
            }
            else if( ( i %  matrix->n == 0 ) ) // If start of line, begin with a new line.
            {
                //outTxtFile << std::endl;
                outTxtFile  << std::endl << matrix->matrix[i];
            }
            else // Otherwise, begin with a comma
            {
                outTxtFile  << "," << matrix->matrix[i];
            }
        }
        outTxtFile.flush();
        outTxtFile.close();
    }
    else
    {
        throw GRMatriceException( "Could not open text file." );
    }
}

/// <summary>
/// Saves the matrix to txt file.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="filepath">The filepath.</param>
void GRMatrices::saveMatrix2txt( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException )
{
    std::string outputFilename = filepath + std::string( ".txt" );
    std::ofstream outTxtFile;
    outTxtFile.open( outputFilename.c_str(), std::ios::out | std::ios::trunc );

    if( outTxtFile.is_open() )
    {
        int totalElements = matrix->m * matrix->n;
        for( int i = 0; i < totalElements; i++ )
        {
            if( i == 0 ) // Don't start firstline with comma or newline
            {
                outTxtFile  << matrix->matrix[i];
            }
            else if( ( i %  matrix->n == 0 ) ) // If start of line, begin with a new line.
            {
                //outTxtFile << std::endl;
                outTxtFile  << std::endl << matrix->matrix[i];
            }
            else // Otherwise, begin with a comma
            {
                outTxtFile  << "," << matrix->matrix[i];
            }
        }
        outTxtFile.flush();
        outTxtFile.close();
    }
    else
    {
        throw GRMatriceException( "Could not open text file." );
    }
}

/// <summary>
/// Saves the matrix to txt file with options.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="filepath">The filepath.</param>
/// <param name="outtxt">The outtxt.</param>
void GRMatrices::saveMatrix2txtOptions( Matrix *matrix, std::string filepath, outTXTform outtxt ) throw( GRMatriceException, GROutputStreamException )
{
    if( outtxt == mtxt )
    {
        this->saveMatrix2txt( matrix, filepath );
    }
    else if( outtxt == gtxt )
    {
        this->saveMatrix2GridTxt( matrix, filepath );
    }
    else if( outtxt == csv )
    {
        this->saveMatrix2CSV( matrix, filepath );
    }
    else
    {
        throw GRMatriceException( "Txt format not recognised!" );
    }
}

/// <summary>
/// Saves the matrix to binary file.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="filepath">The filepath.</param>
void GRMatrices::saveMatrix2Binary( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException )
{
    std::ofstream matrixOutput;
    std::string matrixFilepath = filepath + std::string( ".mtx" );
    matrixOutput.open( matrixFilepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary );
    if( !matrixOutput.is_open() )
    {
        throw GRMatriceException( "Could not open output stream for Matrix output." );
    }

    matrixOutput.write( ( char * ) matrix->m, 4 );
    matrixOutput.write( ( char * ) matrix->n, 4 );

    int matrixLength = matrix->m * matrix->n;
    for( int i = 0; i < matrixLength; i++ )
    {
        matrixOutput.write( ( char * ) &matrix->matrix[i], 4 );
    }

    matrixOutput.flush();
    matrixOutput.close();
}

/// <summary>
/// Reads the matrix from text. This has some problem.
/// </summary>
/// <param name="filepath">The filepath.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::readMatrixFromTxt( std::string filepath ) throw( GRMatriceException, GRInputStreamException )
{
    Matrix *matrix = new Matrix();
    std::ifstream inputMatrix;
    inputMatrix.open( filepath.c_str() );
    if( !inputMatrix.is_open() )
    {
        throw GRMatriceException( "Could not open input text file." );
    }
    else
    {
        std::string strLine;
        std::string word;
        int number;
        float value;
        int lineCounter = 0;
        inputMatrix.seekg( std::ios_base::beg );

        while( !inputMatrix.eof() )
        {
            getline( inputMatrix, strLine, '\n' );
            if( strLine.length() > 0 )
            {
                if( lineCounter == 0 )
                {
                    // m
                    word = strLine.substr( 2 );
                    number = strtol( word.c_str(), NULL, 10 );
                    matrix->m = number;
                }
                else if( lineCounter == 1 )
                {
                    // n
                    word = strLine.substr( 2 );
                    number = strtol( word.c_str(), NULL, 10 );
                    matrix->n = number;
                }
                else if( lineCounter >= 2 )
                {
                    // data
                    int dataCounter = 0;
                    int start = 0;
                    int lineLength = strLine.length();
                    int numDataPoints = matrix->n * matrix->m;
                    matrix->matrix = new double[numDataPoints];
                    for( int i = 0; i < lineLength; i++ )
                    {
                        if( strLine.at( i ) == ',' )
                        {
                            word = strLine.substr( start, i - start );
                            value = strtod( word.c_str(), NULL );
                            if( custom_isnan( value ) )
                            {
                                value = 0;
                            }
                            matrix->matrix[dataCounter] = value;
                            dataCounter++;

                            start = start + i - start + 1;
                        }

                        if( dataCounter >= numDataPoints )
                        {
                            throw GRInputStreamException( "Too many data values, compared to header." );
                        }
                    }
                    word = strLine.substr( start );
                    value = strtod( word.c_str(), NULL );
                    matrix->matrix[dataCounter] = value;
                    dataCounter++;

                    if( dataCounter != matrix->n )
                    {
                        break;
                    }

                }
                else
                {
                    break;
                }
            }
            lineCounter++;
        }

        if( lineCounter < 3 )
        {
            throw GRInputStreamException( "A complete matrix has not been reconstructed." );
        }
        inputMatrix.close();
    }
    return matrix;
}

/// <summary>
/// Reads the matrix from grid text.
/// </summary>
/// <param name="filepath">The filepath.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::readMatrixFromGridTxt( std::string filepath ) throw( GRMatriceException, GRInputStreamException )
{
    Matrix *matrix = new Matrix();
    std::ifstream inputMatrix;
    inputMatrix.open( filepath.c_str() );
    if( !inputMatrix.is_open() )
    {
        throw GRInputStreamException( "Could not open input text file." );
    }
    else
    {
        std::string strLine;
        std::string wholeline;
        std::string word;
        int number;
        float value;
        int lineCounter = 0;
        bool first = true;
        inputMatrix.seekg( std::ios_base::beg );
        while( !inputMatrix.eof() )
        {
            getline( inputMatrix, strLine, '\n' );
            if( strLine.length() > 0 )
            {
                if( lineCounter == 0 )
                {
                    // m
                    word = strLine.substr( 2 );
                    number = strtol( word.c_str(), NULL, 10 );
                    matrix->m = number;
                    //cout << "columns = " << number << std::endl;
                }
                else if( lineCounter == 1 )
                {
                    // n
                    word = strLine.substr( 2 );
                    number = strtol( word.c_str(), NULL, 10 );
                    matrix->n = number;
                    //cout << "rows = " << number << std::endl;
                }
                else
                {
                    if( first )
                    {
                        wholeline = strLine;
                        first = false;
                    }
                    else
                    {
                        wholeline = wholeline + std::string( "," ) + strLine;
                    }
                }
                lineCounter++;
            }
        }
        inputMatrix.close();

        // data
        int dataCounter = 0;
        int start = 0;
        int lineLength = wholeline.length(); ;
        int numDataPoints = matrix->m * matrix->n;
        matrix->matrix = new double[numDataPoints];

        for( int i = 0; i < lineLength; i++ )
        {
            if( wholeline.at( i ) == ',' )
            {
                word = wholeline.substr( start, i - start );
                value = strtod( word.c_str(), NULL );
                matrix->matrix[dataCounter] = value;
                dataCounter++;

                start = start + i - start + 1;
            }

            if( dataCounter >= numDataPoints )
            {
                throw GRInputStreamException( "Too many data values, compared to header." );
            }
        }

        word = wholeline.substr( start );
        value = strtod( word.c_str(), NULL );
        matrix->matrix[dataCounter] = value;
        dataCounter++;

        if( dataCounter != ( matrix->m * matrix->n ) )
        {
            throw GRInputStreamException( "An incorrect number of data points were read in." );
        }
    }
    return matrix;
}

/// <summary>
/// Reads the matrix from binary.
/// </summary>
/// <param name="filepath">The filepath.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::readMatrixFromBinary( std::string filepath ) throw( GRMatriceException, GRInputStreamException )
{
    Matrix *matrix = new Matrix();
    std::string matrixFilepath = filepath + std::string( ".mtx" );
    std::ifstream matrixInput;
    matrixInput.open( matrixFilepath.c_str(), std::ios::in | std::ios::binary );
    if( !matrixInput.is_open() )
    {
        throw GRInputStreamException( "Could not open matrix binary file." );
    }

    matrixInput.seekg ( 0, std::ios::end );
    long end = matrixInput.tellg();
    matrixInput.seekg ( 0, std::ios::beg );
    int matrixSizeFile = ( end / 16 ) - 2;

    matrixInput.read( ( char * ) &matrix->m, 4 );
    matrixInput.read( ( char * ) &matrix->n, 4 );

    int matrixSize = matrix->m * matrix->n;
    if( matrixSizeFile != matrixSize )
    {
        throw GRInputStreamException( "The file size and header differ on the number of points." );
    }

    matrix->matrix = new double[matrixSize];

    for( int i = 0; i < matrixSize; i++ )
    {
        matrixInput.read( ( char * ) &matrix->matrix[i], 4 );
    }

    matrixInput.close();
    return matrix;
}

/// <summary>
/// Exports the matrix to image.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="filepath">The filepath.</param>
void GRMatrices::exportAsImage( Matrix *matrix, std::string filepath ) throw( GRMatriceException )
{
    GDALAllRegister();
    GDALDataset *outputImageDS = NULL;
    GDALRasterBand *outputRasterBand = NULL;
    GDALDriver *gdalDriver = NULL;
    float *row;

    try
    {
        // Create new Image
        gdalDriver = GetGDALDriverManager()->GetDriverByName( "ENVI" );
        if( gdalDriver == NULL )
        {
            throw GRMatriceException( "Image output error: ENVI driver does not exists.." );
        }
        outputImageDS = gdalDriver->Create( filepath.c_str(), matrix->m, matrix->n, 1, GDT_Float32, gdalDriver->GetMetadata() );
        outputRasterBand = outputImageDS->GetRasterBand( 1 );

        row = ( float * ) CPLMalloc( sizeof( float ) * matrix->m );

        for( int i = 0; i < matrix->n; i++ )
        {
            for( int j = 0; j < matrix->m; j++ )
            {
                row[j] = ( float ) matrix->matrix[( i * matrix->m ) + j];
            }

            outputRasterBand->RasterIO( GF_Write, 0, i, matrix->m, 1, row, matrix->m, 1, GDT_Float32, 0, 0 );
        }


        delete row;
        GDALClose( outputImageDS );
    }
    catch( GRMatriceException e )
    {
        throw e;
    }
}

/// <summary>
/// Normaliseds the matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::normalisedMatrix( Matrix *matrix, double min, double max ) throw( GRMatriceException )
{
    double matrixMIN = 0;
    double matrixMAX = 0;
    double matrixDIFF = 0;
    double inDIFF = 0;
    bool first = true;
    int size = matrix->m * matrix->n;

    for( int i = 0; i < size; i++ )
    {
        if( first )
        {
            matrixMIN = matrix->matrix[i];
            matrixMAX = matrix->matrix[i];
            first = false;
        }
        else
        {
            if( matrix->matrix[i] > matrixMAX )
            {
                matrixMAX = matrix->matrix[i];
            }
            else if( matrix->matrix[i] < matrixMIN )
            {
                matrixMIN = matrix->matrix[i];
            }
        }
    }

    inDIFF = max - min;
    matrixDIFF = matrixMAX - matrixMIN;

    Matrix *outMatrix = this->createMatrix( matrix->m, matrix->n );
    double norm = 0;

    for( int i = 0; i < size; i++ )
    {
        norm = ( matrix->matrix[i] - matrixMIN ) / matrixDIFF;
        outMatrix->matrix[i] = ( norm * inDIFF ) + min;
    }

    return outMatrix;
}

/// <summary>
/// Normaliseds the columns matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::normalisedColumnsMatrix( Matrix *matrix ) throw( GRMatriceException )
{
    Matrix *outMatrix = this->createMatrix( matrix );

    float *normalisingVals = new float[matrix->n];
    for( int i = 0; i < matrix->n; ++i )
    {
        normalisingVals[i] = 0;
        for( int j = 0; j < matrix->m; ++j )
        {
            normalisingVals[i] += ( matrix->matrix[( j * matrix->n ) + i] * matrix->matrix[( j * matrix->m ) + i] );
        }

        normalisingVals[i] = sqrt( normalisingVals[i] );
    }

    for( int i = 0; i < matrix->n; ++i )
    {
        for( int j = 0; j < matrix->m; ++j )
        {
            //cout << matrix->matrix[(j*matrix->m)+i] << " / " << normalisingVals[i] << " = " << matrix->matrix[(j*matrix->m)+i]/normalisingVals[i] << std::endl;
            outMatrix->matrix[( j * matrix->n ) + i] = matrix->matrix[( j * matrix->n ) + i] / normalisingVals[i];
        }
    }

    delete[] normalisingVals;

    return outMatrix;
}

/// <summary>
/// Duplicates the matrix.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="xDuplications">The executable duplications.</param>
/// <param name="yDuplications">The asynchronous duplications.</param>
/// <returns>Matrix *  .</returns>
Matrix* GRMatrices::duplicateMatrix( Matrix *matrix, int xDuplications, int yDuplications ) throw( GRMatriceException )
{
    int newM = matrix->m * xDuplications;
    int newN = matrix->n * yDuplications;

    Matrix *outMatrix = this->createMatrix( newM, newN );

    int column = 0;
    int row = 0;
    int width = matrix->n;
    int height = matrix->m;
    int length = ( height * xDuplications ) * width;

    int inCounter = 0;
    int outCounter = 0;
    int xDupCount = 0;

    for( int n = 0; n < yDuplications; n++ )
    {
        inCounter = 0;
        xDupCount = 0;
        outCounter = n * length;

        for( int i = 0; i < length; i++ )
        {
            outMatrix->matrix[outCounter++] = matrix->matrix[inCounter++];

            column++;
            if( column == width )
            {
                xDupCount++;

                if( xDupCount < xDuplications )
                {
                    inCounter = inCounter - width;
                }
                else
                {
                    row++;
                    xDupCount = 0;
                }
                column = 0;
            }
        }
    }

    return outMatrix;
}









} // namespace math
} // namespace GR