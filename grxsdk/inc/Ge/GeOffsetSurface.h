/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef OD_GEOFFSF_H
#define OD_GEOFFSF_H /*!DOM*/

#include "../Ge/GeSurface.h"

#include "../TD_PackPush.h"

/** \details
    This class represents surfaces that are exact offsets of other surfaces.

    Corresponding C++ library: TD_Ge

   <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeOffsetSurface : public OdGeSurface
{
public:

  /** \details
    Default constructor for the OdGeOffsetSurface class.
    
    \remarks
    This constructor initializes the base surface pointer to NULL and the offset distance to 0.0.
  */
  OdGeOffsetSurface();
  
  /** \details
    Constructor for the OdGeOffsetSurface class.
    
    \param baseSurface [in]  A base surface that is referenced by this offset surface.
    \param offsetDistance [in]  Offset distance.
    \param makeCopy [in]  Makes a copy of baseSurface.

    \remarks
    Constructs an offset object defined by input data. If makeCopy is true, then the offset points to its own copy of the base surface. 
    Otherwise it points directly to the input surface.
    The direction of offset is determined by the sign of the offsetDistance parameter.
  */
  OdGeOffsetSurface(
    OdGeSurface* baseSurface,
    double offsetDistance,
    OdBool makeCopy = true);
  
  /** \details
    Copy constructor for the OdGeOffsetSurface class.
    
    \param source [in]  Object to be copied.
  */
  OdGeOffsetSurface(
    const OdGeOffsetSurface& source);

  /** \details
    Return true if and only if the offset surface can be represented as an OdGePlanarEnt. 

    \remarks
    Currently not implemented.
  */
   OdBool isPlane() const;
  
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeBoundedPlane. 

    \remarks
    Currently not implemented.
  */
   OdBool isBoundedPlane() const;
  
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeSphere. 

    \remarks
    Currently not implemented.
  */
   OdBool isSphere() const;
  
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeCylinder. 

    \remarks
    Currently not implemented.
  */
   OdBool isCylinder() const;
  
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeCone. 

    \remarks
    Currently not implemented.
  */
   OdBool isCone() const;
   
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeEllipCylinder. 

    \remarks
    Currently not implemented.
  */
   OdBool isEllipCylinder() const;
  
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeEllipCone. 

    \remarks
    Currently not implemented.
  */
   OdBool isEllipCone() const;
  
  /** \details
    Return true if and only if the offset surface can be represented as an OdGeTorus. 

    \remarks
    Currently not implemented.
  */
   OdBool isTorus() const;
  
  /** \details
    Creates a copy of this surface as an OdGeSurface, and returns a pointer to the new surface.
    
    \param simpleSurface [out]  Receives the converted simple OdGeSurface. 
  */
   OdBool getSurface(
    OdGeSurface*& simpleSurface) const;

  /** \details
    Returns the base surface.
    
    \param baseSurface [out]  Receives base surface.
  */
   void getConstructionSurface(
    OdGeSurface*& baseSurface) const;

  /** \details
    Returns the offset distance of this surface. 
  */
   double offsetDist() const;

  /** \details
    Sets the parameters for this surface according to the arguments.

    \param baseSurface [in]  A base surface that is referenced by this offset surface.
    \param offsetDistance [in]  Offset distance.
    \param makeCopy [in]  Makes a copy of baseSurface.
    
    \returns
    Returns a reference to this surface.
    
    \remarks
    The direction of offset is determined by the sign of the offsetDistance parameter.
  */
   OdGeOffsetSurface& set(
    OdGeSurface* baseSurface, 
    double offsetDistance,
    OdBool makeCopy = true);

  /** \details
    Assignment operator for the OdGeOffsetSurface object.
  */
  OdGeOffsetSurface& operator =(
    const OdGeOffsetSurface& surface);

};

#include "../TD_PackPop.h"

#endif // OD_GEOFFSF_H

