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

#ifndef __IMGVARS_H
#define __IMGVARS_H /*!DOM*/

#include "TD_PackPush.h"

class OdDbRasterVariables;

#include "DbRasterImageDef.h"
#include "OdString.h"

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbRasterVariables object pointers.
*/
typedef OdSmartPtr<OdDbRasterVariables> OdDbRasterVariablesPtr;

/** \details
    This class represents RasterVariables objects in an OdDbDatabase instance.
    Corresponding C++ library: ISM
    
   
    \remarks
    RasterVariables objects contain settings applicable to raster images.   
    A single instance of this class is stored with every OdDbDatabase that contains raster images.
    
    <group OdDb_Classes>
*/
class ISM_EXPORT OdDbRasterVariables : public OdDbObject
{
public:  
  
  ODDB_DECLARE_MEMBERS(OdDbRasterVariables);
  static OdDbRasterVariables* create();
  OdDbRasterVariables();
  
  static ClassVersion classVersion();

  enum FrameSettings
  {
    kImageFrameInvalid  = -1, // Invalid
    kImageFrameOff      = 0,  // Frame is off
    kImageFrameAbove    = 1,  // Frame is above the image
    kImageFrameBelow    = 2,  // Frame is below the image
    // New in R24 (AC24 support)
    kImageFrameOnNoPlot = 3   // Frame is above the image, but not drawn during plotting
  };

  enum ImageQuality
  {
    kImageQualityInvalid  = -1, // Invalid
    kImageQualityDraft    = 0,  // Draft quality
    kImageQualityHigh     = 1   // High quality
  };
    
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields
    (OdDbDxfFiler* pFiler) const;
  
  /** \details
    Returns the image frame display (DXF 70).
    
    \remarks
    imageFrame() returns one of the following:
    
    <table>
    Name                  Value   Description
    kImageFrameInvalid    -1      Invalid
    kImageFrameOff        0       Frame is off
    kImageFrameAbove      1       Frame is above the image
    kImageFrameBelow      2       Frame is below the image
    kImageFrameOnNoPlot   3       Frame is above the image, but not drawn during plotting
    </table>
  */
  virtual FrameSettings imageFrame() const;

  /** \details
    Sets the image frame display (DXF 70).
    
    \param imageFrame [in]  Image frame display.

    \remarks
    imageFrame must be one of the following:
    
    <table>
    Name                  Value   Description
    kImageFrameOff        0       Frame is off
    kImageFrameAbove      1       Frame is above the image
    kImageFrameBelow      2       Frame is below the image
    kImageFrameOnNoPlot   3       Frame is above the image, but not drawn during plotting
    </table>
  */
  virtual OdResult setImageFrame( 
    FrameSettings imageFrame );

  /** \details
    Returns the image display quality (DXF 71).

    \remarks
    imageQuality() returns one of the following:
    
    <table>
    Name                    Value   Description
    kImageQualityInvalid    -1      Invalid
    kImageQualityDraft       0      Draft quality
    kImageQualityHigh        1      High quality
    </table>
  */
  virtual ImageQuality imageQuality() const;

  /** \details
    Sets the image display quality (DXF 71).
    \param imageQuality [in]  Image Quality.

    \remarks
    imageQuality must be one of the following:
    
    <table>
    Name                    Value   Description
    kImageQualityInvalid    -1      Invalid
    kImageQualityDraft       0      Draft quality
    kImageQualityHigh        1      High quality
    </table>
  */
  virtual OdResult setImageQuality(
    ImageQuality imageQuality );
  
  /** \details
    Returns the real-world units corresponding to drawing units (DXF 72).

    \remarks
    units() returns one of the following:
    
    <table>
    Name                                 Value
    OdDbRasterImageDef::kNone            0 
    OdDbRasterImageDef::kMillimeter      1 
    OdDbRasterImageDef::kCentimeter      2 
    OdDbRasterImageDef::kMeter           3 
    OdDbRasterImageDef::kKilometer       4 
    OdDbRasterImageDef::kInch            5 
    OdDbRasterImageDef::kFoot            6 
    OdDbRasterImageDef::kYard            7 
    OdDbRasterImageDef::kMile            8 
    OdDbRasterImageDef::kMicroinches     9 
    OdDbRasterImageDef::kMils            10 
    OdDbRasterImageDef::kAngstroms       11 
    OdDbRasterImageDef::kNanometers      12 
    OdDbRasterImageDef::kMicrons         13 
    OdDbRasterImageDef::kDecimeters      14 
    OdDbRasterImageDef::kDekameters      15 
    OdDbRasterImageDef::kHectometers     16 
    OdDbRasterImageDef::kGigameters      17 
    OdDbRasterImageDef::kAstronomical    18 
    OdDbRasterImageDef::kLightYears      19 
    OdDbRasterImageDef::kParsecs         20
    </table>
  */
  virtual OdDbRasterImageDef::Units userScale() const;

