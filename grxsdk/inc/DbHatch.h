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

#ifndef OD_DBHATCH_H
#define OD_DBHATCH_H

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "Ge/GePoint2dArray.h"
#include "IntArray.h"
//#include "Ge/GeVoidPointerArray.h"
#include "CmColorArray.h"
#include "HatchPattern.h"
#include "DwgDeclareMembers.h"
#include "DbRegion.h"
#include "UInt16Array.h"

#define HATCH_PATTERN_NAME_LENGTH 35
#define GRADIENT_PATTERN_NAME_LENGTH    32
#define GRADIENT_COLOR_NAME_LENGTH    256

/** \details
    This template class is a specialization of the OdArray class for OdGeCurve2d object pointers.
*/
typedef OdArray<OdGeCurve2d*> EdgeArray;


/** \details
    This class represents Hatch entities in an OdDbDatabase instance.

    
    \remarks
    
    Loops must be closed, simple, and continuous. 
    They must be self-intersecting itself only at their endpoints.
    Their start points and end points must coincide. 
    The outer loops must be appended before all of their inner loops.
    
    The Drawings provides limited validation of the hatch boundary in order to maintain API efficiency
    and performance.
    
    <group OdDb_Classes> 
*/
class DBENT_EXPORT OdDbHatch : public OdDbEntity
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbHatch);

  OdDbHatch();

  enum HatchLoopType
  {
    kDefault             = 0,        // Not yet specified.
    kExternal            = 1,        // Defined by external entities.
    kPolyline            = 2,        // Defined by OdGe polyline.
    kDerived             = 4,        // Derived from a picked point.
    kTextbox             = 8,        // Defined by text.
    kOutermost           = 0x10,     // Outermost loop.
    kNotClosed           = 0x20,     // Open loop.
    kSelfIntersecting    = 0x40,     // Self-intersecting loop.
    kTextIsland          = 0x80,     // Text loop surrounded by an even number of loops.
    kDuplicate           = 0x100,    // Duplicate loop.
    kIsAnnotative        = 0x200,    // The bounding area is an annotative block.
    kDoesNotSupportScale = 0x400,    // The bounding type does not support scaling
    kForceAnnoAllVisible = 0x800,    // Forces all annotatives to be visible
    kOrientToPaper       = 0x1000,   // Orients hatch loop to paper
    kIsAnnotativeBlock   = 0x2000    // Describes if the hatch is an annotative block.
  };

  enum HatchEdgeType
  {
    kNone     = 0,  // Skip this segment.
    kLine     = 1,  // Linear.         
    kCirArc   = 2,  // Circular arc.
    kEllArc   = 3,  // Elliptical arc.
    kSpline   = 4   // Spline curve.
  };

  enum HatchPatternType
  {
    kUserDefined     = 0, // User-defined hatch.
    kPreDefined      = 1, // Defined in acad.pat and acadiso.pat. 
    kCustomDefined   = 2  // In its own PAT file.
  };

  enum HatchStyle
  {
    kNormal   = 0, // Hatch toggles on each boundary.
    kOuter    = 1, // Hatch turns off after first inner loop.
    kIgnore   = 2  // Hatch ignores inner loop
  };

  enum HatchObjectType 
  {
    kHatchObject      = 0, // Classic hatch
    kGradientObject   = 1  // Color gradient
  };

  enum GradientPatternType 
  {
    kPreDefinedGradient    = 0, // Predefined gradient pattern.
    kUserDefinedGradient   = 1  // User-defined gradient pattern.
  };

  /** \details
    Returns the elevation of this entity in the OCS (DXF 30).
    
    \remarks
    The elevation is the distance from the WCS origin to the plane of this entity.
  */
  double elevation() const;

  /** \details
    Sets the elevation of this entity in the OCS (DXF 30).

    \param elevation [in] Elevation.    

    \remarks
    The elevation is the distance from the WCS origin to the plane of this entity.
  */
  OdResult setElevation(
    double elevation);

   /** \details
    Returns the WCS normal to the plane of this entity (DXF 210).
   */
  OdGeVector3d normal() const;
  
  /** \details
    Sets the WCS normal to the plane of this entity (DXF 210).

    \param normal [in] Normal.
  */
  OdResult setNormal(
    const OdGeVector3d& normal);

  /** \details
    Returns true if and only if this entity is planar.
  */
  virtual OdBool isPlanar() const { return true; }

  /** \details
    Returns the plane that contains the curve and curve's configuration.

    \param plane [out] Plain.

    \param planarity [out] Curve's configuration.

    \remarks
    planarity and plane return values as follows:
    
    <table>
    planarity     Value     Description     plane
    kNonPlanar    0         Non-planar.     Not set.
    kPlanar       1         Planar.         Entity plane.
    kLinear       2         Linear.         Arrbitrary plane containing this entity.
    </table>

    \returns Returns eOk if getting was successful 
      or an appropriate OdResult error code in the other case.
  */
  virtual OdResult getPlane(
    OdGePlane& plane, 
    OdDb::Planarity& planarity) const;

  /** \details
    Returns the number of loops in this hatch (DXF 91).
  */
  int numLoops() const;

  /** \details
    Returns the type of loop at the specified index (DXF 92). 
    
    \param loopIndex [in]  Loop index. 
    
    \remarks
    The loop type consists of a combination of bits from the HatchLoopType enumeration.
  */
  OdInt32 loopTypeAt(
    int loopIndex) const;

   /** \details
    Returns the specified loop from this Hatch entity.

    \param loopIndex [in]  Loop index.
    \param edgePtrs [out]  Receives a set of OdGeCurve2d pointers to the edges that comprise this loop.
    
    \remarks
    Should be called with edgePtrs if the loop is not a polyline loop.
   */
  OdResult getLoopAt(
    int loopIndex, 
    EdgeArray& edgePtrs) const;

  /** \details
    Returns the specified loop from this Hatch entity.

    \param loopIndex [in]  Loop index.
    \param vertices [out]  Receives the vertices that comprise this loop.
    \param bulges [out]  Receives a set of bulges corresponding to the vertices array.
    
    \remarks
    Should be called with vertices and bulges if the loop is a polyline loop.
   */
  OdResult getLoopAt(
    int loopIndex, 
    OdGePoint2dArray& vertices, 
    OdGeDoubleArray& bulges) const;

  OdResult getLoopAt(int loopIndex,
    OdInt32& loopType,
    OdGeVoidPointerArray& edgePtrs,
    OdIntArray&  edgeTypes) const;

  OdResult getLoopAt(int loopIndex,
    OdInt32& loopType,
    OdGePoint2dArray& vertices,
    OdGeDoubleArray& bulges) const;

  /** \details
    Appends a loop onto this Hatch entity.

    \param loopType [in]  Type of loop being appended.
    \param edgePtrs [in]  Array OdGeCurve pointers to the edges that comprise this loop.
    
    \remarks
    
    loopType is one of the following:
    
    <table>
    Name                Value     Description
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>
    
    edgePtrs may contain pointers to only the following objects:

    <table>
    Name
    OdGeLineSeg2d
    OdGeCircArc2d
    OdGeEllipArc2d
    OdGeNurbCurve2d
    </table>

    The hatch will take ownership of the curves passed in.
  */
  OdResult appendLoop(
    OdInt32 loopType,
    EdgeArray& edgePtrs);

  /** \details
    Appends a loop onto this Hatch entity.

    \param loopType [in]  Type of loop being appended.
    \param vertices [in]  The vertices that comprise this loop.
    \param bulges [in]  The bulges corresponding to the vertices array.
    
    \remarks
    
    loopType is one of the following:
    
    <table>
    Name                Value     Description
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>
  */
  OdResult appendLoop(
    OdInt32 loopType,
    const OdGePoint2dArray& vertices,
    const OdGeDoubleArray& bulges);

  /** \details
    Appends a loop onto this Hatch entity.

    \param loopType [in]  Type of loop being appended.
    \param dbObjIds [in]  Array of OdDbEntity Object IDs that comprise the loop.
    
    \remarks
    
    loopType is one of the following:
    
    <table>
    Name                Value     Description
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>
  */
  OdResult appendLoop(
    OdInt32 loopType, 
    const OdDbObjectIdArray& dbObjIds);

  OdResult appendLoop(OdInt32 loopType,
    const OdGeVoidPointerArray& edgePtrs,
    const OdIntArray&  edgeTypes);

  /** \details
    Appends an ordered loop onto this Hatch entity.

    \param loopType [in]  Type of loop being appended.
    \param edgePtrs [in]  Array OdGeCurve pointers to the edges that comprise this loop.
    
    \remarks
    
    loopType is one of the following:
    
    <table>
    Name                Value     Description
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>
    
    edgePtrs may contain pointers to only the following objects:

    <table>
    Name
    OdGeLineSeg2d
    OdGeCircArc2d
    OdGeEllipArc2d
    OdGeNurbCurve2d
    </table>
  */
  void appendOrderedLoop(OdInt32 loopType, EdgeArray& edgePtrs);
 
  /** \details
    Inserts a loop into this Hatch entity on the specified index.

    \param loopIndex [in]  Loop index.
    \param loopType [in]  Type of loop being appended.
    \param edgePtrs [in]  Array OdGeCurve pointers to the edges that comprise this loop.

    \remarks
    loopType is one of the following:
    
    <table>
    Name                Value     Description.
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>

    The hatch will take ownership of the curves passed in.
  */
  OdResult insertLoopAt(
    int loopIndex, 
    OdInt32 loopType,
    EdgeArray& edgePtrs);

  /** \details
    Inserts a loop into this Hatch entity on the specified index.

    \param loopIndex [in]  Loop index.
    \param loopType [in]  Type of loop being appended.
    \param vertices [in]  The vertices that comprise this loop.
    \param bulges [in]  The bulges corresponding to the vertices array.

    \remarks
    loopType is one of the following:
    
    <table>
    Name                Value     Description.
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>

    The hatch will take ownership of the curves passed in.
  */
  OdResult insertLoopAt(
    int loopIndex, 
    OdInt32 loopType,
    const OdGePoint2dArray& vertices,
    const OdGeDoubleArray& bulges);

  /** \details
    Inserts a loop into this Hatch entity on the specified index.

    \param loopIndex [in]  Loop index.
    \param loopType [in]  Type of loop being appended.
    \param dbObjIds [in]  Array of OdDbEntity Object IDs that comprise the loop.

    \remarks
    loopType is one of the following:
    
    <table>
    Name                Value     Description.
    kDefault            0         Not yet specified.
    kExternal           1         Defined by external entities.
    kPolyline           2         Defined by OdGe polyline.
    kDerived            4         Derived from a picked point.
    kTextbox            8         Defined by text.
    kOutermost          0x10      Outermost loop.
    kNotClosed          0x20      Open loop.
    kSelfIntersecting   0x40      Self-intersecting loop.
    kTextIsland         0x80      Text loop surrounded by an even number of loops.
    kDuplicate          0x100     Duplicate loop.
    </table>
  */
  OdResult insertLoopAt(
    int loopIndex, OdInt32 loopType,
    const OdDbObjectIdArray& dbObjIds);

  OdResult insertLoopAt(int loopIndex,
    OdInt32 loopType,
    const OdGeVoidPointerArray& edgePtrs,
    const OdIntArray&  edgeTypes);

  /** \details
    Removes the specified loop from this Hatch entity.

    \param loopIndex [in]  Loop index.
  */
  OdResult removeLoopAt(
    int loopIndex);

  /** \details
    Returns true if and only if this hatch is associative (DXF 71).

    \remarks
    Associative hatch is automatically recalculated 
    when its boundaries are modified.
  */
  bool associative() const;

  /** \details
    Controls the associative flag for this hatch (DXF 71).
    \param isAssociative [in]  Controls the associative flag.

    \remarks
    Associative hatch is automatically recalculated 
    when its boundaries are modified.
  */
  OdResult setAssociative(
    bool isAssociative);

  /** \details
    Returns the Object IDs comprising the specified associative loop in this Hatch entity.

    \param loopIndex [in]  Loop index.
    \param dbObjIds [out]  Receives the boundary Object IDs.
    
    \remarks
    Returns nothing if this Hatch entity is not associative.
  */
  OdResult getAssocObjIdsAt(
    int loopIndex, 
    OdDbObjectIdArray& dbObjIds) const;

  /** \details
    Returns the Object IDs comprising all the associative boundaries in this Hatch entity.

    \param dbObjIds [out]  Receives the boundary Object IDs.

    \remarks
    Returns nothing if this Hatch entity is not associative.
  */
  OdResult getAssocObjIds(
    OdDbObjectIdArray& dbObjIds) const;

  /** \details
    Sets the Object IDs comprising the specified associative loop in this Hatch entity.

    \param loopIndex [in]  Loop index.
    \param dbObjIds [in]  The set of boundary Object ID's that make up the specified loop.

    \remarks
    Adds the Object ID of this hatch to the reactors of the boundary objects.
  */
  void setAssocObjIdsAt(
    int loopIndex, 
    const OdDbObjectIdArray& dbObjIds);

  /** \details
    Removes all Object IDs that are associated with this Hatch entity.
  */
  OdResult removeAssocObjIds();

  /** \details
    Returns the hatch pattern type for this Hatch entity (DXF 76).
    
    \remarks
    
    patternType() returns one of the following:
    
    <table>
    Name              Value
    kUserDefined      0
    kPreDefined       1
    kCustomDefined    2 
    </table>
  */
  OdDbHatch::HatchPatternType patternType() const;

  /** \details
    Returns true if and only if this hatch is solid fill (DXF 70).
  */
  bool isSolidFill() const;

  
  /** \details
      Returns the name of the pattern for this Hatch entity (DXF 2).
  */
  const OdChar * patternName() const;

  /** \details
    Sets the pattern data for this Hatch entity.
    
    \param patType [in]  Pattern type.
    \param patName [in]  Pattern name.
    
    \remarks
    patType must be one of the following:
    
    <table>
    Name              Value
    kUserDefined      0
    kPreDefined       1
    kCustomDefined    2
    </table>
     
    patName is ignored for patType == kUserDefined; appearance is defined by setPatternAngle(),
    setPatternSpace() and setPatternDouble(). 
  */
  OdResult setPattern(
    OdDbHatch::HatchPatternType patType, 
    const OdString& patName);

  /** \details
    Sets the pattern data for this Hatch entity.
    
    \param patType [in]  Pattern type.
    \param patName [in]  Pattern name.
    \param angle [in]  Pattern angle.
    \param scale [in]  Pattern scale.
    \param pat [in]  Pattern definition (as in PAT file)
    \param basePt [in]  Base point.
    
    \remarks
    patType must be one of the following:
    
    <table>
    Name              Value
    kUserDefined      0
    kPreDefined       1
    kCustomDefined    2
    </table>
     
    patName is ignored for patType == kUserDefined; appearance is defined by setPatternAngle(),
    setPatternSpace() and setPatternDouble(). 
  */
  OdResult setPattern(
    OdDbHatch::HatchPatternType patType, 
    const OdString& patName,
    double angle, 
    double scale,
    const OdHatchPattern& pat,
    OdGePoint2d basePt = OdGePoint2d());

  /** \details
    Returns the pattern angle for this Hatch entity (DXF 52).
    
    \remarks
    All angles are expressed in radians.
  */
  double patternAngle() const;

  /** \details
    Sets the pattern angle for this Hatch entity (DXF 52).

    \remarks
    All angles are expressed in radians.
  */
  OdResult setPatternAngle(
    double angle);

  /** \details
    Returns the pattern spacing for this Hatch entity (DXF 41).
    
    \remarks
    Pattern spacing is the distance between parallel lines for kUserDefined hatch.
  */
  double patternSpace() const;

  /** \details
    Sets the pattern spacing for this Hatch entity (DXF 41).

    \param space [in]  Pattern spacing.
    
    \remarks
    Pattern spacing is the distance between parallel lines for kUserDefined hatch.
  */
  OdResult setPatternSpace(
    double space);

  /** \details
    Returns the pattern scale for this Hatch entity (DXF 41).
  */
  double patternScale() const;

  /** \details
    Sets the pattern scale for this Hatch entity (DXF 41).
    
    \param scale [in]  Pattern scale.
  */
  OdResult setPatternScale(
    double scale);

  /** \details
    Returns the pattern double flag for this Hatch entity (DXF 77).
      
    \remarks
    Setting the pattern double flag causes a second set of lines, at 90?to the first, for kUserDefined hatch.
  */
  bool patternDouble() const;

  /** \details
    Sets the pattern double flag for this Hatch entity (DXF 77).

    \param isDouble [in]  Sets the pattern double flag if true, clears it otherwise.
    
    \remarks
    Setting the pattern double flag causes a second set of lines, at 90?to the first, for kUserDefined hatch.
  */
  OdResult setPatternDouble(
    bool isDouble);

 /** \details
    Returns the number of pattern definition lines for this Hatch entity (DXF 78).
 */
  int numPatternDefinitions() const;

  /** \details
    Returns the specified pattern definition line for this Hatch entity.

    \param lineIndex [in]  Line index.
    \param lineAngle [out]  Receives the line angle (DXF 53).
    \param baseX [out]  Receives the line base point X (DXF 43).
    \param baseY [out]  Receives the line base point Y (DXF 44).
    \param offsetX [out]  Receives the line offset X (DXF 45).
    \param offsetY [out]  Receives the line offset Y (DXF 46).
    \param dashes [out]  Receives the line dash lengths (DXF 79, 49).
  */
  OdResult getPatternDefinitionAt(
    int lineIndex, 
    double& lineAngle, 
    double& baseX,
    double& baseY, 
    double& offsetX, 
    double& offsetY,
    OdGeDoubleArray& dashes) const;

  /** \details
    Clear cache and recalculate pattern.

    \remarks
    Use it, if Hatch is not solid and pattern was set or changed

    \param forceReload [in] Recalculate already calculated pattern if true.
  */
  void regeneratePattern(bool forceReload = true);

  /** \details
    Returns the hatch style of this hatch entity (DXF 75).
      
    \remarks
    hatchStyle is one of the following:
    
    <table>
    Name          Value
    kNormal       0
    kOuter        1
    kIgnore       2
    </table>
  */
  OdDbHatch::HatchStyle hatchStyle() const;

  /** \details
    Sets the hatch style of this Hatch entity (DXF 75).
    
    \param hatchStyle [in]  Hatch style.
    
    \remarks
    hatchStyle is one of the following:
    
    <table>
    Name          Value
    kNormal       0
    kOuter        1
    kIgnore       2
    </table>
  */
  OdResult setHatchStyle(
    OdDbHatch::HatchStyle hatchStyle);

  /** \details
    Returns the number of seed points for this Hatch entity (DXF 98).
  */
  int numSeedPoints() const;

  /** \details
    Returns the specified seed point from this Hatch entity (DXF 10).

    \param seedIndex [in]  Seed point index.
  */
  const OdGePoint2d& getSeedPointAt(
    unsigned seedIndex) const;

  /** \details
    Sets the specified seed point for this Hatch entity (DXF 10).

    \param seedIndex [in]  Seed point index.
    \param point [in]  Seed point.
  */
  void setSeedPointAt(
    unsigned seedIndex, 
    OdGePoint2d& point);

  OdResult insertSeedPointAt(unsigned seedIndex, const OdGePoint2d& point);

  OdResult getSeepPointIndex(const int loopIndex, unsigned& seedIndex)const;

  /** \details
    Appends the specified seed point to this Hatch entity (DXF 10).

    \param point [in]  Seed point.
  */
  void appendSeedPoint(const OdGePoint2d& point);

  /** \details
  Remove a specified seed point from this Hatch entity.

  \param seedIndex [in]  Seed point index.
  */
  void removeSeedPointAt(int seedPointIndex);

  /** \details
    Returns the pixel size for intersection and ray casting.
  */
  double pixelSize() const;

  /** \details
    Sets the pixel size for intersection and ray casting.

    \param pixelSize [in]  Pixel size.
  */
  void setPixelSize(
    double pixelSize);

  /** \details
    Reads the .dwg file data of this object.

    \param pFiler [in]  Filer object from which data are read.

    \remarks
    This function is called by dwgIn() to allow the object to read its data. 
    When overriding this function: 
    1) Call assertWriteEnabled(). 
    2) Call the parent class's dwgInFields(pFiler). 
    3) If it returns eOK, continue; otherwise return whatever the parent's dwgInFields(pFiler) returned. 
    4) Call the OdDbDwgFiler(pFiler) methods to read each of the object's data items in the order they were written. 
    5) Return pFiler->filerStatus().

    \returns Returns eOk if reading was successful 
      or an appropriate OdResult error code in the other case.
  */
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object.

    \param pFiler [in]  Pointer to the filer to which data are written.

    \remarks
    This function is called by dwgIn() to allow the object to write its data. 
    When overriding this function: 
    1) Call assertReadEnabled(). 
    2) Call the parent class's dwgOutFields(pFiler). 
    3) Call the OdDbDwgFiler(pFiler) methods to write each of the object's data items in the order they were written.

    \returns Returns eOk if writing was successful 
      or an appropriate OdResult error code in the other case.
  */
  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the DXF data of this object.

    \param pFiler [in] Pointer to the filer from which data are read.

    \remarks
    This function is called by dxfIn() to allow the object to read its data. 
    When overriding this function: 
    1) Call assertWriteEnabled(). 
    2) Call the parent class's dwgInFields(pFiler).
    3) If it returns eOK, continue; otherwise return whatever the parent's dxfInFields(pFiler) returned.
    4) Call the OdDbDxfFiler(pFiler) methods to read each of the object's data items in the order they were written.
    5) Return pFiler->filerStatus().

    \returns Returns eOk if reading was successful 
      or an appropriate OdResult error code in the other case.
  */
  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  /** \details
    Writes the DXF data of this object.

    \param pFiler [in]  Pointer to the filer to which data are to be written.

    \remarks
    This function is called by dxfOut() to allow the object to write its data. 
    When overriding this function: 
    1) Call assertReadEnabled(). 
	2) Call the parent class's dxfOutFields(pFiler). 
	3) Use pFiler to call the OdDbDxfFiler methods to write each of the object's data items in the order they were written.

    \returns Returns eOk if writing was successful 
      or an appropriate OdResult error code in the other case.
  */
  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  virtual OdBool subWorldDraw(
    OdGiWorldDraw* pWd);

  virtual void subViewportDraw(
    OdGiViewportDraw* pWd);

  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm) ODRX_OVERRIDE;

  virtual OdResult subGetTransformedCopy(
    const OdGeMatrix3d& xfm, 
    OdDbEntity*& pCopy) const ODRX_OVERRIDE;

  virtual OdResult TransformBy(
    const OdGePlane& orthoPlane,
    const OdGeVector3d& orthoVec);

  OdDbObjectPtr decomposeForSave(
    OdDb::DwgVersion ver,
    OdDbObjectId& replaceId,
    bool& exchangeXData);

  void subSetDatabaseDefaults(OdDbDatabase *pDb);

  /** \details
    Evaluates the hatch for this Hatch entity.
    \param bUnderestimateNumLines [in]  Underestimates the hatch count before aborting.

    \returns
    Returns eOk if successful, or an appropriate error code if not.
  */
  OdResult evaluateHatch(
    bool bUnderestimateNumLines = false) const;

  /** \details
    Returns the number of hatch lines in this Hatch entity.
    
    \remarks
    Returns zero if the hatch pattern is SOLID. 
  */
  int numHatchLines() const;
  
  /** \details
    Returns the hatch line data for the specified hatch line in this Hatch entity.
      
    \param lineIndex [in]  Line index.
    \param startPoint [out]  Receives the start point.
    \param endPoint [out]  Receives the end point.
  */
  OdResult getHatchLineDataAt(
    int lineIndex, 
    OdGePoint2d& startPoint, 
    OdGePoint2d& endPoint) const;
  
  /** \details
    Returns all the hatch line data for this Hatch entity.
    
    \param startPoints [out]  Receives the start points.
    \param endPoints [out]  Receives the end points.
  */
  OdResult getHatchLinesData(
    OdGePoint2dArray& startPoints, 
    OdGePoint2dArray& endPoints) const;
  
  virtual OdResult subExplode(
    OdDbVoidPtrArray& entitySet) const ODRX_OVERRIDE;

  /** \details
    Notification function called whenever an object is opened for modify OdDb::kForWrite.

    \param pObject [in]  Pointer to the object that is being opened.
  */
  virtual void openedForModify(
    const OdDbObject* pObject);

  virtual void modifiedGraphics(
    const OdDbObject* pObject);

  virtual void modifiedGraphics(
    const OdDbEntity* pEntity);

  virtual OdResult subSwapIdWith(OdDbObjectId otherId,
    OdBool swapXdata = false,
    OdBool swapExtDict = false);

  /* virtual void subSwapIdWith(OdDbObjectId otherId, bool swapXdata = false, bool swapExtDict = false);
  virtual void swapReferences(const OdDbIdMapping& idMap);*/


  /** \details
    Returns the hatch object type of this Hatch entity.
    
    \remarks
    hatchObjectType is one of the following:
    
    <table>
    Name                Value     Description
    kHatchObject        0         Classic hatch
    kGradientObject     1         Color gradient
    </table>
  */
  OdDbHatch::HatchObjectType hatchObjectType() const;

  /** \details
    Sets the hatch object type of this Hatch entity.
    
    \param hatchObjectType [in]  Hatch object type.
    
    \remarks
    hatchObjectType is one of the following:
    
    <table>
    Name                Value     Description
    kHatchObject        0         Classic hatch
    kGradientObject     1         Color gradient
    </table>
  */
  OdResult setHatchObjectType(
    OdDbHatch::HatchObjectType hatchObjectType);
  
  /** \details
    Returns true if and only if this Hatch entity is a color gradient.
  */
  virtual bool isGradient() const;

  /** \details
    Returns true if and only if this Hatch entity is of type kHatchObject.
  */
  virtual bool isHatch() const;
  
  /** \details
    Returns the gradient type of this Hatch entity.
    
    \remarks
    gradientType is one of the following:
    
    <table>
    Name                    Value
    kPreDefinedGradient     0
    kUserDefinedGradient    1
    </table>
  */
  OdDbHatch::GradientPatternType gradientType() const;
  
  /** \details
      Returns the name of the gradient of this Hatch entity.
  */
  OdString gradientName() const;
  
  /** \details
    Sets the gradient type and name for this Hatch entity.
    \param gradientType [in]  Gradient type.
    \param gradientName [in]  Gradient name: SPHERICAL, HEMISPHERICAL, CURVED,
    LINEAR, CYLINDER, INVSPHERICAL, INVHEMISPHERICAL, INVCURVED, INVLINEAR,
    or INVCYLINDER.
    
    \remarks
    gradientType is one of the following:
    
    <table>
    Name                    Value
    kPreDefinedGradient     0
    kUserDefinedGradient    1
    </table>
  */
  OdResult setGradient(
    OdDbHatch::GradientPatternType gradientType, 
    const OdString& gradientName);
  
  /** \details
    Returns the angle of the gradient for this Hatch entity.
      
    \remarks
    All angles are expressed in radians.  
  */
  double gradientAngle() const;

  /** \details
    Returns the angle of the gradient for this Hatch entity.

    \param angle [in]  Gradient angle.
          
    \remarks
    All angles are expressed in radians.  
  */
  OdResult setGradientAngle(double angle);
  
  /** \details
    Returns the colors and interpolation values describing the gradient fill for this Hatch entity.
    
    \param colors [out]  Array of colors defining the gradient.
    \param values [out]  Array of interpolation values for the gradient.
  */
  OdResult getGradientColors(
    OdCmColorArray& colors, 
    OdGeFloatArray& values) const;
  
  OdResult getGradientColors(
	unsigned int& count, 
    OdCmColor*& colors,
    float*& values );
  /** \details
    Returns the colors and interpolation values describing the gradient fill for this Hatch entity.
    
    \param colors [in]  Array of colors defining the gradient.
    \param values [in]  Array of interpolation values for the gradient.

    \remarks
    count must be two for the current implementation.
    
    Throws:
    <table>
    Exception             Cause
    eInvalidInput         count < 2 || values[0] != 0. || values[count-1] != 1.
    eNotImplementedYet    count > 2
    </table>
  */
  OdResult setGradientColors(
    OdUInt32 count, 
    const OdCmColor* colors, 
    const float* values);
  
  /** \details
    Returns the oneColorMode for this Hatch entity.
  */
  bool getGradientOneColorMode() const;

  /** \details
    Controls the oneColorMode for this Hatch entity.
    \param oneColorMode [in]  Controls the oneColorMode.
  */
  OdResult setGradientOneColorMode(
    bool oneColorMode);
  
  /** \details
    Returns the luminance value for this Hatch entity.
    
    \returns
    Returns a value in the range. [0.0 .. 1.0].
    
    If the gradient is using oneColorMode, this function returns 
    the luminance value applied to the first color.
  */
  double getShadeTintValue() const;
  
  /** \details
    Sets the luminance value for this Hatch entity.
    
    \param luminance [in]  Luminace value. [0.0 .. 1.0]
    
    If the gradient is using oneColorMode, this function sets 
    the luminance value applied to the first color.
  */
  OdResult setShadeTintValue(
    double luminance);
  
  OdResult setShadeTintValueAndColor2(float value);

  OdResult  evaluateHatchAllScales(bool bUnderestimateNumLines = false);

  bool lineGenerationEnabled() const;

  bool setLineGenerationEnabled(bool bEnable);

  virtual OdResult swapReferences(const OdDbIdMapping& idMap);

  void removeHatchLines();

  /** \details
    Returns the interpolation value between the 
    default and shifted values of the gradient's definition. 
    
    \remarks
    A gradientShift of 0 indicates a fully unshifted gradient.
    A gradientShift of 1 indicates a fully shifted gradient.
  */
  double gradientShift() const;
  
  /** \details
      Sets the interpolation value between the 
      default and shifted values of the gradient's definition. 

      \param gradientShift [in]  Shift value.
	  
      \remarks
      A gradientShift of 0 indicates a fully unshifted gradient.
      A gradientShift of 1 indicates a fully shifted gradient.
  */
  OdResult setGradientShift(double gradientShift);
  
  /** \details
    Returns the interpolated color of the gradient definition.

    \param value [in]  Interpolation value.
    \param color [out]  Receives the interpolated color.
  */
  OdResult evaluateGradientColorAt(
    double value, 
    OdCmColor& color) const;

  /** \details
    This function appends this object to the specified owner object.

    \param idPair  [in]  ID pair to append.
    \param pOwnerObject  [in]  Pointer to the owner object.
    \param ownerIdMap  [in/out]  Owner's ID map.

    \remarks
    Adds a record to the specified ID map. 
    This function is used internally to subDeepClone() and subWblockClone().
  */
  void appendToOwner(
    OdDbIdPair& idPair, 
    OdDbObject* pOwnerObject , 
    OdDbIdMapping& ownerIdMap);

  OdResult subClose();

  /** \details
    Sets the pattern data for this Hatch entity directly, bypassing OdHatchPatternManager (DXF 76 and DXF 2).
    
    \param patType [in]  Pattern type.
    \param patName [in]  Pattern name.
    \param angle [in]  Pattern angle.
    \param scale [in]  Pattern scale.
    \param pat [in]  Pattern definition (already scaled and rotated)
    
    \remarks
    patType must be one of the following:
    
    <table>
    Name              Value
    kUserDefined      0
    kPreDefined       1
    kCustomDefined    2
    </table>
     
    patName is ignored for patType == kUserDefined; appearance is defined by setPatternAngle(),
    setPatternSpace() and setPatternDouble().
    
    \remarks
    angle and scale are not applied to the pattern.
  */
  void setRawPattern(
    OdDbHatch::HatchPatternType patType, 
    const OdString& patName,
    double angle, 
    double scale,
    const OdHatchPattern& pat);


  /** \details
    Returns the hatch pattern definition for this Hatch entity as it appears in the PAT file.
  */
  OdHatchPattern getPattern() const;


  /** \details
    Returns the hatch pattern definition for this Hatch entity as it appears in the DWG/DXF file.
  */
  OdHatchPattern getRawPattern() const;

  /** \details
    Sets the origin point to the current Hatch object.

    \param pt [in] Origin point.
  */
  OdResult setOriginPoint(const OdGePoint2d& pt);

  /** \details
    Returns the origin point of the current Hatch object as OdGePoint2d object.
  */
  OdGePoint2d originPoint() const;

  virtual OdResult explodeGeometry(OdRxObjectPtrArray& entitySet) const;

  /** \details
    Returns the area of this entity.

    \param area [out]  Receives the area.
    \returns
    Returns eOk if successful, or an appropriate error code if not.
  */
  /**
  Gcad(Add):���Ӽ��ݽӿ�
  //arx 2018
  */
  virtual OdResult getArea(double& area, int segLimit = 0) const;
  /** \details
    Creates a region from the boundary loops of the hatch.

    \returns
    Returns null pointer if the hatch boundary doesn't have closed loops, or self intersection, or modeler can't create it.
  */
  virtual OdDbRegionPtr getRegionArea(ODSYSDEF) const;

  OdDbRegion* getRegionArea(const int segLimit = 0) const;

  /** \details
    Creates an ordered closed loop.

    \param edgePtrs              [out] array of curves contains closed loop curves
    \param dbObjIds              [in]  array of object id from what made edgePtrs
    \param gapTolerance          [in]  bridge the gap that less than a value specified by this tolerance
    \param isEdgeArrayConsistent [in]  is objects id in dbObjIds placed sequentially around the loop

    \returns eOk if edgePtrs contains closed loop curves

    \remarks
    If dbObjIds placed sequentially (and isEdgeArrayConsistent set 'true') result will be correct(if the result is not correct, decrease or increase gapTolerance).
    Otherwise a loop may be cut and formed incorrectly.
  */
  static OdResult makeClosedLoop(EdgeArray& edgePtrs, const OdDbObjectIdArray& dbObjIds, const OdGeTol& gapTolerance, const bool& isEdgeArrayConsistent);

  /** \details
    Mark loop that need recalculate. (If associated entity was changed)

    \param loopIndex              [in]  Loop index.

    \returns eOk if loop with specified index exist

    \remarks
    Hatch loops are recalculated in endTransaction if associated Entity was changed and Hatch protocol extension not implemented.
    Use makeClosedLoop to mark loop and recalculate by OdDbHatch::updateMarkedLoops() if OdDbHatchWatcherPE(or derived) classes implemented.
  */
  OdResult markModifiedLoop(const OdUInt16 loopIndex);

  /** \details
    Mark loop that need recalculate. (If associated entity was changed)

    \param entityHandle [in]  handle of associated entity.

    \returns eOk if related loop was find

    \remarks
    Hatch loops are recalculated in endTransaction if associated Entity was changed and Hatch protocol extension not implemented.
    Use makeClosedLoop to mark loop and recalculate by OdDbHatch::updateMarkedLoops() if OdDbHatchWatcherPE(or derived) classes implemented.
  */
  OdResult markModifiedLoop(const OdDbHandle entityHandle);
  /** \details
    Calculate second hatch gradient color from first color with applied luminance value.

    \param value [in] Luminance value in the range from 0.0 to 1.0.

    \returns eOk if successful.
             eInvalidContext if single color mode is false or gradient colors list is empty or hatch object type not kGradientObject.
             eInvalidInput if the luminance value is out of range.
  */
  OdResult setShadeTintValueAndColor2(double value);

  /** \details
    Remove record about loop from recalculate loop list.

    \param loopIndex [in]  Loop index.

    \returns eOk if loop was erased from recalculate loop list

    \remarks
    Used in group with markModifiedLoop, updateMarkedLoops.
  */
  OdResult unmarkModifiedLoop(const OdUInt16 loopIndex);

  /** \details
    Remove record about loop from recalculate loop list.

    \param entityHandle  [in]  handle of associated entity.

    \returns eOk if related loop was find and erased from recalculate loop list

    \remarks
    Used in group with markModifiedLoop, updateMarkedLoops.
  */
  OdResult unmarkModifiedLoop(const OdDbHandle entityHandle);

  /** \details
    Returns the loops marked as modified.

    \param indicesMarkedLoops [out]  Receives an array of loop index

    \remarks
    Returns an array containing loop indices written with OdDbHatch::markModifiedLoop
  */
  void getMarkedModifiedLoops(OdUInt16Array& indicesMarkedLoops) const;

  /** \details
    Clear recalculate loop list.

    \remarks
    Clear recalculate loop list written with OdDbHatch::markModifiedLoop.
  */
  void clearMarkModifiedLoops();

  /** \details
    Update geometry of the loops previously marked as modified, using associated entities geometry.

    \returns eOk if recalculation is success. 
             eInvalidInput if recalculation is unsuccessful.
             eEmptySet if recalculate loop list is empty (use OdDbHatch::markModifiedLoop to fill this list)

    \remarks
    To mark loops use OdDbHatch::markModifiedLoop.
  */
  OdResult updateMarkedLoops();

  virtual OdResult subGetSubentPathsAtGsMarker(OdDb::SubentType type, OdGsMarker gsMark,
    const OdGePoint3d& pickPoint, const OdGeMatrix3d& xfm,
    int& numPaths, OdDbFullSubentPath*& subentPaths,
    int numInserts = 0,
    OdDbObjectId* pEntAndInsertStack = 0) const;

  virtual OdResult subGetGsMarkersAtSubentPath(const OdDbFullSubentPath& subPath,
    OdGsMarkerArray& gsMarkers) const;

  virtual OdDbEntity* subSubentPtr(const OdDbFullSubentPath& path) const;

  virtual OdResult subDeepClone(OdDbObject* pOwnerObject, OdDbObject*& pClonedObject, OdDbIdMapping& idMap, OdBool isPrimary = true) const;

  /** \details
      Returns the hatch background color.
  */
  OdCmColor backgroundColor() const;

  /** \details
      Sets the hatch background color.
  */
  OdResult setBackgroundColor(const OdCmColor& color);

  void getEcs(OdGeMatrix3d&) const;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbHatch object pointers.
*/
typedef OdSmartPtr<OdDbHatch> OdDbHatchPtr;

DBENT_EXPORT EdgeArray oddbCreateEdgesFromEntity(const OdDbEntity* pEnt, const OdGePlane& hatchPlane, bool bUseExtend = true, bool bBoundary = false);

#include "TD_PackPop.h"

#endif /* OD_DBHATCH_H */