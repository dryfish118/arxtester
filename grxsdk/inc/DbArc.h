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




#ifndef _OD_DB_ARC_
#define _OD_DB_ARC_

#include "TD_PackPush.h"

#include "DbCurve.h"
#include "DwgDeclareMembers.h"

/** \details
  <group OdDb_Classes>

  This class implements the circular arc object (Arc entity) in the database. This class 
  inherits the base functionality of entities. An arc is a circular segment in world space.

  
  \sa
  <link db_circular_arc, Working with Circular Arcs>

  \sa
  <link db_circular_arc_sample, Example of Working with the Circular Arc>

  \sa 
  <link OdDbCircle, OdDbCircle class>, <link OdDbEllipse, OdDbEllipse class>
*/
class DBENT_EXPORT OdDbArc : public OdDbCurve
{
public:

  DWGMAP_DECLARE_MEMBERS(OdDbArc);

  /** \details
    Builds an instance of the circular arc object.
    
    \remarks
    Use the static pseudo-constructor instead it.
    
	\sa 
	<link db_circular_arc_overview, Overview of Circular Arcs>
  */
  OdDbArc();

  OdDbArc(const OdGePoint3d& center, double radius,
    double startAngle, double endAngle);

  OdDbArc(const OdGePoint3d& center, const OdGeVector3d& normal,
    double radius, double startAngle, double endAngle);

  ~OdDbArc();

  /** \details
    Returns the WCS coordinates of the arc center (DXF 10) as three-dimensional point instance.

    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa 
	<link OdDbArc::setCenter@OdGePoint3d&, OdDbArc::setCenter() method>
  */
  OdGePoint3d center() const;


  /** \details
    Sets the center point of the circular arc (DXF 10) in WCS. The initial value is  
    (0,0,0) by default.
    
    \param center [in]  Three-dimensional point instance to set the center.

    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa 
	<link OdDbArc::center@const, OdDbArc::center() method>
  */
  OdResult setCenter( const OdGePoint3d& center );

  /** \details
    Returns the radius of the circular arc (DXF 40).

    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
	\sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
	<link OdDbArc::setRadius@double, OdDbArc::setRadius() method>
  */
  double radius() const;


  /** \details
    Sets the radius of the circular arc (DXF 40). The initial value is 0.0 by default.

    \param radius [in]  Radius as a Double value.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::radius@const, OdDbArc::radius() method>
  */
  OdResult setRadius( double radius );


  /** \details
    Returns the start angle of the circular arc in radians (DXF 50).

    \remarks
    The angle is measured counterclockwise from the OCS X-axis.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::setStartAngle@double, OdDbArc::setStartAngle() method>, <link OdDbArc::endAngle@const, OdDbArc::endAngle() method>
  */
  double startAngle() const;


  /** \details
    Sets the start angle of the circular arc in the range ?PI radians (DXF 50).
    A positive value specifies the angle measured from the OCS X-axis counterclockwise. 
    A negative value specifies the angle measured from the OCS X-axis clockwise. 
    The initial value is zero by default.

    \param startAngle [in]  Start angle as a Double value.
    
    \remarks
    If an angle value is negative, this method automatically converts it to the positive 
    equivalent. If an angle value is more than 2PI, this method automatically converts 
    it to the range 0 to 2PI.    

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::startAngle@const, OdDbArc::startAngle() method>, <link OdDbArc::setEndAngle@double, OdDbArc::setEndAngle() method>
  */
  OdResult setStartAngle( double startAngle );


  /** \details
    Returns the end angle of the circular arc in radians (DXF 51).

    \remarks
    The angle is measured counterclockwise from the OCS X-axis.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::setStartAngle@double, OdDbArc::setStartAngle() method>, <link OdDbArc::startAngle@const, OdDbArc::startAngle() method>
  */
  double endAngle() const;


  /** \details
    Sets the end angle of the circular arc in the range ?PI radians (DXF 51).
    A positive value specifies the angle measured from the OCS X-axis counterclockwise. 
    A negative value specifies the angle measured from the OCS X-axis clockwise. 
    The initial value is zero by default.

    \param endAngle [in]  End angle as a Double value.

    \remarks
    If an angle value is negative, this method automatically converts it to the positive 
    equivalent. If an angle value is more than 2PI, this method automatically convertes 
    it to the range 0 to 2PI.    

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
	\sa
    <link OdDbArc::endAngle@const, OdDbArc::endAngle() method>, <OdDbArc::setStartAngle@double, OdDbArc::setStartAngle() method>
  */
  OdResult setEndAngle( double endAngle );


