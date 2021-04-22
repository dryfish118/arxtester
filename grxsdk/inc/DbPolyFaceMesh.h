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




#ifndef _OD_DB_POLYFACE_MESH_
#define _OD_DB_POLYFACE_MESH_

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DbObjectIterator.h"
#include "DwgDeclareMembers.h"

class OdDbPolyFaceMeshVertex;
class OdDbSequenceEnd;
class OdDbFaceRecord;
class OdDbVertex;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbPolyFaceMeshVertex object pointers.
*/
typedef OdSmartPtr<OdDbPolyFaceMeshVertex> OdDbPolyFaceMeshVertexPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbSequenceEnd object pointers.
*/
typedef OdSmartPtr<OdDbSequenceEnd> OdDbSequenceEndPtr;

/** \details
    This class represents PolyFaceMesh entities in an OdDbDatabase instance.
  

    \remarks
    A PolyFaceMesh entity consists of a list of PolyFaceMeshVertex (coordinate) vertices 
    and a list of OdDbFaceRecord face records.
    Together they define a set of 3D faces.
    
    \remarks
    Never derive from this class.

    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbPolyFaceMesh : public OdDbEntity
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbPolyFaceMesh);

  OdDbPolyFaceMesh();
  
  /** \details
    Returns the number of vertices in this PolyFaceMesh entity (DXF 71).
  */
  OdInt16 numVertices() const;

  /** \details
    Returns the number of faces in this PolyFaceMesh entity (DXF 72).
  */
  OdInt16 numFaces() const;
  
  /** \details
    Appends the specified face vertex onto this PolyFaceMesh entity.

    \param pVertex [in]  Pointer to the vertex to append.

    \returns
    Returns the Object ID of the appended face vertex.
  */
  OdDbObjectId appendVertex(
	ODSYSDEF,
    OdDbPolyFaceMeshVertex* pVertex);
	
  OdResult appendVertex(OdDbPolyFaceMeshVertex*);
  OdResult appendVertex(OdDbObjectId& objId, OdDbPolyFaceMeshVertex*);
  
  /** \details
    Appends the specified face record onto this PolyFaceMesh entity.

    \param pFaceRecord [in]  Pointer to the face record to append.

    \returns
    Returns the Object ID of the newly appended face record.
  */
  OdDbObjectId appendFaceRecord(
	ODSYSDEF,
    OdDbFaceRecord* pFaceRecord);
  OdResult appendFaceRecord(OdDbFaceRecord*);
  OdResult appendFaceRecord(OdDbObjectId&, OdDbFaceRecord*);
  
  /** \details
    Opens the specified vertex owned by this PolyFaceMesh entity.

    \param subObjId [in]  Object ID of vertex to be opened.
    \param mode [in]  Mode in which the object is being opened.
    \param openErasedOne [in]  If and only if true, erased objects will be opened.
    \returns
    Returns a SmartPointer to the opened object if successful, otherwise a null SmartPointer.
  */
  OdDbPolyFaceMeshVertexPtr openVertex(
    OdDbObjectId subObjId, 
    OdDb::OpenMode mode, 
    bool openErasedOne = false);

  OdResult openVertex(OdDbVertex*&, OdDbObjectId subObjId, OdDb::OpenMode, bool openErasedOne = false);
  /** \details
    Opens the OdDbSequenceEnd entity for this PolyfaceMesh entity.

    \param mode [in]  Mode in which to open the OdDbSequenceEnd entity.

    \returns
    Returns a SmartPointer to the newly opened OdDbSequenceEnd, or a null SmartPointer.

    \remarks
    This method is provided solely for applications that store XData on
    OdDbSequenceEnd entities; this is not recommended. 
  */
  OdDbSequenceEndPtr openSequenceEnd(
    OdDb::OpenMode mode);

  // Gcad(Add)
  OdResult openSequenceEnd(OdDbSequenceEnd*&, OdDb::OpenMode);

 /** \details
    Removes all vertices and faces
*/
  void clear();

  /** \details
    Returns a SmartPointer to an iterator that can be used to traverse the vertices and face records owned 
    by this PolyFaceMesh entity.
  */
  OdDbObjectIteratorPtr vertexIterator(ODSYSDEF) const;

  // Gcad(Add)
#ifdef ODARXDEF
  OdDbObjectIterator*  vertexIterator() const;
#endif

  virtual OdBool subWorldDraw(
    OdGiWorldDraw* pWd);
  
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult dxfOut(
    OdDbDxfFiler* pFiler,
    OdBool allXdFlag = kTrue,
    unsigned char* regAppTable = NULL) const;

  virtual OdResult dxfIn(
    OdDbDxfFiler* pFiler);

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  virtual OdResult dxfInFields_R12(
    OdDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdDbDxfFiler* pFiler) const;

  OdResult subClose();

  virtual OdBool isPlanar() const;
  
  virtual OdResult getPlane(
    OdGePlane& plane, 
    OdDb::Planarity& planarity) const;

  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm);

  OdResult subGetGeomExtents(
    OdDbExtents& extents) const;

  /** \remarks
    Creates and returns a set of OdDbFace entities.
  */
  virtual OdResult subExplode(
    OdDbVoidPtrArray& entitySet) const;

  /** \remarks
    Creates and returns a set of OdDbFace entities.
  */
  virtual OdResult explodeGeometry(OdRxObjectPtrArray& entitySet) const;

  virtual OdResult subGetSubentPathsAtGsMarker(OdDb::SubentType type, OdGsMarker gsMark,
    const OdGePoint3d& pickPoint, const OdGeMatrix3d& xfm,
    int& numPaths, OdDbFullSubentPath*& subentPaths,
    int numInserts = 0,
    OdDbObjectId* pEntAndInsertStack = 0) const;

  virtual OdResult subGetGsMarkersAtSubentPath(const OdDbFullSubentPath& subPath,
    OdGsMarkerArray& gsMarkers) const;

};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbPolyFaceMesh object pointers.
*/
typedef OdSmartPtr<OdDbPolyFaceMesh> OdDbPolyFaceMeshPtr;

#include "TD_PackPop.h"

#endif
