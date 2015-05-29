#include "GREnviAsciiRoi.h"

namespace GR
{
namespace utils
{


GREnviAsciiRoi::GREnviAsciiRoi( std::string file )
{
    this->inputfile = file;
    this->parsefile();
}

void GREnviAsciiRoi::parsefile()
{

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

math::GRMatrix* GREnviAsciiRoi::getMatrix( int i ) throw ( GREnviRoiException )
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

}

}
}