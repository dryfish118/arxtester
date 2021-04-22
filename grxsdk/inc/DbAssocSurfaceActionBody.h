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

#pragma once

#ifndef OdDbAssocSurfaceActionBody_INCLUDED_
#define OdDbAssocSurfaceActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocParamBasedActionBody.h"
#include "DbGeomRef.h"

#include "TD_PackPush.h"

/** \details
This class represents the base class OdDbAssocSurfaceActionBody for the Assoc surfaces bodies.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT  OdDbAssocSurfaceActionBody : public OdDbAssocParamBasedActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdDbAssocSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
  explicit OdDbAssocSurfaceActionBody(OdDbAssocCreateImpObject createImpObject = kOdDbAssocCreateImpObject);

	/** \details
	This is the notification call of the corresponding evaluate() method
	of the parent class that owns this action body.
	*/
	virtual void evaluateOverride(void);

	enum OdResult setGeometryParam(double newValue, const OdString& paramName, bool assertEnable = true);
	enum OdResult getGeometryParam(double& value, const OdString& paramName) const;

  OdDbObjectId resultingSurfaceDep(bool createIfDoesNotExist, bool isWriteOnlyDependency = true);

  OdDbObjectId resultingSurface() const;

  OdResult setResultingSurface(const OdDbObjectId& surfaceId, bool isWriteOnlyDependency = true);

  virtual bool isSemiAssociativitySatisfiedOverride() const;

  virtual OdResult getGripPoints(
    OdGePoint3dArray& gripPoints,
    OdDbIntArray&     osnapModes,
    OdDbIntArray&     geomIds) const;

  virtual OdResult getGripPoints(
    OdDbGripDataPtrArray& grips,
    const double          curViewUnitSize,
    const int             gripSize,
    const OdGeVector3d&   curViewDir,
    const int             bitflags) const;

  virtual OdResult moveGripPoints(
    const OdDbIntArray& indices,
    const OdGeVector3d& offset);

  virtual OdResult moveGripPoints(
    const OdDbVoidPtrArray& gripAppData,
    const OdGeVector3d&     offset,
    const int               bitflags);

  virtual OdResult moveStretchPoints(
    const OdDbIntArray& indices,
    const OdGeVector3d& offset);

  virtual void gripStatus(const OdDb::GripStat status);

  virtual OdResult getGripEntityUCS(
    const void*   pGripAppData,
    OdGeVector3d& normalVec,
    OdGePoint3d&  origin,
    OdGeVector3d& xAxis) const;

  virtual void list() const;

  bool isSemiAssociative() const;

  static OdResult findActionsThatAffectedTopologicalSubentity(
    const OdDbEntity*  pAsmBasedEntity,
    const OdDbSubentId&,
    OdDbObjectIdArray& actionIds);

  static OdResult getTopologicalSubentitiesForActionsOnEntity(
    const OdDbEntity*                pAsmBasedEntity,
    bool                             alsoUseAdjacentTopology,
    OdDbObjectIdArray&               actionIds,
    OdArray<OdArray<OdDbSubentId> >& actionSubentIds);

  static OdResult getSurfacesDirectlyDependentOnObject(
    const OdDbObject*,
    OdDbObjectIdArray& dependentSurfaceIds);
}; 

/** \details
The typified smart pointer. This template class is specialization of the OdSmartPtr class
for the OdDbAssocSurfaceActionBody class.

\sa
<link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbAssocSurfaceActionBody> OdDbAssocSurfaceActionBodyPtr;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** \details
  <group Contraint_Classes>
  Library: Source code provided.
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdDbAssocPathBasedSurfaceActionBody : public OdDbAssocSurfaceActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdDbAssocPathBasedSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdDbAssocPathBasedSurfaceActionBody(OdDbAssocCreateImpObject createImpObject = kOdDbAssocCreateImpObject) {};

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdDbAssocPathBasedSurfaceActionBody() {};

  OdResult removeAllPathParams();

  OdResult getInputPathParams(OdDbObjectIdArray& pathParamIds) const;

  OdResult getInputPaths(OdArray<OdArray<OdArray<OdDbEdgeRef> > >& edge) const;

  OdResult setInputPaths(const OdArray<OdArray<OdDbEdgeRef> >& edge);


  OdResult setInputPaths(const OdArray<OdDbPathRef>& path);

  OdResult updateInputPath(int pathIndex, const OdDbPathRef& path);

  OdResult removeAllVertexParams();

  OdResult getInputVertexParams(OdDbObjectIdArray& vertexParamIds) const;

  OdResult setInputPoints(const OdArray<OdDbVertexRef>& vertex);

  OdResult getInputPoints(OdArray<OdDbVertexRef>& vertex) const;

  OdResult makeInputPathsDrawOnTopOfResultingSurface() const;
}; 

typedef OdSmartPtr<OdDbAssocPathBasedSurfaceActionBody> OdDbAssocPathBasedSurfaceActionBodyPtr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif

