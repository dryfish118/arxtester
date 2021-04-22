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




#ifndef OD_WIPEOUT_H
#define OD_WIPEOUT_H

#ifdef _DBWIPEOBJ_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP
#endif

#include "TD_PackPush.h"

#include "DbRasterImage.h"
#include "DbWipeoutVariables.h"

#define WIPEOUTOBJSERVICE	/*NOXLATE*/ACRX_T("WipeOut")

/** \details
  This class represents wipeout entities in an OdDbDatabase instance.
  Corresponding C++ library: WipeOut
  <group OdDb_Classes>
*/
class WIPEOUT_EXPORT OdDbWipeout : public OdDbRasterImage
{
public:
  ODDB_DECLARE_MEMBERS(OdDbWipeout);

  OdDbWipeout();

  /** \details
      Sets orientation and boundary for this Wipeout entity (DXF 10, 11, 12, 71, 14, 24).
      \param boundary [in]  Array of planar WCS points.
  */
  virtual void setBoundary(const OdGePoint3dArray& boundary);

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;

  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;

  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler) ODRX_OVERRIDE;

  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  virtual OdBool subWorldDraw(OdGiWorldDraw* pWd) ODRX_OVERRIDE;

  virtual OdResult subGetTransformedCopy(const OdGeMatrix3d& mat, OdDbEntity*& pCopy) const ODRX_OVERRIDE;

#ifdef ODARXDEF
  OdResult append(OdDbObjectId& id);
#endif

  OdBool  frame() const;
  OdBool  setFrame(OdBool bFrame);

  virtual OdResult subGetClassID(CLSID* pClsid) const ODRX_OVERRIDE;

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits);

  static OdResult createImageDefinition();

  static OdResult fitPointsToImage(OdGePoint2dArray& pointArray, OdGePoint2d& minPoint, double& scale, OdBool bFlipY = kFalse);
};
 
/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbWipeout object pointers.
*/
typedef OdSmartPtr<OdDbWipeout> OdDbWipeoutPtr;

#include "TD_PackPop.h"

#endif  // OD_WIPEOUT_H

