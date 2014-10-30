#include "GRFeature.h"



GRFeature::GRFeature()
{

}

GRFeature::GRFeature( GRFeature const& rhs )
    : mGeometry( rhs.mGeometry ),
      mTypeName( rhs.mTypeName ),
      mDirty( rhs.mDirty ),
      mValid( rhs.mValid )
{

}

GRFeature::~GRFeature()
{

}