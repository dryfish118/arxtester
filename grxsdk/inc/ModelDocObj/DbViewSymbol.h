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

#ifndef OD_VIEWSYMBOL_H
#define OD_VIEWSYMBOL_H

#include "DbEntity.h"
#include "ModelDocObjExports.h"

#include "TD_PackPush.h"

class OdDbImpViewSymbol;
class OdRxSymbolSketch;
class OdDbAssocViewSymbolConstrGrpPE;

/** \details
    This abstract class is the base class for OdDbSectionSymbol and OdDbDetailSymbol classes.

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class ODRX_ABSTRACT MODELDOCOBJ_EXPORT OdDbViewSymbol : public OdDbEntity
{
  //friend class OdDbViewSymbolSystemInternals;
public:
  ODDB_DECLARE_MEMBERS(OdDbViewSymbol);
  virtual ~OdDbViewSymbol();

  /** \details
    Returns an ObjectId of the associated model documentation view style object for this OdDbViewSymbol entity.  
  */
  OdDbObjectId symbolStyleId() const;

  /** \details
    Sets an ObjectId of the associated model documentation view style object for this OdDbViewSymbol entity.

    \param styleId [in]  Id of the view style to be set.
  */
  void setSymbolStyleId(const OdDbObjectId& styleId);

  /** \details
    Returns the scale factor for this OdDbViewSymbol entity.  
  */
  double scale() const;

  /** \details
    Sets the scale factor for this OdDbViewSymbol entity.
    
    \param val [in]  Scale value to be set.
  */
  void setScale(double val);

  /** \details
    Gets the identifier of the view symbol as a string value.
    
    \param sName [in]  Receives the identifier string.

    \returns
    OdResult::eOk value if successful, OdResult::eNotApplicable otherwise. 
  */
  OdResult getIdentifier(OdString& sName) const;
  OdResult getIdentifier(OdChar*& pszName) const;

  /** \details
    Sets the identifier of the view symbol as a string value.
    
    \param sName [in]  The identifier string to be set.

    \returns
    OdResult::eOk value if successful. 
  */
  OdResult setIdentifier(const OdString& sName);

protected:
  // Internal use only methods:
  OdDbObjectId owningViewRep() const;
  void setOwningViewRep(const OdDbObjectId& owner);
  OdResult createDefinition(class OdRxSymbolSketch* pSketchObject);
  OdResult exportSymbolGeometry(OdArray<OdGeCurve3d*>& geomArr, const OdDbObjectId& viewRepId);
  OdResult setSymbolGeometry(const OdDbObjectIdArray& entIds);
  OdResult setSymbolGeometry(const OdArray<OdDbObject*>& entities);
  OdResult updateDefinition();

protected:
  // OdGiDrawable methods :
  virtual OdBool subWorldDraw(OdGiWorldDraw* pWorldDraw);

  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;

  //virtual void audit(OdDbAuditInfo* pAuditInfo);
  //virtual OdResult subErase(bool erasing);
  //virtual void objectClosed(const OdDbObjectId& objectId);
  //virtual OdResult subClose();

  //OdDbEntity methods :
  //virtual void subSetDatabaseDefaults(OdDbDatabase* pDb);
  //virtual OdResult subGetGeomExtents(OdDbExtents& extents) const;
  //virtual OdResult subGetOsnapPoints(OdDb::OsnapMode osnapMode,
  //                                   OdGsMarker gsSelectionMark,
  //                                   const OdGePoint3d& pickPoint,
  //                                   const OdGePoint3d& lastPoint,
  //                                   const OdGeMatrix3d& xWorldToEye,
  //                                   OdGePoint3dArray& snapPoints) const;
  //virtual OdResult subTransformBy(const OdGeMatrix3d& xfm);
  //virtual void subGripStatus(const OdDb::GripStat status);
  //virtual OdResult subGetGripPoints(OdDbGripDataPtrArray& grips,
  //                                  const double curViewUnitSize,
  //                                  const int gripSize,
  //                                  const OdGeVector3d& curViewDir,
  //                                  const int bitFlags) const;
  //virtual OdResult subMoveGripPointsAt(const OdDbVoidPtrArray& grips,
  //                                     const OdGeVector3d& offset,
  //                                     int bitFlags);
  //virtual OdResult subGetClassID(void* pClsid) const;
  //virtual void subList() const;
  //virtual void saveAs(OdGiWorldDraw* pWd, OdDb::DwgVersion ver) const;

protected:
  // Makes OdDbViewSymbol an abstract class.
  OdDbViewSymbol();

//private:
//friend class OdDbAssocViewSymbolConstrGrpPE;
//class OdDbViewSymbolImp* m_pImpl;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewSymbol object pointers.
*/
typedef OdSmartPtr<OdDbViewSymbol> OdDbViewSymbolPtr;

#include "TD_PackPop.h"

#endif // OD_VIEWSYMBOL_H
