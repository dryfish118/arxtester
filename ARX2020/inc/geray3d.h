//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2019 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This file contains the class AcGeRay3d - A mathematical entity
// used to represent a ray (half line) in 3-space.

#ifndef AC_GERAY3D_H
#define AC_GERAY3D_H

#include "gelent3d.h"
#pragma pack (push, 8)

class AcGeRay2d;

class

AcGeRay3d : public AcGeLinearEnt3d
{
public:
    GE_DLLEXPIMPORT AcGeRay3d();
    GE_DLLEXPIMPORT AcGeRay3d(const AcGeRay3d& line);
    GE_DLLEXPIMPORT AcGeRay3d(const AcGePoint3d& pnt, const AcGeVector3d& vec);
    GE_DLLEXPIMPORT AcGeRay3d(const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Set methods.
    //
    GE_DLLEXPIMPORT AcGeRay3d&     set         (const AcGePoint3d& pnt, const AcGeVector3d& vec);
    GE_DLLEXPIMPORT AcGeRay3d&     set         (const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Assignment operator.
    //
    GE_DLLEXPIMPORT AcGeRay3d&     operator =  (const AcGeRay3d& line);
};

#pragma pack (pop)
#endif
