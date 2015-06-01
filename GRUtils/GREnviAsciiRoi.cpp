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
    GR::math::GRMatrices matrixUtils;
    std::ifstream inputRoiFile;
    inputRoiFile.open( inputfile.c_str() );
    if ( !inputRoiFile.is_open() )
    {
        std::string msg = std::string( "Could not open input text file: " ) + inputfile;
        throw GR::GRInputStreamException( msg );
    }
    else
    {
        std::string strLine;
        std::string word;
        GRTextUtils textUtils;
        int lineCounter = 0; // current line
        int roicount = 0; // total roi numbers
        int headingsLine = 0;
        int sampleCount = 0; // roi sample numbers
        int variable = 0;
        int dataindex = 0;
        int dataStart = 0;
        inputRoiFile.seekg( std::ios_base::beg );
        std::vector<std::string> *tokens = new std::vector<std::string>();
        while( !inputRoiFile.eof() )
        {
            getline( inputRoiFile, strLine );

            // lines start with ";"
            if( textUtils.lineStart( strLine, ';' ) )
            {
                // Header
                if( lineCounter == 0 )
                {
                    textUtils.tokenizeString( strLine, ' ', tokens, true );
                    for( unsigned int i = 0; i < tokens->size(); i++ )
                    {
                        //std::cout << i << ") " << tokens->at(i) << std::endl;
                        if( tokens->at( 1 ) == std::string( "ENVI" ) &
                                tokens->at( 2 ) == std::string( "Output" ) &
                                tokens->at( 3 ) == std::string( "of" ) &
                                tokens->at( 4 ) == std::string( "ROIs" ) )
                        {
                            // correct file type;
                        }
                        else
                        {
                            throw GRTextException( "Incorrect file format" );
                        }
                    }
                    tokens->clear();
                }
                else if( lineCounter == 1 )
                {
                    textUtils.tokenizeString( strLine, ':', tokens, true );
                    numrois = strtol( tokens->at( 1 ).c_str(), NULL, 10 );
                    //std::cout << "Number of ROI\'s = " << numrois << std::endl;
                    rois = new ENVIRoi[numrois];
                    roicount = 0;
                    tokens->clear();
                    headingsLine = ( 3 * numrois ) + 3 + numrois;
                }
                else
                {
                    if( lineCounter == headingsLine )
                    {
                        //std::cout << "Headings: " << strLine << std::endl;
                        textUtils.tokenizeString( strLine, ' ', tokens, true );
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
                        std::cout << "There are " << numrois << " roi's where each sample has " << VariableCount << " variables\n";
                        for( int i = 0; i < numrois; i++ )
                        {
                            std::cout << "ROI " << rois[i].name << " has " << rois[i].samples << " samples\n";
                            rois[i].data = matrixUtils.createMatrix( VariableCount, rois[i].samples );
                            //matrixUtils.printMatrix(rois[i].data);
                        }
                        tokens->clear();
                        roicount = 0;
                    }
                    else // read all the headingsLine and store information of rois
                    {
                        textUtils.tokenizeString( strLine, ':', tokens, true );
                        for( unsigned int i = 0; i < tokens->size(); i++ )
                        {
                            //std::cout << i << ") \'" << tokens->at(i) << "\'" << std::endl;
                            if( tokens->at( i ) == std::string( "; ROI name" ) )
                            {
                                rois[roicount].name = tokens->at( i + 1 );
                            }
                            else if( tokens->at( i ) == std::string( "; ROI rgb value" ) )
                            {
                                rois[roicount].color = new GRColor();
                            }
                            else if( tokens->at( i ) == std::string( "; ROI npts" ) )
                            {
                                rois[roicount].samples = strtol( tokens->at( 1 ).c_str(), NULL, 10 );
                                roicount++;
                            }
                        }
                        tokens->clear();
                    }
                }
            }
            // empty lines
            else if( textUtils.blankline( strLine ) )
            {
                std::cout << "START OF NEW ROI DATA\n";
                roicount++;
                sampleCount = 0;
                dataindex = 0;
            }
            // data lines
            else
            {
                // DATA
                //std::cout << "dataStart = " << dataStart << std::endl;
                //std::cout << lineCounter << ") " << strLine << std::endl;
                //std::cout << sampleCount << "] ROI: " << roicount << std::endl;
                variable = 0;
                textUtils.tokenizeString( strLine, ' ', tokens, true );
                //std::cout << "Found " << tokens->size() << " tokens\n";
                for( unsigned int i = dataStart; i < tokens->size(); i++ )
                {
                    rois[roicount].data->matrix[dataindex++] = strtod( tokens->at( i ).c_str(), NULL );
                    //std::cout << variable << ") " << tokens->at(i) << std::endl;
                    variable++;
                }
                tokens->clear();
                sampleCount++;
            }
            lineCounter++;
        }
    }



}

ENVIRoi* GREnviAsciiRoi::getENVIRoi( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= numrois )
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
    if ( i<0 & i >= numrois )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return rois[i].color;
}

int GREnviAsciiRoi::getNumSamples( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= numrois )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return rois[i].samples;
}

math::Matrix* GREnviAsciiRoi::getMatrix( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= numrois )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return rois[i].data;
}

std::string* GREnviAsciiRoi::getName( int i ) throw ( GREnviRoiException )
{
    if ( i<0 & i >= numrois )
    {
        throw GREnviRoiException( "There are insufficient ROIs in datastructure.." );
    }
    return &rois[i].name;
}

int GREnviAsciiRoi::getRoiCounts()
{
    return numrois;
}

void GREnviAsciiRoi::printRois()
{

}

}
}