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




#ifndef _ODDBBLOCKTABLERECORD_INCLUDED
#define _ODDBBLOCKTABLERECORD_INCLUDED

#include "TD_PackPush.h"

#include "DbSymbolTableRecord.h"
#include "DbObjectIterator.h"
#include "DbXrefGraph.h"
#include "DbDatabase.h"
#include "Ge/GeMatrix3d.h"
#include "DwgDeclareMembers.h"

class OdDbBlockBegin;
class OdDbBlockEnd;
class OdDbBlockTableRecord;
class OdDbBlockTable;
class OdBinaryData;
class OdDbSortentsTable;
typedef OdSmartPtr<OdDbBlockBegin> OdDbBlockBeginPtr;
typedef OdSmartPtr<OdDbBlockEnd> OdDbBlockEndPtr;
typedef OdSmartPtr<OdDbSortentsTable> OdDbSortentsTablePtr;

class TOOLKIT_EXPORT OdDbBlockTableRecordIterator
{
public:
  virtual ~OdDbBlockTableRecordIterator();

  void     start (bool atBeginning = true, bool skipDeleted = true)
  { if(!mIterator.isNull()) mIterator->start(!atBeginning, skipDeleted); }

  void     step  (bool forward = true, bool skipDeleted = true)
  { if(!mIterator.isNull()) mIterator->step(!forward, skipDeleted); }

  bool     done  () const
  { return ( mIterator.isNull() ? true : mIterator->done() ); }

  OdResult getEntityId (OdDbObjectId& entityId) const;
  OdResult getEntity   (OdDbEntity*& pEntity,
                        OdDb::OpenMode openMode = OdDb::kForRead,
                        bool openErasedEntity = false) const;

  OdResult seek (OdDbObjectId id);
  OdResult seek (const OdDbEntity* pEntity);

  OdDbBlockTableRecord* blockTableRecord() const
  { return mpBlockTabrec; }

protected:
  friend class OdDbBlockTableRecord;
  OdDbBlockTableRecordIterator();

  OdDbBlockTableRecord* mpBlockTabrec;
  OdDbObjectIteratorPtr mIterator;
};

class OdDbBlockReference;
class TOOLKIT_EXPORT OdDbBlockReferenceIdIterator
{
public:
  virtual ~OdDbBlockReferenceIdIterator();

  void     start () { mPos = 0; }
  void     step  () { mPos++; }
  bool     done  () const { return mPos >= mAry.length(); }

  OdResult getBlockReferenceId (OdDbObjectId& id) const;
  OdResult getBlockReference (OdDbBlockReference*& pBlkRef,
                              OdDb::OpenMode openMode = OdDb::kForRead,
                              bool openErasedEntity = false) const;
  OdResult getDatabase (OdDbDatabase*& pDb) const;

  OdResult seek (OdDbObjectId id);

protected:
  friend class OdDbBlockTableRecord;
  OdDbBlockReferenceIdIterator();

  OdSize mPos;
  OdDbObjectIdArray mAry;
};

