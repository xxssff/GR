#pragma once

#include "ENVIRoi.h"
#include "GRColor.h"
#include "GREnviRoiException.h"

namespace GR
{
namespace utils
{

// ENVI ACSII roi class, parse and store the information of ENVI ACSII roi files.
class _declspec( dllexport ) GREnviAsciiRoi
{

private:

    // input ENVI ASCII roi file
    std::string inputfile;
    int numrois;
    int VariableCount;
    ENVIRoi* rois;

    // parse roi files.
    void parsefile() throw ( GR::GRInputStreamException );

public:
    GREnviAsciiRoi( std::string file );
    ~GREnviAsciiRoi();


    ENVIRoi* getENVIRoi( int i ) throw ( GREnviRoiException );

    int getVariableCount();

    GRColor* getColor( int i ) throw ( GREnviRoiException );

    int getNumSamples( int i ) throw ( GREnviRoiException );

    math::Matrix* getMatrix( int i ) throw ( GREnviRoiException );

    std::string* getName( int i ) throw ( GREnviRoiException );

    int getRoiCounts();

    void printRois();
};

}
}