  /** \details
    Returns the thickness of the circular arc entity (DXF 39) in drawing units. Thickness  
    is the extrusion length along the normal. A positive value defines the thickness to 
    be drawn along the normal direction. A negative value defines the thickness to be 
    drawn in the opposite direction from the normal. A zero value defines an arc without 
    thickness.
    
    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::setThickness@double, OdDbArc::setThickness() method>
  */
  double thickness() const;


  /** \details
    Sets the thickness of the circular arc entity (DXF 39) in drawing units. Thickness is  
    the extrusion length along the normal. A positive value extrudes along the normal. 
    A negative value extrudes opposite from the normal. A zero value defines an arc without 
    thickness. The initial value is zero by default.

    \param vThickness [in]  Thickness as a Double value.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa
	<link OdDbArc::thickness@const, OdDbArc::thickness() method>
  */
  OdResult setThickness( double vThickness );


  /** \details
    Returns the WCS unit vector which is the normal to the plane of the circular arc  
    entity (DXF 210). The normal defines the orientation of the arc plane in world space.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::setNormal@OdGeVector3d&, OdDbArc::setNormal() method>
  */
  OdGeVector3d normal() const;


  /** \details
    Sets the WCS normal to the plane of the circular arc entity (DXF 210). The normal defines 
    the orientation of the arc plane in world space. The initial value is (0,0,1) by default.

    \param geVector [in]  Three-dimensional vector instance to set the normal.

    \remarks
    This method automatically converts the specified vector to the unit vector.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc_specific, Specific Circular Arc Properties>
    \sa 
	<link OdDbArc::normal@const, OdDbArc::normal() method>
  */
  OdResult setNormal( const OdGeVector3d& geVector );


  /** \details
  Returns the entity coordinate system matrix.
  */
  void getEcs(OdGeMatrix3d&) const;
  
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult dxfInFields_R12(
    OdDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdDbDxfFiler* pFiler) const;

