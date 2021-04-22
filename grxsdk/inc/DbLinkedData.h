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



#ifndef OD_DBLINKEDDATA_H
#define OD_DBLINKEDDATA_H

#include "TD_PackPush.h"

#include "DbObject.h"

	/** \details
    Work-in-progress. This class represents LinkedData objects in an OdDbDatabase instance.


	<group OdDb_Classes> 
	*/
class DBENT_EXPORT OdDbLinkedData : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbLinkedData);

  OdDbLinkedData();

  virtual OdResult clear(void);
  virtual bool isEmpty(void) const;

  virtual const OdChar* name (void) const;
  virtual OdResult setName(const OdChar* name);
  virtual const OdChar* description(void) const;
  virtual OdResult setDescription(const OdChar* description);

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdDbLinkedData> OdDbLinkedDataPtr;

#include "TD_PackPop.h"

#endif // OD_DBLINKEDDATA_H
