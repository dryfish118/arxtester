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




#ifndef _OD_DB_ATTRIBUTE_
#define _OD_DB_ATTRIBUTE_

#include "TD_PackPush.h"

#include "DbText.h"
#include "DbMText.h"
#include "DwgDeclareMembers.h"

class OdDbAttributeDefinition;
/** \details
    This class represents Attribute entities in an OdDbDatabase instance.
  

    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbAttribute : public OdDbText
{
public:
  
  DWGMAP_DECLARE_MEMBERS(OdDbAttribute);
  OdDbAttribute();
  OdDbAttribute(
    const OdGePoint3d& position,
    const OdChar*       text,
    const OdChar*       tag,
    OdDbObjectId       style = OdDbObjectId::kNull);
  /** \details
    Returns the tag string of this Attribute entity (DXF 2).
  */
  const OdString tag(ODSYSDEF) const;
  OdChar*  tag() const;

  const OdChar* tagConst() const;

  /** \details
    Sets the tag string of this Attribute entity (DXF 2).
    \param tagString [in]  Tag string.  
  */
  OdResult setTag(
    const OdString& tagString);

  /** \details
    Returns true if and only if this Attribute entity is invisible (DXF 70, bit 0x01).
  */
  virtual bool isInvisible() const;

  /** \details
    Controls the invisibility of this Attribute entity (DXF 70, bit 0x01).

    \param invisible [in]  Controls invisibility.
  */
  OdResult setInvisible(
    bool invisible);

  /** \details
    Returns true if and only if this Attribute entity is constant (DXF 70, bit 0x02).
  */
  bool isConstant() const;

  /** \details
    Returns true if and only if this Attribute entity is verifiable (DXF 70, bit 0x04).
  */
  bool isVerifiable() const;

  /** \details
    Returns true if and only if this Attribute entity is preset (DXF 70, bit 0x08).
  */
  bool isPreset() const;

  /** \details
    Returns the field length of this Attribute entity (DXF 73).
  */
  OdUInt16 fieldLength() const;

  /** \details
    Sets the field length of this Attribute entity (DXF 73).
    \param fieldLength [in]  Field length.
  */
  OdResult setFieldLength(
    OdUInt16 fieldLength);

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

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  virtual OdBool subWorldDraw(OdGiWorldDraw* pWd);
  virtual void subViewportDraw(OdGiViewportDraw* pVd);

  /** \details
    Applies the settings from the specified attribute definition,
    then applies the specified block transformation matrix to
    to this Attribute entity.
    
    \param blkXform [in]  Block transformation matrix.
    
    \remarks
    Equivalent to the ATTREDEF and INSERT commands.
    
    blkXform is the transformation matrix returned by the OdDbBlockReference::blockTransform() function
    of the OdDbBlockReference that will own this attribute.
  */
  OdResult setAttributeFromBlock(
    const OdGeMatrix3d& blkXform);

  /** \details
    Applies the settings from the specified attribute definition,
    then applies the specified block transformation matrix to
    to this Attribute entity.
    
    \param pAttDef [in]  Pointer to the attribute definition entity.
    \param blkXform [in]  Block transformation matrix.
    
    \remarks
    Equivalent to the ATTREDEF and INSERT commands.
    
    blkXform is the transformation matrix returned by the OdDbBlockReference::blockTransform() function
    of the OdDbBlockReference that will own this attribute.
  */ 
  virtual OdResult setAttributeFromBlock(
    const OdDbAttributeDefinition* pAttDef, 
    const OdGeMatrix3d& blkXform);
  
  /** \details
    Returns true if and only if the position of this Attribute entity is 
    fixed relative to the block geometry.
  */
  bool lockPositionInBlock() const;
  OdResult setLockPositionInBlock(bool lock);

  // multiline attribute support
  bool isMTextAttribute() const;
  OdDbMText* getMTextAttribute() const;

  const OdDbMText* getMTextAttributeConst() const;

  OdResult setMTextAttribute(OdDbMText*);
  TOOLKIT_EXPORT OdResult setMTextAttributeConst(const OdDbMText *);
  OdResult convertIntoMTextAttribute (bool val = true);
  OdResult updateMTextAttribute();
  bool isReallyLocked() const;
  virtual OdResult subClose() ODRX_OVERRIDE;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbAttribute object pointers.
*/
typedef OdSmartPtr<OdDbAttribute> OdDbAttributePtr;

#include "TD_PackPop.h"

#endif
