﻿/////////////////////////////////////////////////////////////////////////////// 
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




#ifndef ODDB_DBHELIX_H
#define ODDB_DBHELIX_H

#include "TD_PackPush.h"

#include "DbSpline.h"

/** \details
    <group OdDb_Classes> 

    This class represents Helix entities in an OdDbDatabase instance.

    Corresponding C++ library: TD_Db
*/
class DBENT_EXPORT OdDbHelix : public OdDbSpline
{
public:
  ODDB_DECLARE_MEMBERS(OdDbHelix);

  OdDbHelix();  
  /** 
  Gcad(Add):增加兼容接口	
  */
  virtual ~OdDbHelix();

  enum ConstrainType
  {
    kTurnHeight = 0,
    kTurns      = 1,
    kHeight     = 2
  };

  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);
  
  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;
  
  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);
  
  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  /** \details
    Explodes this entity into a set of simpler entities.  

    \param entitySet [in/out] Receives an array of pointers to the new entities.
    
    \returns
    Returns eOk if successful, or an appropriate error code if not.

    \remarks
    Entities resulting from the explosion are appended to the specified array.
    
    The newly created entities are not database resident.
    
    The default implementation of this function returns eNotApplicable. This function can be
    overridden in custom classes.
  */
  virtual OdResult subExplode(
    OdDbVoidPtrArray& entitySet) const; /* Replace OdRxObjectPtrArray */

  /** \details
    Applies the specified 3D transformation matrix to this entity.

    \param xfm [in]  3D transformation matrix.

    \returns
    Returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm);

  virtual OdResult subClose();

  virtual OdBool subWorldDraw(
    OdGiWorldDraw* pWd);

  // This functions creates the helix geometry based on the values set 
  // in prior function calls. Without calling this function, 
  // no geometry will be visible on the screen. 
  OdResult createHelix();

  // Returns the start point of the axis for the helix.
  virtual OdGePoint3d axisPoint() const;

  // Sets the start point of the axis for the helix.
  // axisPoint Input the 3D point where the axis starts  
  // bMoveStartPoint Input Boolean indicating whether to 
  // relocate the start point by the same offset
  virtual OdResult setAxisPoint(const OdGePoint3d& axisPoint, const bool bMoveStartPoint = true);

  // Returns the start point of the helix
  virtual OdGePoint3d startPoint() const;

  // Sets the start point of the helix 
  virtual OdResult setStartPoint(const OdGePoint3d &startPoint);

  // Vector of the axis of the helix
  virtual OdGeVector3d axisVector() const;

  // Sets the vector for the axis for the helix 
  virtual OdResult setAxisVector(const OdGeVector3d& axisVector);

  // Height of the helix
  virtual double height() const;

  // Sets the height of the helix
  virtual OdResult setHeight(double dHeight);

  // Base radius of the helix
  virtual double baseRadius() const;

  // Sets the base radius of the helix
  virtual OdResult setBaseRadius(double dRadius);

  // Top radius of the helix
  virtual double topRadius() const;

  // Sets the top radius of the helix
  virtual OdResult setTopRadius(double dRadius);

  // Number of turns (revolutions) of the helix
  virtual double turns() const;

  // Sets the number of turns (revolutions)
  virtual OdResult setTurns(double dTurns);

  // Turn height (distance between threads)
  virtual double turnHeight() const;

  // Sets the turn height (distance between threads)
  virtual OdResult setTurnHeight(double dTurnHeight);

  // Returns the twist of the helix (clockwise or counter-clockwise)
  // true means "counter-clockwise"
  virtual OdBool twist() const;

  // Sets the twist of the helix (is counter-clockwise)
  virtual OdResult setTwist(OdBool bTwist);

  // Returns the constrain property of the helix
  virtual ConstrainType constrain() const;

  // Sets the constrain property of the helix
  virtual OdResult setConstrain(ConstrainType constrain);

  // Returns the turn slope angle of the helix
  virtual double turnSlope() const;

  // Returns the total length of the helix
  virtual double totalLength() const;

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  virtual OdResult reverseCurve();
  virtual void subGripStatus(const OdDb::GripStat status);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbHelix object pointers.
*/
typedef OdSmartPtr<OdDbHelix> OdDbHelixPtr;

#include "TD_PackPop.h"

#endif

