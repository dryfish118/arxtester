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

#ifndef OD_GELENT3D_H
#define OD_GELENT3D_H /*!DOM*/

class OdGeLine3d;
class OdGeCircArc3d;
class OdGePlanarEnt;
class OdGeLinearEnt3dImpl;

#include "../OdPlatform.h"
#include "../Ge/GeCurve3d.h"

#include "../TD_PackPush.h"

/** \details
    This class is the base class for OdGe 3D linear entities.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeLinearEnt3d : public OdGeCurve3d
{
public:

  ///////////////////////////////////////////////////////////////////////////

  /** \details
    Returns true and the intersection point, if and only 
    if the specified line intersects with this line.

    \param line [in]  3D linear entity with which an intersection is computed.
    \param intPt [out]  Receives the intersection point.
    \param tol [in]  Geometric tolerance.
  */
   OdBool intersectWith(
    const OdGeLinearEnt3d& line,
    OdGePoint3d& intPt,
    const OdGeTol& tol = OdGeContext::gTol) const;
  
  /** \details
    Returns true and the intersection point, if and only 
    if the specified plane intersects with this line.

    \param plane [in]  A planar entity with which overlapping is tested.
    \param intPnt [out]  Receives the intersection point.
    \param tol [in]  Geometric tolerance.
  */
  OdBool intersectWith(
    const OdGePlanarEnt& plane, 
    OdGePoint3d& intPnt,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns the projected intersection of the specified line with this line.

    \param line [in]  3D projected linear entity with which the intersection is computed.
    \param projDir [in]  Projection direction.
    \param pntOnThisLine [out]  Receives the intersection point on this line.   
    \param pntOnOtherLine [out]  Receives the intersection point on the other line. 
    \param tol [in]  Geometric tolerance.

    \remarks
    By default this function throws exception "not Implemented".
  */
   OdBool projIntersectWith(
    const OdGeLinearEnt3d& line,
    const OdGeVector3d& projDir,
    OdGePoint3d& pntOnThisLine,
    OdGePoint3d& pntOnOtherLine,
    const OdGeTol& tol = OdGeContext::gTol) const;

   /** \details
    Determines if two lines overlap and if so returns 
    the line that coincides with their region of overlap. 

    \param line [in]  3D linear entity with which overlapping is tested.
    \param overlap [out]  Output linear entity that is coincident with the region of overlap.
    \param tol [in]  Input tolerance.
   */
   OdBool overlap(
    const OdGeLinearEnt3d& line,
    OdGeLinearEnt3d*& overlap,
    const OdGeTol& tol = OdGeContext::gTol) const;
//DOM-IGNORE-BEGIN
  TD_USING(OdGeCurve3d::isOn);
//DOM-IGNORE-END
   
   /** \details
    Determines if this line lies on the specified plane considering the tolerance. 

    \param plane [in]  Planar entity on which this line presumably lies.
    \param tol [in]  Input tolerance.
   */
   OdBool isOn(
    const OdGePlane& plane,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified entity is parallel to this line.

    \param line [in]  3D linear entity which is tested to be parallel with this linear entity.
    \param tol [in]  Geometric tolerance.
  */
   OdBool isParallelTo(
    const OdGeLinearEnt3d& line,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified entity is parallel to this line.

    \param plane [in]  Planar entity that is presumably parallel to this linear entity.
    \param tol [in]  Geometric tolerance.
  */
    OdBool isParallelTo(
    const OdGePlanarEnt& plane,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified entity is perpendicular to this line.

    \param line [in]  3D linear entity which is tested to be perpendicular to this linear entity.
    \param tol [in]  Geometric tolerance.
  */
   OdBool isPerpendicularTo(
    const OdGeLinearEnt3d& line,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only 
    if the specified entity is perpendicular to this line.

    \param plane [in]  Planar entity that is presumably perpendicular to this linear entity.
    \param tol [in]  Geometric tolerance.
  */
    OdBool isPerpendicularTo(
    const OdGePlanarEnt& plane,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only if the specified line is collinear with this one. 

    \param line [in]  3D linear entity which is tested to be collinear with this linear entity.
    \param tol [in]  Geometric tolerance.
  */
   OdBool isColinearTo(
    const OdGeLinearEnt3d& line,
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns a plane, containing the specified point, perpendicular to this line.

    \param point [in]  3D point at which the given plane is perpendicular to this linear entity.
    \param plane [out]  Receives the perpendicular plane.

    \remarks
    The returned plane is created with the new method. It is up to the caller to delete it.
  */
   void getPerpPlane(
      const OdGePoint3d& point, 
      OdGePlane& plane) const;

  /** \details
    Returns an arbitrary point on this line.
  */
   OdGePoint3d pointOnLine() const;

  /** \details
    Returns a unit vector parallel to this line, 
    and pointing in the direction of increasing parametric value.
  */
   OdGeVector3d direction() const;

  /** \details
    Returns a reference to an infinite line collinear with this one.

    \param line [out]  Receives the infinite line.
  */
   void getLine(OdGeLine3d& line) const;

  /** \details
    Assignment operator for the OdGeLinearEnt3d object.
  */ 
  OdGeLinearEnt3d& operator =(
      const OdGeLinearEnt3d& line);
//DOM-IGNORE-BEGIN
protected:
  OdGeLinearEnt3d(); 
  OdGeLinearEnt3d(OdGeLinearEnt3dImpl* impl);

  OdGeLinearEnt3d(
    const OdGeLinearEnt3d& source);
//DOM-IGNORE-END
};

#include "../TD_PackPop.h"

#endif // OD_GELENT3D_H