  /** \details
    Specifies the real-world units corresponding to drawing units  (DXF 72).
    
    \param units [in]  Real-world units.
    
    \remarks
    units must be one of the following:
    
    <table>
    Name                                 Value
    OdDbRasterImageDef::kNone            0 
    OdDbRasterImageDef::kMillimeter      1 
    OdDbRasterImageDef::kCentimeter      2 
    OdDbRasterImageDef::kMeter           3 
    OdDbRasterImageDef::kKilometer       4 
    OdDbRasterImageDef::kInch            5 
    OdDbRasterImageDef::kFoot            6 
    OdDbRasterImageDef::kYard            7 
    OdDbRasterImageDef::kMile            8 
    OdDbRasterImageDef::kMicroinches     9 
    OdDbRasterImageDef::kMils            10 
    OdDbRasterImageDef::kAngstroms       11 
    OdDbRasterImageDef::kNanometers      12 
    OdDbRasterImageDef::kMicrons         13 
    OdDbRasterImageDef::kDecimeters      14 
    OdDbRasterImageDef::kDekameters      15 
    OdDbRasterImageDef::kHectometers     16 
    OdDbRasterImageDef::kGigameters      17 
    OdDbRasterImageDef::kAstronomical    18 
    OdDbRasterImageDef::kLightYears      19 
    OdDbRasterImageDef::kParsecs         20
    </table>
  */
  virtual OdResult setUserScale(
    OdDbRasterImageDef::Units units);
  
  /** \details
    Opens the RasterVariables object in the specified database. Creates a RasterVariables object if one does not exist.
    
    \param openMode [in]  Mode in which to open the RasterVariables object.
    \param pDb [in]  Pointer to the database containg the RasterVariables object.
    \returns
    Returns a SmartPointer to the RasterVariables object.
   
  */
  static OdDbRasterVariablesPtr openRasterVariables(
    OdDbDatabase* pDb,
    OdDb::OpenMode openMode = OdDb::kForRead, bool bCreateIfNotExist = true);
  static OdDbRasterVariables* openRasterVariables(
    OdDb::OpenMode mode,
    OdDbDatabase* pDatabase = 0);
};


inline OdDbRasterVariablesPtr OdDbRasterVariables::openRasterVariables(OdDbDatabase* pDatabase, OdDb::OpenMode mode, bool bCreateIfNotExist) {
  OdDbRasterVariablesPtr pRastVars;
  ODA_ASSERT(pDatabase);
  if (pDatabase) {
    OdString strAcDbRasterVariables(L"AcDbRasterVariables");
    OdDbDictionaryPtr pRootDict = pDatabase->getNamedObjectsDictionaryId().openObject();
    OdResult res;
    pRastVars = ::odrxCastByClassName<OdDbRasterVariables>(pRootDict->getAt(ACAD_IMAGE_VARS, &res).openObject(mode), strAcDbRasterVariables);
    if (res == eKeyNotFound && bCreateIfNotExist)
    {
      pRootDict->upgradeOpen();
      pRastVars = ::odrxSafeCreateObject<OdDbRasterVariables>(strAcDbRasterVariables);

      OdDbRasterImageDef::Units units;
      switch (pDatabase->getINSUNITS()) {
      default:
        //case OdDb::kUnitsUndefined:
        units = OdDbRasterImageDef::kNone;
        break;
      case OdDb::kUnitsInches:
        units = OdDbRasterImageDef::kInch;
        break;
      case OdDb::kUnitsFeet:
        units = OdDbRasterImageDef::kFoot;
        break;
      case OdDb::kUnitsMiles:
        units = OdDbRasterImageDef::kMile;
        break;
      case OdDb::kUnitsMillimeters:
        units = OdDbRasterImageDef::kMillimeter;
        break;
      case OdDb::kUnitsCentimeters:
        units = OdDbRasterImageDef::kCentimeter;
        break;
      case OdDb::kUnitsMeters:
        units = OdDbRasterImageDef::kMeter;
        break;
      case OdDb::kUnitsKilometers:
        units = OdDbRasterImageDef::kKilometer;
        break;
      case OdDb::kUnitsMicroinches:
        units = OdDbRasterImageDef::kMicroinches;
        break;
      case OdDb::kUnitsMils:
        units = OdDbRasterImageDef::kMils;
        break;
      case OdDb::kUnitsYards:
        units = OdDbRasterImageDef::kYard;
        break;
      case OdDb::kUnitsAngstroms:
        units = OdDbRasterImageDef::kAngstroms;
        break;
      case OdDb::kUnitsNanometers:
        units = OdDbRasterImageDef::kNanometers;
        break;
      case OdDb::kUnitsMicrons:
        units = OdDbRasterImageDef::kMicrons;
        break;
      case OdDb::kUnitsDecimeters:
        units = OdDbRasterImageDef::kDecimeters;
        break;
      case OdDb::kUnitsDekameters:
        units = OdDbRasterImageDef::kDekameters;
        break;
      case OdDb::kUnitsHectometers:
        units = OdDbRasterImageDef::kHectometers;
        break;
      case OdDb::kUnitsGigameters:
        units = OdDbRasterImageDef::kGigameters;
        break;
      case OdDb::kUnitsAstronomical:
        units = OdDbRasterImageDef::kAstronomical;
        break;
      case OdDb::kUnitsLightYears:
        units = OdDbRasterImageDef::kLightYears;
        break;
      case OdDb::kUnitsParsecs:
        units = OdDbRasterImageDef::kParsecs;
        break;
      }
      pRastVars->setUserScale(units);
      pRootDict->setAt(ACAD_IMAGE_VARS, pRastVars);
      if (mode == OdDb::kForRead) 
      {
        pRastVars->downgradeOpen();
      }
    }
  }
  return pRastVars;
}

#include "TD_PackPop.h"

#endif // __IMGVARS_H