  virtual OdBool subWorldDraw(
    OdGiWorldDraw* pWd);

  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm);

  virtual OdResult subGetTransformedCopy(
    const OdGeMatrix3d& xfm, 
    OdDbEntity*& pCopy) const;

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  virtual OdBool isClosed() const;

  virtual OdBool isPeriodic() const;


  /** \details
    Determines whether the circular arc entity is planar as a Boolean value and returns True.
    This method is inherited from the OdDbEntity class.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc, Working with Circular Arcs>
    \sa
	<link OdDbArc::getPlane@OdGePlane&@OdDb::Planarity&@const, OdDbArc::getPlane() method>, <link OdDbEntity::isPlanar@const, OdDbEntity::isPlanar() method>
  */
  virtual OdBool isPlanar() const;


  /** \details
    Gets a plane in which the circular arc entity places. This method is inherited from the  
    OdDbEntity class.

    \param gePlane [out]  Reference to a variable in which this method must save the plane parameters as 
                a plane instance.
    \param gePlanarity [out] Reference to a variable in which this method must save the plane type
                    (returns kPlanar - planar entity).

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>
    \sa
    <link db_circular_arc, Working with Circular Arcs>
    \sa
	<link OdDbArc::isPlanar@const, OdDbArc::isPlanar()>, <link OdDbEntity::getPlane@OdGePlane&@OdDb::Planarity&@const, OdDbEntity::getPlane()> methods
  */
  virtual OdResult getPlane( OdGePlane& gePlane, OdDb::Planarity& gePlanarity ) const;


  /** \details
    Gets the start parameter value. The start parameter equals equals the start angle.
    Parameter is an angle measured counterclockwise from the OCS X-axis in the range 
    0 to 2PI radians.

    \param startParam [out]  Reference to a variable in which this method must save the start    
                   parameter value as a Double value in radians.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getStartParam( double& startParam ) const;


  /** \details
    Gets the end parameter value. The end parameter equals the end angle.
    Parameter is an angle measured counterclockwise from the OCS X-axis in the range 
    0 to 2PI radians.

    \param endParam [out]  Reference to a variable in which this method must save the end    
                 parameter value as a Double value in radians.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getEndParam( double& endParam ) const;


  /** \details
    Computes the WCS coordinates of the start point on the circular arc for which  
    the parameter equals the start angle.

    \param startPoint [out]  Reference to a variable in which this method must save the start 
                   point as three-dimensional point instance.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getStartPoint( OdGePoint3d& startPoint ) const;


  /** \details
    Computes the WCS coordinates of the end point on the circular arc for which the  
    parameter equals the end angle.

    \param endPoint [out]  Reference to a variable in which this method must save the end  
                 point as three-dimensional point instance.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getEndPoint( OdGePoint3d& endPoint ) const;


  /** \details
    Computes the WCS coordinates of the point on the circular arc at the specified 
    parameter value. Parameter is an angle measured counterclockwise from the OCS 
    X-axis in the range 0 to 2PI radians.

    \param param [in]  Parameter value specifying the point on the circular curve as a Double 
              value in radians. 
    \param pointOnCurve [out] Reference to a variable in which this method must save the 
                     three-dimensional point instance corresponding to the parameter.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getPointAtParam( double param, OdGePoint3d& pointOnCurve ) const;


  /** \details
    Computes the parameter at the point placed on the circular arc. Parameter is an 
    angle measured counterclockwise from the OCS X-axis in the range 0 to 2PI radians.

    \param pointOnCurve [in]  Three-dimensional point instance which specifies the point on 
                     the circular curve. 
    \param param [out] Reference to a variable in which this method must save the parameter   
              value as a Double value in radians.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getParamAtPoint( const OdGePoint3d& pointOnCurve, double& param ) const;


  /** \details
    Computes the distance along the circular arc measured from the start point to the 
    point on circular curve specified by the parameter.

    \param param [in]  Parameter value specifying the point on the circular curve as a Double 
              value in radians. 
    \param dist  [out] Reference to a variable in which this method must save the distance value 
              as a Double value in drawing units.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getDistAtParam( double param, double& dist ) const;


  /** \details
    Computes the parameter at the distance along the circular arc. Parameter is an angle
    measured from the OCS X-axis in the range 0 to 2PI radians. 

    \param dist [in]   Distance value along the circular curve as a Double value in drawing units. 
    \param param [out]  Reference to a variable in which this method must save the parameter value  
              as a Double value in radians.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getParamAtDist( double dist, double& param ) const;


  /** \details
    Computes the first derivative for the specified parameter of the circular arc entity 
    and returns the three-dimensional vector instance.

    \param param [in]  Parameter value specifying the point on the circular curve as a Double 
              value in radians. 
    \param firstDeriv [out] Reference to a variable in which this method must save the first  
                   derivative as three-dimensional vector instance.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getFirstDeriv( double param, OdGeVector3d& firstDeriv ) const;


  /** \details
    Computes the second derivative for the specified parameter of the circular arc entity   
    and returns the three-dimensional vector instance.

    \param param [in]  Parameter value specifying the point on the circular curve as a Double 
              value in radians. 
    \param secondDeriv [out] Reference to a variable in which this method must save the second   
                   derivative as three-dimensional vector instance.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getSecondDeriv( double param, OdGeVector3d& secondDeriv ) const;


  /** \details
    Returns the area calculated for the closed figure formed by the circular arc and 
    a line passed from the end point to the start point.

    \param vArea [out]  Reference to a variable in which this method must save the area
              as a Double value.

    \sa
    <link db_circular_arc_sample, Example of Working with the Circular Arc>

    \sa
    <link db_circular_arc_compute, Computed Circular Arc Properties>
  */
  virtual OdResult getArea( double& vArea ) const;


  TD_USING(OdDbCurve::getFirstDeriv);
  TD_USING(OdDbCurve::getSecondDeriv);
  /*
     OdDbArc(const OdGePoint3d& center, double radius,
             double startAngle, double endAngle);
     OdDbArc(const OdGePoint3d& center, const OdGeVector3d& normal,
             double radius, double startAngle, double endAngle);
  */

  virtual OdResult getOdGeCurve(OdGeCurve3d*& pGeCurve, const OdGeTol& tol = OdGeContext::gTol) const;
  virtual OdResult setFromOdGeCurve(const OdGeCurve3d& geCurve, OdGeVector3d *normal = NULL, const OdGeTol& tol = OdGeContext::gTol);
  virtual OdResult reverseCurve();
  virtual OdDbEntity* subSubentPtr(const OdDbFullSubentPath& /* path */) const;

  double    totalAngle() const;
  TOOLKIT_EXPORT double    length() const;
};

/** \details
  The typified smart pointer for the circular arc object (Circular Arc entity). This  
  template class is specialization of the OdSmartPtr class for the OdDbArc class.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbArc> OdDbArcPtr;

#include "TD_PackPop.h"

#endif