/** \details
  This class represents Block records in the OdDbBlockTable in an OdDbDatabase
  instance.

  \sa 
  <link Blocks, Overview of Blocks>
  
  <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbBlockTableRecord : public OdDbSymbolTableRecord
{
public:
  //DOM-IGNORE-BEGIN
  DWGMAP_DECLARE_MEMBERS(OdDbBlockTableRecord);
  //DOM-IGNORE-END

  /** \details
    This is the default constructor for objects of the OdDbBlockTableRecord
    class.
  */
  OdDbBlockTableRecord();

  typedef OdDbBlockTable TableType;
  typedef OdBinaryData PreviewIcon;

  OdResult newBlockReferenceIdIterator(OdDbBlockReferenceIdIterator*& pIter) const;

  /** \details
    Appends the specified entity to this Block.

    \param pEntity [in]  Pointer to the entity.

    \returns
    Returns the Object ID of the newly appended entity.
  */
  OdDbObjectId appendOdDbEntity(
    ODSYSDEF,
    OdDbEntity* pEntity);

  OdResult appendOdDbEntity(
    OdDbEntity* pEntity);

  OdResult appendOdDbEntity(
    OdDbObjectId& pOutputId, 
    OdDbEntity* pEntity);

  void removeOdDbEntity(OdDbObjectId &id);

  /** \details
    Returns an Iterator that can be used to traverse this Block.

    \param atBeginning [in]  True to start at the beginning, false to start at the end.
    \param skipDeleted [in]  If and only if true, deleted records are skipped.
    \param sorted      [in]  If and only if true, the iterator will traverse the
                             Block as sorted by this Block's SortentsTable.
    \returns Smart pointer to an iterator object.
  */
  OdDbObjectIteratorPtr newIterator(
    bool atBeginning = true, 
    bool skipDeleted = true, 
    bool sorted = false) const;

  OdResult newIterator(
    OdDbBlockTableRecordIterator*& pIterator,
    bool atBeginning = true,
    bool skipDeleted = true) const;

  /** \details
    Returns the description text associated with this Block (DXF 4).
  */
  OdString comments() const;

  OdResult comments(OdChar*& pString) const;
  OdResult comments(const OdChar*& pString) const;

  /** \details
    Sets the description text associated with this Block (DXF 4).
    \param comments [in]  Description text.
  */
  OdResult setComments(const OdChar * pString);

  /** \details
    Returns the path and filename for the Xref drawing (DXF 1).

    \remarks
    Returns an empty string for non-Xref blocks.
  */
  OdString pathName() const;

  OdResult pathName(OdChar*& pPath) const;
  OdResult pathName(const OdChar*& pPath) const;

  virtual const OdChar * activeFileName() const;

  /** \details
    Sets the path and filename for the Xref drawing (DXF 1).
    \param pathName [in]  Path and filename.
  */
  OdResult setPathName(const OdString& pathName);

  /** \details
    Returns the WCS origin of this Block (DXF 10).
  */
  OdGePoint3d origin() const;

  /** \details
    Sets the WCS origin of this Block (DXF 10).
    \param origin [in]  Origin point.
  */
  OdResult setOrigin(const OdGePoint3d& origin);

  /** \details
    Opens and returns the OdDbBlockBegin object associated with this Block.

    \param openMode [in]  Mode in which to open the object.

    \remarks
    This function allows client applications to access the OdDbBlockBegin object
    to store and retrieve Xdata in a manner compatible with AutoLISP applications.
  */
  OdDbBlockBeginPtr openBlockBegin(OdDb::OpenMode openMode = OdDb::kForRead);

  OdResult openBlockBegin(OdDbBlockBegin*& pBlockBegin, OdDb::OpenMode openMode = OdDb::kForRead);

  /** \details
    Opens and returns the OdDbBlockEnd object associated with this Block.

    \param openMode [in]  Mode in which to open the object.

    \remarks
    This function allows client applications to access the OdDbBlockEnd object
    to store and retrieve Xdata in a manner compatible with AutoLISP applications.
  */
  OdDbBlockEndPtr openBlockEnd(OdDb::OpenMode openMode = OdDb::kForRead);

  OdResult openBlockEnd(OdDbBlockEnd*& pBlockEnd, OdDb::OpenMode openMode = OdDb::kForRead);

  /** \details
    Returns true if and only if this Block contains Attribute definitions.

    \sa
    <link OdDbAttributeDefinition, OdDbAttributeDefinition class>
  */
  bool hasAttributeDefinitions() const;

  /** \details
    Returns true if and only if this Block is anonymous (DXF 70, bit 0x01).
	
	\sa
	<link Blocks, Overview of Blocks>
  */
  bool isAnonymous() const;

  /** \details
    Returns true if and only if this Block is an Xref (DXF 70, bit 0x04).
  */
  bool isFromExternalReference() const;

  /** \details
    Returns true if and only if this Block is an overlaid Xref (DXF 70, bit 0x08).
  */
  bool isFromOverlayReference() const;

  /** \details
    Sets the BlockTableRecord's overlay flag.

    \param bIsOverlay [in]  True to set the record to be an overlay; false to set the record to be an insert type xref.
  */
  OdResult setIsFromOverlayReference(bool bIsOverlay);

  /** \details
    Returns true if and only if this Block represents a layout.
  */
  bool isLayout() const;

  /** \details
    Returns the Object ID of the OdDbLayout associated with this Block.
  */
  OdDbObjectId getLayoutId() const;

  /** \details
    Sets the Object ID of the OdDbLayout associated with this Block.

    \param layoutId [in]  Layout ID.
  */
  OdResult setLayoutId(const OdDbObjectId& layoutId);

  /** \details
    Returns the Object ID's of all OdDbBlockReference entities that reference this Block.

    \param referenceIds [out]  Receives the BlockReference Object ID's.
    \param directOnly    [in]  If true, returns only direct references.
    \param forceValidity [in]  If true, forces the loading of partially loaded drawings.

    \remarks
    If this Block is nested, references to the parent block(s) will be included
    if and only if directOnly is false.
    Older drawings do not explicitly store this information, and hence must be
    completely loaded.

    \sa
    <link OdDbBlockTableRecord::getErasedBlockReferenceIds@OdDbObjectIdArray&, getErasedBlockReferenceIds() method>
  */
  OdResult getBlockReferenceIds(
    OdDbObjectIdArray& referenceIds,
    bool directOnly = true, 
    bool forceValidity = false) const;

  /** \details
    Returns the Object ID's of all erased OdDbBlockReference entities that directly reference this Block.

    \param referenceIds [out]  Receives the BlockReference Object ID's.

    \sa
    <link OdDbBlockTableRecord::getBlockReferenceIds@OdDbObjectIdArray&@bool@bool, getBlockReferenceIds() method>
  */
  OdResult getErasedBlockReferenceIds(OdDbObjectIdArray& referenceIds);

  /** \details
    Returns true if and only if this Xref is unloaded (DXF 71).
  */
  bool isUnloaded() const;

  /** \details
    Sets the unloaded status of this Xref (DXF 71).

    \param isUnloaded [in]  Unloaded status.
  */
  OdResult setIsUnloaded(bool isUnloaded);

  /** \details
    Returns true if the entity has no view-dependent graphics. In another case
    returns false.

    \param pWd [in] Pointer to the OdGiWorldDraw object.
  */
  virtual OdBool subWorldDraw(OdGiWorldDraw* pWd) ODRX_OVERRIDE;
 
  /** \details
    Sets the values of this object's subentity traits, and returns with the
    calling object's subentity traits.

    \param pTraits [in] Pointer to the OdGiDrawableTraits object to be set.

    \remarks
    When overriding subSetAttributes(), you must OR (|) the return value of
    <base class>::subSetAttributes(pTraits) with any flags you add.
    A derived class may not remove flags for any reason.
    The default implementation does nothing but returns kDrawableNone.
    This function can be overridden in custom classes.
  */
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) ODRX_OVERRIDE;

  /** \details
    Reads the .dwg file data of this object.

    \param pFiler [in]  Filer object from which data are read.

    \remarks 
    Returns the filer status.
    This function is called by dwgIn() to allow the object to read its data.
    When overriding this function:
    1) Call assertWriteEnabled().
    2) Call the parent class's dwgInFields(pFiler).
    3) If it returns eOK, continue; otherwise return whatever the parent's dwgInFields(pFiler) returned.
    4) Call the OdDbDwgFiler(pFiler) methods to read each of the object's data items in the order they were written.
    5) Return pFiler->filerStatus().
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;

  /** \details
    Writes the .dwg file data of this object.

    \param pFiler [in]  Pointer to the filer to which data are written.

    \remarks 
    This function is called by dwgIn() to allow the object to write its data.
    When overriding this function:
    1) Call assertReadEnabled().
    2) Call the parent class's dwgOutFields(pFiler).
    3) Call the OdDbDwgFiler(pFiler) methods to write each of the object's data items in the order they were written.
  */
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;

  /** \details
    Reads the DXF data of this object.

    \param pFiler [in]  Pointer to the filer from which data are read.

    \remarks
    Returns the filer status.
    This function is called by dxfIn() to allow the object to read its data.
    When overriding this function:
    1) Call assertWriteEnabled().
    2) Call the parent class's dwgInFields(pFiler).
    3) If it returns eOK, continue; otherwise return whatever the parent's dxfInFields(pFiler) returned.
    4) Call the OdDbDxfFiler(pFiler) methods to read each of the object's data items in the order they were written.
    5) Return pFiler->filerStatus().
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler) ODRX_OVERRIDE;

  /** \details
    Reads the DXF data of this object.

    \param pFiler [in]  Pointer to the filer from which data are read.

    \remarks
    Returns the filer status.
    This function is called by dxfIn() to allow the object to read its data.
    When overriding this function:
    1) Call assertWriteEnabled().
    2) Call the parent class's dwgInFields(pFiler).
    3) If it returns eOK, continue; otherwise return whatever the parent's
       dxfInFields(pFiler) returned.
    4) Call the OdDbDxfFiler(pFiler) methods to read each of the object's data
       items in the order they were written.
    5) Return pFiler->filerStatus().
  */
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  /** \details
    Called as the first operation as this object is being closed, for
    database-resident objects only.

    \remarks
    This function is notified just before the current open operation is to be
    closed, giving this function the ability to perform necessary operations. 
    When overriding this function:
    1) If the OdDbObject's state is incorrect, throw exception.
    2) Call parent class's subClose().
    3) If other actions are required before close, do them.
    The default implementation of this function does nothing. This function can
    be overridden in custom classes.
  */
  virtual OdResult subClose() ODRX_OVERRIDE;

  /** \details
    Overridables.
  */ 
  virtual OdResult subGetClassID(CLSID* pClsid) const ODRX_OVERRIDE;

  /** \details
    Called as the first operation as this object is being *erased* or unerased.

    \param erasing [in] A copy of the erasing argument passed to erase().

    \remarks
    This function is notified just before the current object is to be *erased*,
    giving this function the ability to cancel the erase.
    Returns eOk if and only if erase() is to continue.
    When overriding this function:
    1) If the OdDbObject's state is incorrect, return something other than eOk.
    2) If the parent class's subErase() returns anything other than eOk, immediately return it.
    3) If other actions are required before erase, do them.
    4) Return eOk.
    If you must make changes to this object's state, either make them after
    step 2, or roll them back if step 2 returns other than eOk.
    The default implementation of this function does nothing but return eOk.
    This function can be overridden in custom classes.
  */
  virtual OdResult subErase(bool erasing) ODRX_OVERRIDE;

  /** \details
    Called as the first operation of the handOverTo function.

    \param pNewObject [in] Pointer to the object with which to replace this object in the *database*.

    \remarks
    This function allows custom classes to populate the new object.
    Overriding this function in a child class allows a child instance to be
    notified each time an object is handed over.
    This function is notified just before an object is to be handed over, giving
    this function the ability to cancel the handover.
    When overriding this function:
    1) If the OdDbObject's state is incorrect, throw exception.
    2) Call parent class's subHandover().
    3) If other actions are required before handover, do them.
    The default implementation of this function does nothing.
    This function can be overridden in custom classes.
  */ 
  virtual OdResult subHandOverTo(OdDbObject* pNewObject) ODRX_OVERRIDE;

  /** \details
    Copies the contents of the specified object into this object when possible.  

    \param p [in] Pointer to the source object.

    \remarks
    The source object and this object need not be of the same type. This
    function is meaningful only when implemented by custom classes.
  */
  virtual OdResult copyFrom(const OdRxObject* p) ODRX_OVERRIDE;

  /** \details
    Returns the database that defines this Xref.
    \param includeUnresolved [in]  Include unresolved Xrefs.
  */
  OdDbDatabase* xrefDatabase(bool includeUnresolved = false) const;

  /** \details
    Returns the Xref status of this Block.
    \remarks
    xrefStatus() returns one of the following:

    <table>
    Name                      Value   Description
    OdDb::kXrfNotAnXref       0       Not an Xref
    OdDb::kXrfResolved        1       Resolved
    OdDb::kXrfUnloaded        2       Unloaded
    OdDb::kXrfUnreferenced    3       Unreferenced
    OdDb::kXrfFileNotFound    4       File Not Found
    OdDb::kXrfUnresolved      5       Unresolved
    </table>
  */
  OdDb::XrefStatus xrefStatus() const;

  /** \details
    Returns true if and only if this Block has a preview icon.
  */
  bool hasPreviewIcon() const;

  /** \details
    Returns the preview icon associated with this Block.
    \param previewIcon [out]  Receives the Preview icon.
  */
  OdResult getPreviewIcon(PreviewIcon &previewIcon) const;

  /** \details
    Sets the preview icon associated with this Block.
    \param previewIcon [in]  Preview icon.
  */
  OdResult setPreviewIcon(const PreviewIcon &previewIcon);

  /** \details
    This is subWblockClone, a member of class OdDbBlockTableRecord.
  */
  virtual OdDbObjectPtr subWblockClone(OdDbIdMapping& ownerIdMap, OdDbObject*, bool bPrimary) const ODRX_OVERRIDE;

  /** \details
    Returns the SortentsTable associated with this block.

    \param createIfNotFound [in]  Create the SortentsTable if not found.

    \remarks
    The SortentsTable is opened for write.

    \sa
    OdDbSortentsTable
  */
  OdDbSortentsTablePtr getSortentsTable(bool createIfNotFound = true);

  OdResult getSortentsTable(OdDbSortentsTable*& pSortents,
    OdDb::OpenMode openMode,
    bool createIfNecessary = false);

  /** \details
   Returns a pointer to the OdGiDrawable for the object. If the object doesn't
   have an associated OdGiDrawable object, this function returns NULL.
  */
  OdGiDrawable* drawable();

  virtual OdResult decomposeForSave(OdDb::DwgVersion ver,
                                    OdDbObject*& replaceObj,
                                    OdDbObjectId& replaceId,
                                    OdBool& exchangeXData);
  /** \details
    Returns the WCS geometric extents of this object.

    \param extents [out]  Receives the extents.

    \returns
    Returns eOk if successful, or eInvalidExtents if not.

    \remarks
    The extents are the WCS corner points of a box, aligned with the
    WCS axes, that encloses the 3D extents of this Block.
  */
  virtual OdResult getGeomExtents(OdDbExtents& extents) const;

  /** \details
    This method gets copies of this object, applies parentXform to it and after
    this calculates extents on the resulting object.

    \param extents    [out] WCS extents of the block reference.
    \param parentXform [in] Transformation matrix for block reference's geometry.
  */
  OdResult geomExtentsBestFit(OdDbExtents& extents,
                              const OdGeMatrix3d& parentXform = OdGeMatrix3d::kIdentity) const;

  /** \details
    This method causes the invoked block table record to assume the ownership of
    all the entities listed in the input entitiesToMove array, and provides an
    optimized way of moving entities between block table records.

    \param entitiesToMove [in] Array of entities Object Ids.
  */
  virtual OdResult assumeOwnershipOf(const OdDbObjectIdArray& entitiesToMove);

  /** \details
    This enumeration defines scaling methods for block references.
  */
  enum BlockScaling {
    kAny            = 0, // Block references can be non-uniformly scaled.
    kUniform        = 1  // Block references can be scaled only uniformly.
  };

  /** \details
    Returns the scaling characteristics of references to this Block.

    \remarks
    blockScaling() returns one of the following:

    <table>
    Name        Value    Description
    kAny        0        Block references can be non-uniformly scaled.
    kUniform    1        Block references can be scaled only uniformly.
    </table>
  */
  BlockScaling blockScaling() const;

  /** \details
    Sets the scaling characteristics of references to this Block.

    \param blockScaling [in]  Block scaling.

    \remarks
    blockScaling can be one of the following:

    <table>
    Name     Value    Description
    kAny     0        Block references can be non-uniformly scaled.
    kUniform 1        Block references can be scaled only uniformly.
    </table>
  */
  OdResult setBlockScaling(BlockScaling blockScaling);

  /** \details
    Controls if references to this Block can be exploded.
    \param explodable [in]  Explodable.
  */
  OdResult setExplodable(bool explodable);

  /** \details
    Returns true if and only if references to this Block can be exploded.
  */
  bool explodable() const;

  /** \details
    Sets the block insertion units for this Block.
    \param blockInsertUnits [in]  Block insert units.
  */
  OdResult setBlockInsertUnits(OdDb::UnitsValue blockInsertUnits);

  /** \details
    Returns the block insertion units for this Block.
  */
  OdDb::UnitsValue blockInsertUnits() const;

  /** \details
    Notification function called each time an Undo operation is performed. This
    object is using partial Undo.

    \param pFiler [in] A pointer to the *undo* filer with the partial *undo* information.
    \param pClass [in] A pointer to the OdRxClass object for the class that will *handle* the Undo.

    \remarks
    An object indicates it's using the partial *undo* mechanism, if and only if
    it has set autoUndo false in all calls to assertWriteEnabled().
    This member function must know which types of fields to scan, and must stop
    after reading what it needs.
    If the class type specified by pClassObj does not matches the class of this
    object, this member function must call the parent class's applyPartialUndo()
    and return whatever it returns.
    If it does match the class of this object, this member function must use
    pUndoFiler to read the *undo* data, then typically use this object's set()
    method.
  */
  OdResult applyPartialUndo(OdDbDwgFiler* pFiler, OdRxClass* pClass);

  /** \details
    This function is called when a block is set as annotative. All entities in
    the block are stripped of their annotative property. If a block has nested
    blocks, they are exploded to entities.

    \param strippedCount [out] Number of entities in the block that were stripped
                               of their annotative property.
    \param noModify       [in] If true, no modifications to the entities in the
                               block are made, but strippedCount value is
                               computed. This mode can be used to check whether
                               the block contains annotative entities.
    \param scale          [in] If true, scale the entities in the block by the
                               current annotation scale value.
  */
  OdResult postProcessAnnotativeBTR(int& strippedCount, bool noModify = false, bool scale = true);

  /** \details
    Traverses through all block references of this block table record and adds
    annotation data to each of them.

    \param scale [in] If true, set the block references user scale values to the
                      current annotation scale value. If false, set the block
                      references user scale values to 1:1.
  */
  OdResult addAnnoScalestoBlkRefs(bool scale = false);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdDbBlockTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbBlockTableRecord> OdDbBlockTableRecordPtr;

#include "TD_PackPop.h"

#endif
