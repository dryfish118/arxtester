//
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
// This file contains the class AcGePointEnt2d - An abstract base
// class to represent point entities.

#ifndef AC_GEPENT2D_H
#define AC_GEPENT2D_H

#include "adesk.h"
#include "geent2d.h"
#include "gepnt2d.h"
#pragma pack (push, 8)

class 

AcGePointEnt2d : public AcGeEntity2d
{
public:

    // Return point coordinates.
    //
    GE_DLLEXPIMPORT AcGePoint2d     point2d     () const;

    // Conversion operator to convert to AcGePoint2d.
    //
    GE_DLLEXPIMPORT operator        AcGePoint2d () const;
    
    // Assignment operator.
    //
    GE_DLLEXPIMPORT AcGePointEnt2d& operator =  (const AcGePointEnt2d& pnt);

protected:

    // Private constructors so that no object of this class can be instantiated.
    GE_DLLEXPIMPORT AcGePointEnt2d ();
    GE_DLLEXPIMPORT AcGePointEnt2d (const AcGePointEnt2d&);
};

#pragma pack (pop)
#endif
