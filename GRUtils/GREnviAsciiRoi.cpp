#include "GREnviAsciiRoi.h"

#include "..\GRMath\GRMatrices.h"

#include "GRTextUtils.h"
#include "GRTextException.h"

#include <fstream>
#include <vector>
#include <iostream>

namespace GR
{
namespace utils
{

GREnviAsciiRoi::GREnviAsciiRoi( std::string file )
{
    this->inputfile = file;
    this->parsefile();
}

void GREnviAsciiRoi::parsefile() throw ( GR::GRInputStreamException )
{
    GR::math::GRMatrices matrixUtil;
    std::ifstream inputRoiFile;
    inputRoiFile.open( inputfile.c_str() );
    if ( !inputRoiFile.is_open() )
    {
        std::string msg = std::string( "Could not open input text file: " ) + inputfile;
        throw GR::GRInputStreamException( msg );
    }

    std::string strLine;
    GRTextUtils textUtil;
    int currentRoiIndex = 0;
    int headingLine = 0;
    int sampleCount = 0; // roi sample numbers
    int lineCounter = 0;
    int dataStart = 0;
    int dataindex = 0;

    inputRoiFile.seekg( std::ios_base::beg );
    std::vector<std::string>* tokens = new std::vector<std::string>;
    while( !inputRoiFile.eof() )
    {
        getline( inputRoiFile, strLine );
        if ( textUtil.lineStart( strLine, ';' ) ) // header
        {
            if ( lineCounter == 0 ) // first line
            {
                textUtil.tokenizeString( strLine, ' ', tokens, true );
                if( tokens->at( 1 ) != std::string( "ENVI" ) &
                        tokens->at( 2 ) != std::string( "Output" ) &
                        tokens->at( 3 ) != std::string( "of" ) &
                        tokens->at( 4 ) != std::string( "ROIs" ) )
                {
                    throw GRTextException( "Incorrect file format" );
                }
            }
            else if ( lineCounter == 1 ) // second line
            {
                textUtil.tokenizeString( strLine, ':', tokens, true );
                roiCount = strtol( tokens->at( 1 ).c_str(), NULL, 10 );
                //std::cout << "Number of ROI\'s = " << numrois << std::endl;
                rois = new ENVIRoi[roiCount];
                currentRoiIndex = 0;
                tokens->clear();
                headingLine =  3 * roiCount  + 3 + roiCount;
            }
            else
            {
                if ( lineCounter < headingLine ) // header information lines
                {
                    textUtil.tokenizeString( strLine, ':', tokens, true );
                    for( unsigned int i = 0; i < tokens->size(); i++ )
                    {
                        //std::cout << i << ") \'" << tokens->at(i) << "\'" << std::endl;
                        if( tokens->at( i ) == std::string( "; ROI name" ) )
                        {
                            rois[currentRoiIndex].name = tokens->at( i + 1 );
                        }
                        else if( tokens->at( i ) == std::string( "; ROI rgb value" ) )
                        {

                            std::vector<std::string> temp;
                            textUtil.tokenizeString( tokens->at( i + 1 ), ',', &temp, true );
                            double red = std::stod( temp.at( 0 ).substr( 2, temp.at( 0 ).length() ) );
                            double green = std::stod( temp.at( 1 ) );
                            double blue = 0;
                            double alpha = 0;
                            if ( temp.size() == 4 )
                            {
                                blue = std::stod( temp.at( 2 ).substr( 0, temp.at( 2 ).length() - 1 ) );
                                alpha = std::stod( temp.at( 3 ).substr( 0, temp.at( 3 ).length() - 1 ) );
                            }
                            else
                            {
                                blue = std::stod( temp.at( 2 ).substr( 0, temp.at( 2 ).length() - 1 ) );
                            }
                            rois[currentRoiIndex].color = new GRColor( red, green, blue, alpha );
                        }
                        else if( tokens->at( i ) == std::string( "; ROI npts" ) )
                        {
                            rois[currentRoiIndex].samples = strtol( tokens->at( 1 ).c_str(), NULL, 10 );
                            currentRoiIndex++;
                        }
                    }
                    tokens->clear();
                }
                else if( lineCounter == headingLine ) // data header line
                {
                    //std::cout << "Headings: " << strLine << std::endl;
                    textUtil.tokenizeString( strLine, ' ', tokens, true );
                    //std::cout << "Number tokens = " << tokens->size() << std::endl;
                    int varDiff = 0;
                    std::string b1 = std::string( "B1" );
                    for( unsigned int i = 0; i < tokens->size(); i++ )
                    {
                        //std::cout << i << ") \'" << tokens->at(i) << "\'" << std::endl;
                        if( std::string( tokens->at( i ) ) == b1 )
                        {
                            varDiff = i;
                        }
                    }
                    //std::cout << "varDiff = " << varDiff << std::endl;
                    //std::cout << "numVaribles (using varDiff) = " << tokens->size() - varDiff << std::endl;
                    VariableCount = tokens->size() - varDiff;

                    if( varDiff == 4 )
                    {
                        dataStart = varDiff - 1;
                    }
                    else
                    {
                        dataStart = varDiff - 3;
                    }
                    std::cout << "There are " << roiCount << " roi's where each sample has " << VariableCount << " variables\n";
                    for( int i = 0; i < roiCount; i++ )
                    {
                        std::cout << "ROI " << rois[i].name << " has " << rois[i].samples << " samples\n";
                        rois[i].data = matrixUtil.createMatrix( rois[i].samples, VariableCount );
                        //matrixUtils.printMatrix(rois[i].data);
                    }
                    tokens->clear();
                    currentRoiIndex = 0;
                }
            }
        }
        // empty lines
        else if( textUtil.blankline( strLine ) && currentRoiIndex != roiCount )
        {
            std::cout << "START OF " << rois[currentRoiIndex].name << " ROI DATA\n";
            currentRoiIndex++;
            sampleCount = 0;
            dataindex = 0;
        }
        // data lines
        else
        {
            // DATA
            /*std::cout << "dataStart = " << dataStart << std::endl;
            std::cout << lineCounter << ") " << strLine << std::endl;
            std::cout << sampleCount << "] ROI: " << roicount << std::endl;*/
            textUtil.tokenizeString( strLine, ' ', tokens, true );
            //std::cout << "Found " << tokens->size() << " tokens\n";
            for( unsigned int i = dataStart; i < tokens->size(); i++ )
            {
                rois[currentRoiIndex].data->matrix[dataindex++] = strtod( tokens->at( i ).c_str(), NULL );
                //std::cout << variable << ") " << tokens->at( i ) << std::endl;
            }
            tokens->clear();
            sampleCount++;
        }
        lineCounter++;
    }

    delete tokens;
}

ENVIRoi* GREnviAsciiRoi::getENVIRoi( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= roiCount )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return &rois[i];
}

int GREnviAsciiRoi::getVariableCount() throw ( GREnviRoiException )
{
    return VariableCount;
}

GRColor* GREnviAsciiRoi::getColor( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= roiCount )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return rois[i].color;
}

int GREnviAsciiRoi::getNumSamples( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= roiCount )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return rois[i].samples;
}

math::Matrix* GREnviAsciiRoi::getMatrix( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= roiCount )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return rois[i].data;
}

std::string* GREnviAsciiRoi::getName( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= roiCount )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return &rois[i].name;
}

int GREnviAsciiRoi::getRoiCounts()
{
    return roiCount;
}

void GREnviAsciiRoi::printRois()
{
    math::GRMatrices matrixUtil;
    for ( int i = 0; i < this->roiCount; i++ )
    {
        std::cout << "ROI " << rois[i].name << " has" << rois[i].samples << std::endl;
        matrixUtil.printMatrix( rois[i].data );
    }
}

int GREnviAsciiRoi::getTotalRoiSamplesCount()
{
    int totalCount = 0;
    for ( int i = 0; i < roiCount; i++ )
    {
        totalCount += rois[i].samples;
    }
    return totalCount;
}

GREnviAsciiRoi::~GREnviAsciiRoi()
{
    delete rois;
}

}
}