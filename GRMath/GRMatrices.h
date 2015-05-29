#pragma once

#include "Matrix.h"
#include "GRMatriceException.h"
#include <..\GRCommons\GROutputStreamException.h>

namespace GR
{
namespace math
{

struct Matrix
{
    double *matrix;
    int m; // row
    int n; // column
};

enum outTXTform
{
    mtxt,
    gtxt,
    csv
};

class GRMatrices
{
public:
    GRMatrices();
    ~GRMatrices();

    Matrix* createMatrix( int n, int m ) throw( GRMatriceException );
    Matrix* createMatrix( Matrix* matrix ) throw( GRMatriceException );

    Matrix* copyMatrix( Matrix* matrix ) throw( GRMatriceException );

    void freeMatrix( Matrix* matrix );

    void setValues( Matrix* matrix, double val ) throw( GRMatriceException );

    double determinant( Matrix *matrix ) throw( GRMatriceException );
    Matrix* cofactors( Matrix *matrix ) throw( GRMatriceException );
    Matrix* transpose( Matrix *matrix ) throw( GRMatriceException );

    void printMatrix( Matrix *matrix );

    // import matrix
    Matrix* readMatrixFromTxt( std::string filepath ) throw( GRMatriceException,/*RSGISInputStreamException*/ );
    Matrix* readMatrixFromGridTxt( std::string filepath ) throw( GRMatriceException, /*RSGISInputStreamException*/ );
    Matrix* readMatrixFromBinary( std::string filepath ) throw( GRMatriceException, /*RSGISInputStreamException*/ );

    // export matrix
    void saveMatrix2GridTxt( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException );
    void saveMatrix2CSV( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException );
    void saveMatrix2txt( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException );
    void saveMatrix2txtOptions( Matrix *matrix, std::string filepath, outTXTform outtxt ) throw( GRMatriceException, GROutputStreamException );
    void saveMatrix2Binary( Matrix *matrix, std::string filepath ) throw( GRMatriceException, GROutputStreamException );

    void exportAsImage( Matrix *matrix, std::string filepath ) throw( GRMatriceException );

    // matrix calculation
    void multipleSingle( Matrix *matrix, double multiple ) throw( GRMatriceException );
    Matrix* multiplication( Matrix *matrixA, Matrix *matrixB ) throw( GRMatriceException );
    void calcEigenVectorValue( Matrix *matrix, Matrix *eigenvalues, Matrix *eigenvectors ) throw( GRMatriceException );
    Matrix* normalisedMatrix( Matrix *matrix, double min, double max ) throw( GRMatriceException );
    Matrix* normalisedColumnsMatrix( Matrix *matrix ) throw( GRMatriceException );

    Matrix* duplicateMatrix( Matrix *matrix, int xDuplications, int yDuplications ) throw( GRMatriceException );

};
}
}



