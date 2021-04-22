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




#ifndef _OD_DB_FACERECORD_
#define _OD_DB_FACERECORD_

#include "TD_PackPush.h"

#include "DbVertex.h"
#include "DwgDeclareMembers.h"

/** \details
  This class represents OdDbPolyFaceMesh faces in an OdDbDatabase instance. 

  <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbFaceRecord : public OdDbVertex
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbFaceRecord);

  OdDbFaceRecord();

  /** Gcad(Add):���Ӽ��ݽӿ�
    ע��: OdDbFaceRecord �Ǵ� OdDbEntity ����, �� xxDbFaceRecord ��� xxDbEntity ����.
  */
  OdDbFaceRecord(
    OdInt16 vtx0,
    OdInt16 vtx1,
    OdInt16 vtx2,
    OdInt16 vtx3);

  /** Gcad(Add):���Ӽ��ݽӿ�
  */
  ~OdDbFaceRecord();

  /** \details
    Returns the index of the parent PolyFaceMesh vertex that defines the specified corner (DXF 71-74) of
    this FaceRecord entity.
    
    \param cornerIndex [in]  Corner index. [0 .. 3].

    \remarks
    Vertex indices start at 1.  
    
    Negative indices indicate the following edge is invisible. 
    
    A zero value for cornerIndex == 3 indicates a triangular face.
  */
  OdInt16 getVertexAt(int cornerIndex) const;

  OdResult getVertexAt(int cornerIndex, OdInt16& vertexIndex) const;

  /** \details
    Sets the specified corner (DXF 71-74) of this FaceRecord entity to the specified index of 
    the parent PolyFaceMesh mesh vertex. 
    
    \param cornerIndex [in]  Corner index. [0 .. 3].
    \param vertexIndex [in]  Vertex index.
    
    \remarks
    Vertex indices start at 1.  
    
    Negative indices indicate the following edge is invisible.

    A zero value vertexIndex for cornerIndex == 3 defines a triangular face.
  */
  OdResult setVertexAt(
    int cornerIndex, 
    OdInt16 vertexIndex);
  
  /** \details
    Returns true if and only if the specified edge of this FaceRecord entity is visible (sign of DXF 71-74)

    \param edgeIndex [in]  Edge index. [0 .. 3]
  */
  bool isEdgeVisibleAt(
    int edgeIndex) const;

  OdResult isEdgeVisibleAt(OdUInt16 faceIndex, OdBool& visible) const;
  /** \details
    Sets visible the specified edge of this FaceRecord entity (sign of DXF 71-74)

    \param edgeIndex [in]  Edge index. [0 .. 3]
  */
  OdResult makeEdgeVisibleAt(
    int edgeIndex);

  /** \details
    Sets invisible the specified edge of this FaceRecord entity (sign of DXF 71-74)

    \param edgeIndex [in]  Edge index. [0 .. 3]
  */
  OdResult makeEdgeInvisibleAt(
    int edgeIndex);

  virtual OdResult dxfInFields_R12(
    OdDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult subErase(
    bool erasing);

  /** \details
    Always returns eInvalidExtents.
  */
  virtual OdResult subGetGeomExtents(
    OdDbExtents& extents) const;
};
/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbFaceRecord object pointers.
*/
typedef OdSmartPtr<OdDbFaceRecord> OdDbFaceRecordPtr;

#include "TD_PackPop.h"

#endif