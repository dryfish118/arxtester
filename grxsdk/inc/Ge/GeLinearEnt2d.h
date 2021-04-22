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

#ifndef OD_GE_LINEAR_ENT_2D_H
#define OD_GE_LINEAR_ENT_2D_H /*!DOM*/

class OdGeCircArc2d;

#include "../Ge/GeCurve2d.h"
#include "../OdPlatformSettings.h"
#include <memory.h> // for memcpy

#include "../TD_PackPush.h"
class OdGeLinearEnt3dImpl;

/** \details
    This class is the base class for OdGe 2D linear entities.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeLinearEnt2d : public OdGeCurve2d
{
public:
  

  /** \details
    Returns true and the intersection point, if and only 
    if the specified linear entity intersects with this one.

    \param line [in]  2D linear entity with which the intersection is computed.
    \param intPnt [out]  Receives the intersection point.
    \param tol [in]  Geometric tolerance.
  */
  OdBool intersectWith(
    const OdGeLinearEnt2d& line, 
    OdGePoint2d& intPnt,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Determines if two lines overlap and if so returns 
    the line that coincides with their region of overlap. 

    \param line [in]  2D linear entity with which overlapping is tested.
    \param overlap [out]  Output linear entity that is coincident with region of overlap  
    \param tol [in]  Input tolerance.
  */
  OdBool overlap(
    const OdGeLinearEnt2d& line, 
    OdGeLinearEnt2d*& overlap,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified linear entity is parallel to this one.

    \param line [in]  2D linear entity that is tested for being parallel with this linear entity.
    \param tol [in]  Geometric tolerance.
  */
  OdBool isParallelTo(
    const OdGeLinearEnt2d& line, 
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified linear entity is perpendicular to this one.

    \param line [in]  2D linear entity that is tested for being perpendicular to this linear entity.
    \param tol [in]  Geometric tolerance.
  */
  OdBool isPerpendicularTo(
    const OdGeLinearEnt2d& line, 
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified linear entity is collinear to this one.

    \param line [in]  2D linear entity that is tested for being collinear with this linear entity.
    \param tol [in]  Geometric tolerance.
  */
  OdBool isColinearTo(
    const OdGeLinearEnt2d& line, 
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns a reference to a 2D line perpendicular to this one,
    and passing through the specified point.

    \param point [in]  2D point through which the perpendicular line passes.
    \param perpLine [out]  Receives a reference to the perpendicular line.

    \remarks
    It is up to the caller to delete the returned line.
  */
  void getPerpLine(
    const OdGePoint2d& point, 
    OdGeLine2d& perpLine) const;

  /** \details
    Returns an arbitrary point on this linear entity.
  */
  OdGePoint2d pointOnLine() const;

  /** \details
    Returns a unit vector parallel to this linear entity, 
    and pointing in the direction of increasing parametric value.
  */
  OdGeVector2d direction() const;

  /** \details
    Returns a reference to an infinite line colinear with this linear entity.

    \param line [out]  Receives the infinite line.

    \remarks
    It is up to the caller to delete the returned line.
  */
  void getLine(
    OdGeLine2d& line) const;

  /** \details
    Assignment operator for the OdGeLinearEnt2d object.
  */
  OdGeLinearEnt2d& operator =(const OdGeLinearEnt2d& line);

  //////////////////////////////////////////////////////////////////////////
  // Overrides :

  //////////////////////////////////////////////////////////////////////////
  // TD Special overrides :
//DOM-IGNORE-BEGIN
protected:
  /** \param source [in]  Object to be cloned.
  */
  OdGeLinearEnt2d(); 
  OdGeLinearEnt2d(OdGeLinearEnt3dImpl *);
  OdGeLinearEnt2d(const OdGeLinearEnt2d& source); 
//DOM-IGNORE-END
};

#include "../TD_PackPop.h"

#endif

