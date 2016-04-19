/*
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2010-08-13 Markus Litz <Markus.Litz@dlr.de>
* Changed: $Id$
*
* Version: $Revision$
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
* @file
* @brief  Implementation of CPACS wing segment handling routines.
*/

#include <math.h>
#include <iostream>
#include <string>
#include <cassert>
#include <cfloat>

#include "CCPACSWingSegment.h"
#include "CCPACSWing.h"
#include "CCPACSWingProfiles.h"
#include "CCPACSGuideCurveProfiles.h"
#include "CCPACSGuideCurveAlgo.h"
#include "CCPACSWingProfileGetPointAlgo.h"
#include "CCPACSConfiguration.h"
#include "CTiglError.h"
#include "tiglcommonfunctions.h"
#include "tigl_config.h"
#include "math/tiglmathfunctions.h"
#include "TixiSaveExt.h"

#include "BRepOffsetAPI_ThruSections.hxx"
#include "TopExp_Explorer.hxx"
#include "TopAbs_ShapeEnum.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shell.hxx"
#include "TopoDS_Wire.hxx"
#include "gp_Trsf.hxx"
#include "gp_Lin.hxx"
#include "Geom_TrimmedCurve.hxx"
#include "GC_MakeSegment.hxx"
#include "GCE2d_MakeSegment.hxx"
#include "GeomAPI_IntCS.hxx"
#include "Geom_Surface.hxx"
#include "Geom_Line.hxx"
#include "gce_MakeLin.hxx"
#include "IntCurvesFace_Intersector.hxx"
#include "Precision.hxx"
#include "TopLoc_Location.hxx"
#include "Poly_Triangulation.hxx"
#include "Poly_Array1OfTriangle.hxx"
#include "BRep_Tool.hxx"
#include "BRep_Builder.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepMesh.hxx"
#include "BRepTools.hxx"
#include "BRepLib.hxx"
#include "BRepBndLib.hxx"
#include "BRepGProp.hxx"
#include "BRepBuilderAPI_MakePolygon.hxx"
#include "Bnd_Box.hxx"
#include "BRepLib_FindSurface.hxx"
#include "ShapeAnalysis_Surface.hxx"
#include "GProp_GProps.hxx"
#include "ShapeFix_Shape.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "GeomAdaptor_Surface.hxx"
#include "GC_MakeLine.hxx"
#include "BRepTools_WireExplorer.hxx"

#include "Geom_BSplineCurve.hxx"
#include "GeomAPI_PointsToBSpline.hxx"
#include "GeomAdaptor_HCurve.hxx"
#include "GeomFill_SimpleBound.hxx"
#include "GeomFill_BSplineCurves.hxx"
#include "GeomFill_FillingStyle.hxx"
#include "Geom_BSplineSurface.hxx"
#include "GeomAPI_ProjectPointOnSurf.hxx"
#include "GeomAPI_ProjectPointOnCurve.hxx"
#include "BRepExtrema_DistShapeShape.hxx"
#include "BRepIntCurveSurface_Inter.hxx"
#include "GCPnts_AbscissaPoint.hxx"
#include "BRepAdaptor_CompCurve.hxx"
#include "BRepTools.hxx"
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>

// [[CAS_AES]] added includes
// [[CAS_AES]] BEGIN
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>
#include "CTiglCommon.h"
// [[CAS_AES]] END

namespace tigl
{

namespace
{
    gp_Pnt transformProfilePoint(const tigl::CTiglTransformation& wingTransform, const tigl::CCPACSWingConnection& connection, const gp_Pnt& pointOnProfile)
    {
        gp_Pnt transformedPoint(pointOnProfile);

        // Do section element transformation on points
        transformedPoint = connection.GetSectionElementTransformation().Transform(transformedPoint);

        // Do section transformations
        transformedPoint = connection.GetSectionTransformation().Transform(transformedPoint);

        // Do positioning transformations
        transformedPoint = connection.GetPositioningTransformation().Transform(transformedPoint);

        transformedPoint = wingTransform.Transform(transformedPoint);

        return transformedPoint;
    }

    TopoDS_Shape transformProfileWire(const tigl::CTiglTransformation& wingTransform, const tigl::CCPACSWingConnection& connection, const TopoDS_Shape& wire)
    {
        TopoDS_Shape transformedWire(wire);

        // Do section element transformation on points
        transformedWire = connection.GetSectionElementTransformation().Transform(transformedWire);

        // Do section transformations
        transformedWire = connection.GetSectionTransformation().Transform(transformedWire);

        // Do positioning transformations
        transformedWire = connection.GetPositioningTransformation().Transform(transformedWire);

        transformedWire = wingTransform.Transform(transformedWire);

        return transformedWire;
    }

    // Set the face traits
    void SetFaceTraits (PNamedShape loft) 
    { 
        // designated names of the faces
        std::vector<std::string> names(5);
        names[0]="Bottom";
        names[1]="Top";
        names[2]="TrailingEdge";
        names[3]="Inside";
        names[4]="Outside";

        // map of faces
        TopTools_IndexedMapOfShape map;
        TopExp::MapShapes(loft->Shape(),   TopAbs_FACE, map);

        // check if number of faces is correct (only valid for ruled surfaces lofts)
        if (map.Extent() != 5 && map.Extent() != 4) {
            LOG(ERROR) << "CCPACSWingSegment: Unable to determine face names in ruled surface loft";
            return;
        }
        // remove trailing edge name if there is no trailing edge
        if (map.Extent() == 4) {
            names.erase(names.begin()+2);
        }
        // set face trait names
        for (int i = 0; i < map.Extent(); i++) {
            CFaceTraits traits = loft->GetFaceTraits(i);
            traits.SetName(names[i].c_str());
            loft->SetFaceTraits(i, traits);
        }
    }
    
    /**
     * @brief getFaceTrimmingEdge Creates an edge in parameter space to trim a face
     * @return 
     */
    TopoDS_Edge getFaceTrimmingEdge(const TopoDS_Face& face, double ustart, double vstart, double uend, double vend)
    {
        Handle_Geom_Surface surf = BRep_Tool::Surface(face);
        Handle(Geom2d_TrimmedCurve) line = GCE2d_MakeSegment(gp_Pnt2d(ustart,vstart), gp_Pnt2d(uend,vend));
    
        BRepBuilderAPI_MakeEdge edgemaker(line, surf);
        TopoDS_Edge edge =  edgemaker.Edge();
        
        // this here is really important
        BRepLib::BuildCurves3d(edge);
        return edge;
    }
}

// Constructor
CCPACSWingSegment::CCPACSWingSegment(CCPACSWing* aWing, int aSegmentIndex)
    : CTiglAbstractSegment(aSegmentIndex)
    , innerConnection(this)
    , outerConnection(this)
    , wing(aWing)
    , surfacesAreValid(false)
    , guideCurvesPresent(false)
{
    Cleanup();
}

// Destructor
CCPACSWingSegment::~CCPACSWingSegment(void)
{
    Cleanup();
}

// Invalidates internal state
void CCPACSWingSegment::Invalidate(void)
{
    CTiglAbstractSegment::Invalidate();
    surfacesAreValid = false;
    guideCurveWires.Clear();
    // [[CAS_AES]] added splittedLoftValid and aeroLoftValid
    splittedLoftValid = false;
    closedAeroLoftValid = false;
    openAeroLoftValid = false;
}

// Cleanup routine
void CCPACSWingSegment::Cleanup(void)
{
    name = "";
    description = "";
    upperShape.Nullify();
    lowerShape.Nullify();
    // [[CAS_AES]] added innerShape, outerShape, trailingEdgeShape
    innerShape.Nullify();
    outerShape.Nullify();
    trailingEdgeShape.Nullify();
    surfacesAreValid = false;
    guideCurvesPresent = false;
    CTiglAbstractSegment::Cleanup();
}

// Update internal segment data
void CCPACSWingSegment::Update(void)
{
    Invalidate();
}

// [[CAS_AES]] Added update method for splitted loft
void CCPACSWingSegment::UpdateSplittedLoft(SegmentType segmentType)
{
    if (splittedLoftValid && segmentType == splittedLoftType)
        return;

    BuildSplittedLoft(segmentType);
    
    splittedLoftValid = true;
    splittedLoftType = segmentType;
}

void CCPACSWingSegment::UpdateAeroLoft(SegmentType segmentType, bool nHalfModel, bool withInnerFace, bool closedTE)
{
    if (closedAeroLoftValid && closedTE)
        return;

    if (openAeroLoftValid && !closedTE)
        return;

    BuildAeroLoft(segmentType, nHalfModel, withInnerFace, closedTE);
}

// Read CPACS segment elements
void CCPACSWingSegment::ReadCPACS(TixiDocumentHandle tixiHandle, const std::string& segmentXPath)
{
    Cleanup();

    std::string elementPath;
    std::string tempString;

    // Get subelement "name"
    char* ptrName = NULL;
    elementPath = segmentXPath + "/name";
    if (tixiGetTextElement(tixiHandle, elementPath.c_str(), &ptrName) == SUCCESS) {
        name = ptrName;
    }

    // Get subelement "description"
    char* ptrDescription = NULL;
    elementPath = segmentXPath + "/description";
    if (tixiGetTextElement(tixiHandle, elementPath.c_str(), &ptrDescription) == SUCCESS) {
        description = ptrDescription;
    }

    // Get attribute "uid"
    char* ptrUID = NULL;
    tempString   = "uID";
    if (tixiGetTextAttribute(tixiHandle, segmentXPath.c_str(), tempString.c_str(), &ptrUID) == SUCCESS) {
        SetUID(ptrUID);
        GetWing().GetConfiguration().GetUIDManager().AddUID(GetUID(), this);
    }

    // Inner connection
    elementPath = segmentXPath + "/fromElementUID";
    innerConnection.ReadCPACS(tixiHandle, elementPath);

    // Outer connection
    elementPath = segmentXPath + "/toElementUID";
    outerConnection.ReadCPACS(tixiHandle, elementPath);

    // Get guide Curves
    if (tixiCheckElement(tixiHandle, (segmentXPath + "/guideCurves").c_str()) == SUCCESS) {
        guideCurvesPresent = true;
        guideCurves.ReadCPACS(tixiHandle, segmentXPath);
    }
    else {
        guideCurvesPresent = false;
    }

    // check that the profiles are consistent
    if (GetNumberOfEdges(GetInnerWire()) !=
        GetNumberOfEdges(GetOuterWire())) {

        throw CTiglError("The wing profiles " + innerConnection.GetProfile().GetUID() +
                         " and " + outerConnection.GetProfile().GetUID() +
                         " in segment " + GetUID() + " are not consistent. "
                         "All profiles must either have a sharp or a blunt trailing edge. "
                         "Mixing different profile types is not allowed.");
    }

    Update();
}

// Write CPACS segment elements
void CCPACSWingSegment::WriteCPACS(TixiDocumentHandle tixiHandle, const std::string& segmentXPath)
{
    // Set the name subelement
    TixiSaveExt::TixiSaveTextElement(tixiHandle, segmentXPath.c_str(), "name", GetName().c_str());
    // Set the name subelement
    TixiSaveExt::TixiSaveTextElement(tixiHandle, segmentXPath.c_str(), "description", description.c_str());
    // Set the uID attribute
    TixiSaveExt::TixiSaveTextAttribute(tixiHandle, segmentXPath.c_str(), "uID", GetUID().c_str());
    
    // Inner connection
    innerConnection.WriteCPACS(tixiHandle, segmentXPath, "fromElementUID");
    // Inner connection
    outerConnection.WriteCPACS(tixiHandle, segmentXPath, "toElementUID");
}

const std::string& CCPACSWingSegment::GetName() const
{
    return name;
}

const std::string& CCPACSWingSegment::GetDescription() const
{
    return description;
}

// Returns the wing this segment belongs to
CCPACSWing& CCPACSWingSegment::GetWing(void) const
{
    return *wing;
}

// helper function to get the inner transformed chord line wire
TopoDS_Wire CCPACSWingSegment::GetInnerWire(void)
{
    CCPACSWingProfile& innerProfile = innerConnection.GetProfile();
    TopoDS_Wire w;
    
    /*
    * The loft algorithm with guide curves does not like splitted
    * wing profiles, we have to give him the unsplitted one.
    * In all other cases, we need the splitted wire to distiguish
    * upper und lower wing surface
    */
#ifdef LOFTALGO_FOUND
    if (guideCurves.GetGuideCurveCount() > 0) {
        w = innerProfile.GetWire();
    }
    else {
        w = innerProfile.GetSplitWire();
    }
#else
    w = innerProfile.GetSplitWire();
#endif

    // [[CAS_AES]] removed wing transformation
    CTiglTransformation identity;
    return TopoDS::Wire(transformProfileWire(identity, innerConnection, w));
}

// helper function to get the outer transformed chord line wire
TopoDS_Wire CCPACSWingSegment::GetOuterWire(void)
{
    CCPACSWingProfile& outerProfile = outerConnection.GetProfile();
    TopoDS_Wire w;
    
    /*
    * The loft algorithm with guide curves does not like splitted
    * wing profiles, we have to give him the unsplitted one.
    * In all other cases, we need the splitted wire to distiguish
    * upper und lower wing surface
    */
#ifdef LOFTALGO_FOUND
    if (guideCurves.GetGuideCurveCount() > 0) {
        w = outerProfile.GetWire();
    }
    else {
        w = outerProfile.GetSplitWire();
    }
#else
    w = outerProfile.GetSplitWire();
#endif

    // [[CAS_AES]] removed wing transformation
    CTiglTransformation identity;
    return TopoDS::Wire(transformProfileWire(identity, outerConnection, w));
}

// [[CAS_AES]] added getter for inner wire of opened profile (containing trailing edge)
TopoDS_Wire CCPACSWingSegment::GetInnerWireOpened(void)
{
    CCPACSWingProfile& innerProfile = innerConnection.GetProfile();
    CTiglTransformation identity;
    return TopoDS::Wire(transformProfileWire(identity, innerConnection, innerProfile.GetWireOpened()));
}

// [[CAS_AES]] added getter for outer wire of opened profile (containing trailing edge)
TopoDS_Wire CCPACSWingSegment::GetOuterWireOpened(void)
{
    CCPACSWingProfile& outerProfile = outerConnection.GetProfile();
    CTiglTransformation identity;
    return TopoDS::Wire(transformProfileWire(identity, outerConnection, outerProfile.GetWireOpened()));
}

// helper function to get the inner closing of the wing segment
// [[CAS_AES]] changed implementation using shape generated in MakeSurfaces
TopoDS_Shape CCPACSWingSegment::GetInnerClosure()
{
    // [[CAS_AES]] BEGIN
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return innerShape;
    // [[CAS_AES]] END
}

// helper function to get the inner closing of the wing segment
// [[CAS_AES]] changed implementation using shape generated in MakeSurfaces
TopoDS_Shape CCPACSWingSegment::GetOuterClosure()
{
    // [[CAS_AES]] BEGIN
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return outerShape;
    // [[CAS_AES]] END
}

// [[CAS_AES]] added getter for loft splitted by spars and ribs
TopoDS_Shape CCPACSWingSegment::GetSplittedLoft(SegmentType segmentType, bool transform)
{
    UpdateSplittedLoft(segmentType);

    // transform into global coordinate system if requested
    if (transform) {
        return GetWing().GetWingTransformation().Transform(splittedLoft);
    }
    else {
        return splittedLoft;
    }
}

// get short name for loft
std::string CCPACSWingSegment::GetShortShapeName () 
{
    unsigned int windex = 0;
    unsigned int wsindex = 0;
    for (int i = 1; i <= wing->GetConfiguration().GetWingCount(); ++i) {
        tigl::CCPACSWing& w = wing->GetConfiguration().GetWing(i);
        if (wing->GetUID() == w.GetUID()) {
            windex = i;
            for (int j = 1; j <= w.GetSegmentCount(); j++) {
                tigl::CTiglAbstractSegment& ws = w.GetSegment(j);
                if (GetUID() == ws.GetUID()) {
                    wsindex = j;
                    std::stringstream shortName;
                    shortName << "W" << windex << "S" << wsindex;
                    return shortName.str();
                }
            }
        }
    }
    return "UNKNOWN";
}

// [[CAS_AES]] added getter for aero loft
TopoDS_Shape CCPACSWingSegment::GetAeroLoft(SegmentType segmentType, bool nHalfModel, bool withInnerFace, bool closedTE)
{
    UpdateAeroLoft(segmentType, nHalfModel, withInnerFace,closedTE);
    if (closedTE) {
        return closedAeroLoft;
    }
    else {
        return openAeroLoft;
    }
}

// Builds the loft between the two segment sections
// [[CAS_AES]] changed implementation to build loft out of faces (for compatibility with component segmen loft)
PNamedShape CCPACSWingSegment::BuildLoft(void)
{
    // [[CAS_AES]] BEGIN
    MakeSurfaces();

    // combine faces of closed profiles to build loft
    TopoDS_Face innerFace = CTiglCommon::getSingleFace(innerShape);
    TopoDS_Face lowerFace = CTiglCommon::getSingleFace(lowerShape);
    TopoDS_Face upperFace = CTiglCommon::getSingleFace(upperShape);
    TopoDS_Face outerFace = CTiglCommon::getSingleFace(outerShape);

    // sew faces and generate a solid
    BRepBuilderAPI_Sewing sewing;
    sewing.Add(innerFace);
    sewing.Add(lowerFace);
    sewing.Add(upperFace);
    sewing.Add(outerFace);
    sewing.Perform();
    TopoDS_Shape shell = sewing.SewedShape();
    TopoDS_Shape loftShape;
    // compute solid out of shell (required for inside check)
    if (shell.ShapeType() == TopAbs_SOLID) {
        loftShape = shell;
    }
    else if (shell.ShapeType() == TopAbs_SHELL) {
        BRepBuilderAPI_MakeSolid ms;
        ms.Add(TopoDS::Shell(shell));
        if (!ms.IsDone()) {
            throw CTiglError("Error building WingSegment shape: generation of solid failed!");
        }
        loftShape = ms.Solid();
    }
    else {
        throw CTiglError("Error building WingSegment shape: result of sewing is no shell or solid!");
    }

    // transform into global coordinate system
    loftShape = GetWing().GetWingTransformation().Transform(loftShape);
    // [[CAS_AES]] END
    
    Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape;
    sfs->Init ( loftShape );
    sfs->Perform();
    loftShape = sfs->Shape();

    // Calculate volume
    GProp_GProps System;
    BRepGProp::VolumeProperties(loftShape, System);
    myVolume = System.Mass();

    // Set Names
    std::string loftName = GetUID();
    std::string loftShortName = GetShortShapeName();
    PNamedShape loft (new CNamedShape(loftShape, loftName.c_str(), loftShortName.c_str()));
    SetFaceTraits(loft);
    return loft;
}

// [[CAS_AES]] Added method for building splitted loft
void CCPACSWingSegment::BuildSplittedLoft(SegmentType segmentType)
{
    MakeSurfaces();

    TopoDS_Shape splittedUpperShape = upperShape;
    TopoDS_Shape splittedLowerShape = lowerShape;

    // STEP 2: build loft including stringer cut lines (combine faces to single loft)
    BRep_Builder compBuilder;
    TopoDS_Compound loftCompound;
    compBuilder.MakeCompound(loftCompound);

    // add inner face if required
    if (segmentType == INNER_SEGMENT || segmentType == INNER_OUTER_SEGMENT) {
        compBuilder.Add(loftCompound, innerShape);
    }
    compBuilder.Add(loftCompound, splittedLowerShape);
    compBuilder.Add(loftCompound, splittedUpperShape);
    // add outer face if required
    if (segmentType == OUTER_SEGMENT || segmentType == INNER_OUTER_SEGMENT) {
        compBuilder.Add(loftCompound, outerShape);
    }

    // STEP 3: build compound containing cut faces for ribs and spars
    // get bounding box of loftCompound in order to identify split geometry which does not cut the segment
    Bnd_Box geomBndBox;
    BRepBndLib::Add(loftCompound, geomBndBox);
    // initialize compound
    TopoDS_Compound splitCompound;
    BRep_Builder builder;
    builder.MakeCompound(splitCompound);

    // STEP 4: cut generated loftCompound with splitCompound containing split faces
    splittedLoft = CTiglCommon::splitShape(loftCompound, splitCompound);

    BRepTools::Clean(splittedLoft);

    Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape;
    sfs->Init ( splittedLoft );
    sfs->Perform();
    splittedLoft = sfs->Shape();
}

// [[CAS_AES]] added method for building aero loft
void CCPACSWingSegment::BuildAeroLoft(SegmentType segmentType, bool nHalfModel, bool withInnerFace, bool closedTE)
{    
    MakeSurfaces();
    
    TopoDS_Shape aeroLoft;

    // build shell from airfoil and loft faces
    TopoDS_Compound comp;
    TopoDS_Shell shell;
    BRep_Builder shellBuilder;
    shellBuilder.MakeShell(shell);
    shellBuilder.MakeCompound(comp);
    
    if (closedTE)
    {
        shellBuilder.Add(comp, upperShape);
        shellBuilder.Add(comp, lowerShape);
    }
    else
    {
//         shellBuilder.Add(shell, CTiglCommon::getSingleFace(upperShapeOpened));
//         shellBuilder.Add(shell, CTiglCommon::getSingleFace(lowerShapeOpened));
//         shellBuilder.Add(shell, CTiglCommon::getSingleFace(trailingEdgeShape));
        shellBuilder.Add(comp, upperShapeOpened);
        shellBuilder.Add(comp, lowerShapeOpened);
        shellBuilder.Add(comp, trailingEdgeShape);
    }

    if (withInnerFace)
    {
        // add inner face if required
        if (segmentType == INNER_SEGMENT || segmentType == INNER_OUTER_SEGMENT) {
            if (closedTE)
                shellBuilder.Add(comp, innerShape);
            else
                shellBuilder.Add(comp, innerShapeOpened);
        }
    }

    // add outer face if required
    if (segmentType == OUTER_SEGMENT || segmentType == INNER_OUTER_SEGMENT) {
            if (closedTE)
                shellBuilder.Add(comp, outerShape);
            else
                shellBuilder.Add(comp, outerShapeOpened);
    }
    
    aeroLoft = comp;
    // transform into global coordinate system
    aeroLoft = GetWing().GetWingTransformation().Transform(aeroLoft);
    
    
    if (nHalfModel)
    {

        TopoDS_Compound halfWing;
        shellBuilder.MakeCompound(halfWing);


        gp_Pnt p1(0., 0., 0.);
        gp_Pnt p2(0., 1., 0.);
        gp_Pnt p3(1., 0., 0.);

        gp_Vec yDir(p1,p2);
        yDir.Normalize();

        gp_Vec xDir(p1,p3);
        xDir.Normalize();

        gp_Ax3 refAx(p1, yDir, xDir);
        gp_Pln cutPlane(refAx);

        TopoDS_Face cutFace = BRepBuilderAPI_MakeFace(cutPlane).Face();

        TopTools_IndexedMapOfShape faceMap;
        faceMap.Clear();
        TopExp::MapShapes(aeroLoft, TopAbs_FACE, faceMap);
        int iNr = faceMap.Extent();

        aeroLoft = CTiglCommon::splitShape(aeroLoft, cutFace);

        TopExp::MapShapes(aeroLoft, TopAbs_FACE, faceMap);

        double u_min = 0.0, u_max = 0.0, v_min = 0.0, v_max = 0.0;

        for (int f = 1; f <= faceMap.Extent(); f++) 
        {
            const TopoDS_Face loftFace = TopoDS::Face(faceMap(f));
            gp_Pnt pnt;
            Handle(Geom_Surface) surf = BRep_Tool::Surface(loftFace);
            BRepTools::UVBounds(loftFace, u_min, u_max, v_min, v_max);
            pnt = surf->Value(u_min + ((u_max - u_min) / 2), v_min + ((v_max - v_min) / 2));

            if (pnt.Y() > 0.)
            {
                shellBuilder.Add(halfWing, loftFace);
            }

        }

        aeroLoft = halfWing;
    }
    
    BRepTools::Clean(aeroLoft);
    
    Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape;
    sfs->Init ( aeroLoft );
    sfs->Perform();
    aeroLoft = sfs->Shape();


    if (closedTE) {
        closedAeroLoft = aeroLoft;
        closedAeroLoftValid = true;
    }
    else {
        openAeroLoft = aeroLoft;
        openAeroLoftValid = true;
    }
}

// Gets the upper point in relative wing coordinates for a given eta and xsi
gp_Pnt CCPACSWingSegment::GetUpperPoint(double eta, double xsi)
{
    return GetPoint(eta, xsi, true);
}

// Gets the lower point in relative wing coordinates for a given eta and xsi
gp_Pnt CCPACSWingSegment::GetLowerPoint(double eta, double xsi)
{
    return GetPoint(eta, xsi, false);
}

// Returns the inner section UID of this segment
const std::string& CCPACSWingSegment::GetInnerSectionUID(void)
{
    return innerConnection.GetSectionUID();
}

// Returns the outer section UID of this segment
const std::string& CCPACSWingSegment::GetOuterSectionUID(void)
{
    return outerConnection.GetSectionUID();
}

// Returns the inner section element UID of this segment
// [[CAS_AES]] added const
const std::string& CCPACSWingSegment::GetInnerSectionElementUID(void) const
{
    return innerConnection.GetSectionElementUID();
}

// Returns the outer section element UID of this segment
// [[CAS_AES]] added const
const std::string& CCPACSWingSegment::GetOuterSectionElementUID(void) const
{
    return outerConnection.GetSectionElementUID();
}

// Returns the inner section index of this segment
int CCPACSWingSegment::GetInnerSectionIndex(void)
{
    return innerConnection.GetSectionIndex();
}

// Returns the outer section index of this segment
int CCPACSWingSegment::GetOuterSectionIndex(void)
{
    return outerConnection.GetSectionIndex();
}

// Returns the inner section element index of this segment
int CCPACSWingSegment::GetInnerSectionElementIndex(void)
{
    return innerConnection.GetSectionElementIndex();
}

// Returns the outer section element index of this segment
int CCPACSWingSegment::GetOuterSectionElementIndex(void)
{
    return outerConnection.GetSectionElementIndex();
}

// Returns the start section element index of this segment
CCPACSWingConnection& CCPACSWingSegment::GetInnerConnection(void)
{
    return( innerConnection );
}

// Returns the end section element index of this segment
CCPACSWingConnection& CCPACSWingSegment::GetOuterConnection(void)
{
    return( outerConnection );
}

// Returns the volume of this segment
double CCPACSWingSegment::GetVolume(void)
{
    Update();
    return( myVolume );
}

// Returns the surface area of this segment
double CCPACSWingSegment::GetSurfaceArea(void)
{
    MakeSurfaces();
    return( mySurfaceArea );
}

void CCPACSWingSegment::etaXsiToUV(bool isFromUpper, double eta, double xsi, double& u, double& v)
{
    gp_Pnt pnt = GetPoint(eta,xsi, isFromUpper);

    Handle_Geom_Surface surf;
    if (isFromUpper) {
        surf = upperSurface;
    }
    else {
        surf = lowerSurface;
    }

    GeomAPI_ProjectPointOnSurf Proj(pnt, surf);
    if (Proj.NbPoints() > 0) {
        Proj.LowerDistanceParameters(u,v);
    }
    else {
        LOG(WARNING) << "Could not project point on wing segment surface in CCPACSWingSegment::etaXsiToUV";

        double umin, umax, vmin, vmax;
        surf->Bounds(umin,umax,vmin, vmax);
        if (isFromUpper) {
            u = umin*(1-xsi) + umax;
            v = vmin*(1-eta) + vmax;
        }
        else {
            u = umin*xsi + umax*(1-xsi);
            v = vmin*eta + vmax*(1-eta);
        }
    }
}

double CCPACSWingSegment::GetSurfaceArea(bool fromUpper, 
                                         double eta1, double xsi1,
                                         double eta2, double xsi2,
                                         double eta3, double xsi3,
                                         double eta4, double xsi4)
{
    MakeSurfaces();
    
    TopoDS_Face face;
    if (fromUpper) {
        face = TopoDS::Face(upperShape);
    }
    else {
        face = TopoDS::Face(lowerShape);
    }
    
    // convert eta xsi coordinates to u,v
    double u1, u2, u3, u4, v1, v2, v3, v4;
    etaXsiToUV(fromUpper, eta1, xsi1, u1, v1);
    etaXsiToUV(fromUpper, eta2, xsi2, u2, v2);
    etaXsiToUV(fromUpper, eta3, xsi3, u3, v3);
    etaXsiToUV(fromUpper, eta4, xsi4, u4, v4);
    
    TopoDS_Edge e1 = getFaceTrimmingEdge(face, u1, v1, u2, v2);
    TopoDS_Edge e2 = getFaceTrimmingEdge(face, u2, v2, u3, v3);
    TopoDS_Edge e3 = getFaceTrimmingEdge(face, u3, v3, u4, v4);
    TopoDS_Edge e4 = getFaceTrimmingEdge(face, u4, v4, u1, v1);
    
    TopoDS_Wire w = BRepBuilderAPI_MakeWire(e1,e2,e3,e4);
    TopoDS_Face f = BRepBuilderAPI_MakeFace(BRep_Tool::Surface(face), w);
    
    // compute the surface area
    GProp_GProps sprops;
    BRepGProp::SurfaceProperties(f, sprops);
    
    return sprops.Mass();
}

// Gets the count of segments connected to the inner section of this segment // TODO can this be optimized instead of iterating over all segments?
int CCPACSWingSegment::GetInnerConnectedSegmentCount(void)
{
    int count = 0;
    for (int i = 1; i <= GetWing().GetSegmentCount(); i++) {
        CCPACSWingSegment& nextSegment = (CCPACSWingSegment&) GetWing().GetSegment(i);
        if (nextSegment.GetSegmentIndex() == mySegmentIndex) {
            continue;
        }
        if (nextSegment.GetInnerSectionUID() == GetInnerSectionUID() ||
            nextSegment.GetOuterSectionUID() == GetInnerSectionUID()) {

            count++;
        }
    }
    return count;
}

// Gets the count of segments connected to the outer section of this segment
int CCPACSWingSegment::GetOuterConnectedSegmentCount(void)
{
    int count = 0;
    for (int i = 1; i <= GetWing().GetSegmentCount(); i++) {
        CCPACSWingSegment& nextSegment = (CCPACSWingSegment&) GetWing().GetSegment(i);
        if (nextSegment.GetSegmentIndex() == mySegmentIndex) {
            continue;
        }
        if (nextSegment.GetInnerSectionUID() == GetOuterSectionUID() ||
            nextSegment.GetOuterSectionUID() == GetOuterSectionUID()) {

            count++;
        }
    }
    return count;
}

// Gets the index (number) of the n-th segment connected to the inner section
// of this segment. n starts at 1.
int CCPACSWingSegment::GetInnerConnectedSegmentIndex(int n)
{
    if (n < 1 || n > GetInnerConnectedSegmentCount()) {
        throw CTiglError("Error: Invalid value for parameter n in CCPACSWingSegment::GetInnerConnectedSegmentIndex", TIGL_INDEX_ERROR);
    }

    for (int i = 1, count = 0; i <= GetWing().GetSegmentCount(); i++) {
        CCPACSWingSegment& nextSegment = (CCPACSWingSegment&) GetWing().GetSegment(i);
        if (nextSegment.GetSegmentIndex() == mySegmentIndex) {
            continue;
        }
        if (nextSegment.GetInnerSectionUID() == GetInnerSectionUID() ||
            nextSegment.GetOuterSectionUID() == GetInnerSectionUID()) {

            if (++count == n) {
                return nextSegment.GetSegmentIndex();
            }
        }
    }

    throw CTiglError("Error: No connected segment found in CCPACSWingSegment::GetInnerConnectedSegmentIndex", TIGL_NOT_FOUND);
}

// Gets the index (number) of the n-th segment connected to the outer section
// of this segment. n starts at 1.
int CCPACSWingSegment::GetOuterConnectedSegmentIndex(int n)
{
    if (n < 1 || n > GetOuterConnectedSegmentCount()) {
        throw CTiglError("Error: Invalid value for parameter n in CCPACSWingSegment::GetOuterConnectedSegmentIndex", TIGL_INDEX_ERROR);
    }

    for (int i = 1, count = 0; i <= GetWing().GetSegmentCount(); i++) {
        CCPACSWingSegment& nextSegment = (CCPACSWingSegment&) GetWing().GetSegment(i);
        if (nextSegment.GetSegmentIndex() == mySegmentIndex) {
            continue;
        }
        if (nextSegment.GetInnerSectionUID() == GetOuterSectionUID() ||
            nextSegment.GetOuterSectionUID() == GetOuterSectionUID()) {

            if (++count == n) {
                return nextSegment.GetSegmentIndex();
            }
        }
    }

    throw CTiglError("Error: No connected segment found in CCPACSWingSegment::GetOuterConnectedSegmentIndex", TIGL_NOT_FOUND);
}

// Returns an upper or lower point on the segment surface in
// dependence of parameters eta and xsi, which range from 0.0 to 1.0.
// For eta = 0.0, xsi = 0.0 point is equal to leading edge on the
// inner wing profile. For eta = 1.0, xsi = 1.0 point is equal to the trailing
// edge on the outer wing profile. If fromUpper is true, a point
// on the upper surface is returned, otherwise from the lower.
gp_Pnt CCPACSWingSegment::GetPoint(double eta, double xsi, bool fromUpper)
{
    if (eta < 0.0 || eta > 1.0) {
        throw CTiglError("Error: Parameter eta not in the range 0.0 <= eta <= 1.0 in CCPACSWingSegment::GetPoint", TIGL_ERROR);
    }

    CCPACSWingProfile& innerProfile = innerConnection.GetProfile();
    CCPACSWingProfile& outerProfile = outerConnection.GetProfile();

    // Compute points on wing profiles for the given xsi
    gp_Pnt innerProfilePoint;
    gp_Pnt outerProfilePoint;
    if (fromUpper == true) {
        innerProfilePoint = innerProfile.GetUpperPoint(xsi);
        outerProfilePoint = outerProfile.GetUpperPoint(xsi);
    }
    else {
        innerProfilePoint = innerProfile.GetLowerPoint(xsi);
        outerProfilePoint = outerProfile.GetLowerPoint(xsi);
    }

    // [[CAS_AES]] removed wing transformation
    CTiglTransformation identity;
    innerProfilePoint = transformProfilePoint(identity, innerConnection, innerProfilePoint);
    outerProfilePoint = transformProfilePoint(identity, outerConnection, outerProfilePoint);

    // Get point on wing segment in dependence of eta by linear interpolation
    Handle(Geom_TrimmedCurve) profileLine = GC_MakeSegment(innerProfilePoint, outerProfilePoint);
    Standard_Real firstParam = profileLine->FirstParameter();
    Standard_Real lastParam  = profileLine->LastParameter();
    Standard_Real param = firstParam + (lastParam - firstParam) * eta;
    gp_Pnt profilePoint;
    profileLine->D0(param, profilePoint);

    return profilePoint;
}

gp_Pnt CCPACSWingSegment::GetPointDirection(double eta, double xsi, double dirx, double diry, double dirz, bool fromUpper, double& deviation)
{
    if (eta < 0.0 || eta > 1.0) {
        throw CTiglError("Error: Parameter eta not in the range 0.0 <= eta <= 1.0 in CCPACSWingSegment::GetPoint", TIGL_ERROR);
    }

    if (dirx*dirx + diry*diry + dirz*dirz < 1e-10) {
        // invalid direction
        throw CTiglError("Direction must not be a null vector in CCPACSWingSegment::GetPointDirection.", TIGL_MATH_ERROR);
    }

    if (!surfacesAreValid) {
        MakeSurfaces();
    }

    CTiglPoint tiglPoint;
    cordSurface.translate(eta, xsi, &tiglPoint);

    gp_Dir direction(dirx, diry, dirz);
    gp_Lin line(tiglPoint.Get_gp_Pnt(), direction);
    
    TopoDS_Shape skin;
    if (fromUpper) {
        skin = wing->GetUpperShape();
    }
    else {
        skin = wing->GetLowerShape();
    }
    
    BRepIntCurveSurface_Inter inter;
    double tol = 1e-6;
    inter.Init(skin, line, tol);
    
    if (inter.More()) {
        deviation = 0.;
        return inter.Pnt();
    }
    else {
        // there is not intersection, lets compute the point next to the line
        BRepExtrema_DistShapeShape extrema;
        extrema.LoadS1(BRepBuilderAPI_MakeEdge(line));
        extrema.LoadS2(skin);
        extrema.Perform();
        
        if (!extrema.IsDone()) {
            throw CTiglError("Could not calculate intersection of line with wing shell in CCPACSWingSegment::GetPointDirection", TIGL_NOT_FOUND);
        }
        
        gp_Pnt p1 = extrema.PointOnShape1(1);
        gp_Pnt p2 = extrema.PointOnShape2(1);

        deviation = p1.Distance(p2);
        return p2;
    }
}

gp_Pnt CCPACSWingSegment::GetChordPoint(double eta, double xsi)
{
    MakeSurfaces();

    CTiglPoint profilePoint; 
    cordSurface.translate(eta,xsi, &profilePoint);

    return profilePoint.Get_gp_Pnt();
}

gp_Pnt CCPACSWingSegment::GetChordNormal(double eta, double xsi)
{
    MakeSurfaces();

    CTiglPoint normal; 
    cordSurface.getNormal(eta,xsi, &normal);

    return normal.Get_gp_Pnt();
}

// TODO: remove this function if favour of Standard GetEta
double CCPACSWingSegment::GetEta(gp_Pnt pnt, double xsi)
{
    // Build virtual eta line.
    // eta is in x = 0
    gp_Pnt pnt0 = GetChordPoint(0, xsi);
    pnt0 = gp_Pnt(0, pnt0.Y(), pnt0.Z());

    gp_Pnt pnt1 = GetChordPoint(1, xsi);
    pnt1 = gp_Pnt(0, pnt1.Y(), pnt1.Z());

    BRepBuilderAPI_MakeWire etaWireBuilder;
    TopoDS_Edge etaEdge = BRepBuilderAPI_MakeEdge(pnt0, pnt1);
    etaWireBuilder.Add(etaEdge);
    TopoDS_Wire etaLine = etaWireBuilder.Wire();

    // intersection line
    Handle(Geom_TrimmedCurve) profileLine = GC_MakeSegment(pnt, gp_Pnt(-1e9, 0, 0));
    BRepBuilderAPI_MakeEdge ME(profileLine);
    TopoDS_Shape aCrv(ME.Edge());

    // now find intersection point
    BRepExtrema_DistShapeShape extrema(etaLine, aCrv);
    extrema.Perform();
    gp_Pnt intersectionPoint = extrema.PointOnShape1(1);

    //length of the eta line
    Standard_Real len1 = pnt0.Distance(pnt1);
    // now the small line, a fraction of the original eta line
    Standard_Real len2 = pnt0.Distance(intersectionPoint);

    assert(len1 != 0.);

    return len2/len1;
}


// Returns eta as parametric distance from a given point on the surface
double CCPACSWingSegment::GetEta(gp_Pnt pnt, bool isUpper)
{
    double eta = 0., xsi = 0.;
    GetEtaXsi(pnt, eta, xsi);
    return eta;
}

// Returns xsi as parametric distance from a given point on the surface
double CCPACSWingSegment::GetXsi(gp_Pnt pnt, bool isUpper)
{
    double eta = 0., xsi = 0.;
    GetEtaXsi(pnt, eta, xsi);
    return xsi;
}

// Returns xsi as parametric distance from a given point on the surface
void CCPACSWingSegment::GetEtaXsi(gp_Pnt pnt, double& eta, double& xsi)
{
    MakeSurfaces();
    CTiglPoint tmpPnt(pnt.XYZ());
    if (cordSurface.translate(tmpPnt, &eta, &xsi) != TIGL_SUCCESS) {
        throw tigl::CTiglError("Cannot determine eta, xsi coordinates of current point in CCPACSWingSegment::GetEtaXsi!", TIGL_MATH_ERROR);
    }
}

// Returns if the given point is ont the Top of the wing or on the lower side.
bool CCPACSWingSegment::GetIsOnTop(gp_Pnt pnt)
{
    double tolerance = 0.03; // 3cm

    MakeSurfaces();

    GeomAPI_ProjectPointOnSurf Proj(pnt, upperSurface);
    if (Proj.NbPoints() > 0 && Proj.LowerDistance() < tolerance) {
        return true;
    }
    else {
        return false;
    }
}

// Builds upper/lower surfaces as shapes
// we split the wing profile into upper and lower wire.
// To do so, we have to determine, what is up
void CCPACSWingSegment::MakeSurfaces()
{
    if (surfacesAreValid) {
        return;
    }
    
    CCPACSWingProfile& innerProfile = innerConnection.GetProfile();
    CCPACSWingProfile& outerProfile = outerConnection.GetProfile();

    // Compute points on wing profiles for the given xsi
    gp_Pnt inner_lep = innerProfile.GetChordPoint(0.);
    gp_Pnt outer_lep = outerProfile.GetChordPoint(0.);
    gp_Pnt inner_tep = innerProfile.GetChordPoint(1.);
    gp_Pnt outer_tep = outerProfile.GetChordPoint(1.);

    // Do section element transformation on points
    inner_lep = transformProfilePoint(wing->GetTransformation(), innerConnection, inner_lep);
    inner_tep = transformProfilePoint(wing->GetTransformation(), innerConnection, inner_tep);
    outer_lep = transformProfilePoint(wing->GetTransformation(), outerConnection, outer_lep);
    outer_tep = transformProfilePoint(wing->GetTransformation(), outerConnection, outer_tep);
        
    cordSurface.setQuadriangle(inner_lep.XYZ(), outer_lep.XYZ(), inner_tep.XYZ(), outer_tep.XYZ());

    TopoDS_Edge iu_wire = innerConnection.GetProfile().GetUpperWireClosed();
    TopoDS_Edge ou_wire = outerConnection.GetProfile().GetUpperWireClosed();
    TopoDS_Edge il_wire = innerConnection.GetProfile().GetLowerWireClosed();
    TopoDS_Edge ol_wire = outerConnection.GetProfile().GetLowerWireClosed();

    // [[CAS_AES]] removed wing transformation
    CTiglTransformation identity;
    iu_wire = TopoDS::Edge(transformProfileWire(identity, innerConnection, iu_wire));
    ou_wire = TopoDS::Edge(transformProfileWire(identity, outerConnection, ou_wire));
    il_wire = TopoDS::Edge(transformProfileWire(identity, innerConnection, il_wire));
    ol_wire = TopoDS::Edge(transformProfileWire(identity, outerConnection, ol_wire));

    BRepOffsetAPI_ThruSections upperSections(Standard_False,Standard_True);
    upperSections.AddWire(BRepBuilderAPI_MakeWire(iu_wire));
    upperSections.AddWire(BRepBuilderAPI_MakeWire(ou_wire));
    upperSections.Build();

    BRepOffsetAPI_ThruSections lowerSections(Standard_False,Standard_True);
    lowerSections.AddWire(BRepBuilderAPI_MakeWire(il_wire));
    lowerSections.AddWire(BRepBuilderAPI_MakeWire(ol_wire));
    lowerSections.Build();

#ifndef NDEBUG
    assert(GetNumberOfFaces(upperSections.Shape()) == 1);
    assert(GetNumberOfFaces(lowerSections.Shape()) == 1);
#endif

    TopExp_Explorer faceExplorer;
    faceExplorer.Init(upperSections.Shape(), TopAbs_FACE);
#ifndef NDEBUG
    assert(faceExplorer.More());
#endif
    upperShape = faceExplorer.Current();
    upperSurface = BRep_Tool::Surface(TopoDS::Face(upperShape));
    
    faceExplorer.Init(lowerSections.Shape(), TopAbs_FACE);
#ifndef NDEBUG
    assert(faceExplorer.More());
#endif
    lowerShape = faceExplorer.Current();
    lowerSurface = BRep_Tool::Surface(TopoDS::Face(lowerShape));
    
    // compute total surface area
    GProp_GProps sprops;
    BRepGProp::SurfaceProperties(upperShape, sprops);
    double upperArea = sprops.Mass();
    BRepGProp::SurfaceProperties(lowerShape, sprops);
    double lowerArea = sprops.Mass();
    
    mySurfaceArea = upperArea + lowerArea;

    // [[CAS_AES]] computing inner shape, outer shape
    // [[CAS_AES]] BEGIN
    TopoDS_Wire wire = GetInnerWire();
    innerShape = BRepBuilderAPI_MakeFace(wire).Face();
    wire = GetOuterWire();
    outerShape = BRepBuilderAPI_MakeFace(wire).Face();

    // [[CAS_AES]] compute shapes for opened profiles
    TopoDS_Edge iu_wire_open = innerConnection.GetProfile().GetUpperWireOpened();
    TopoDS_Edge ou_wire_open = outerConnection.GetProfile().GetUpperWireOpened();
    TopoDS_Edge il_wire_open = innerConnection.GetProfile().GetLowerWireOpened();
    TopoDS_Edge ol_wire_open = outerConnection.GetProfile().GetLowerWireOpened();
    iu_wire_open = TopoDS::Edge(transformProfileWire(identity, innerConnection, iu_wire_open));
    ou_wire_open = TopoDS::Edge(transformProfileWire(identity, outerConnection, ou_wire_open));
    il_wire_open = TopoDS::Edge(transformProfileWire(identity, innerConnection, il_wire_open));
    ol_wire_open = TopoDS::Edge(transformProfileWire(identity, outerConnection, ol_wire_open));

    // compute upper and lower shapes for opened profile
    BRepOffsetAPI_ThruSections upperSectionsOpened(Standard_False,Standard_True);
    upperSectionsOpened.AddWire(BRepBuilderAPI_MakeWire(iu_wire_open));
    upperSectionsOpened.AddWire(BRepBuilderAPI_MakeWire(ou_wire_open));
    upperSectionsOpened.Build();

    BRepOffsetAPI_ThruSections lowerSectionsOpened(Standard_False,Standard_True);
    lowerSectionsOpened.AddWire(BRepBuilderAPI_MakeWire(il_wire_open));
    lowerSectionsOpened.AddWire(BRepBuilderAPI_MakeWire(ol_wire_open));
    lowerSectionsOpened.Build();

#ifndef NDEBUG
    assert(GetNumberOfFaces(upperSectionsOpened.Shape()) == 1);
    assert(GetNumberOfFaces(lowerSectionsOpened.Shape()) == 1);
#endif

    faceExplorer.Init(upperSectionsOpened.Shape(), TopAbs_FACE);
#ifndef NDEBUG
    assert(faceExplorer.More());
#endif
    upperShapeOpened = faceExplorer.Current();

    faceExplorer.Init(lowerSectionsOpened.Shape(), TopAbs_FACE);
#ifndef NDEBUG
    assert(faceExplorer.More());
#endif
    lowerShapeOpened = faceExplorer.Current();

    // compute inner and outer shapes for opened profiles
    wire = GetInnerWireOpened();
    innerShapeOpened = BRepBuilderAPI_MakeFace(wire).Face();
    wire = GetOuterWireOpened();
    outerShapeOpened = BRepBuilderAPI_MakeFace(wire).Face();

    // get trailing edge wires from inner and outer profile
    TopoDS_Edge innerTEWire = innerProfile.GetTrailingEdgeOpened();
    TopoDS_Edge outerTEWire = outerProfile.GetTrailingEdgeOpened();
    if (innerTEWire.IsNull() || outerTEWire.IsNull()) {
        throw CTiglError("ERROR: trailing edge geometry of Wing Section Profile not found!");
    }
    // transform wires
    innerTEWire = TopoDS::Edge(transformProfileWire(identity, innerConnection, innerTEWire));
    outerTEWire = TopoDS::Edge(transformProfileWire(identity, outerConnection, outerTEWire));
    // generate face
    BRepOffsetAPI_ThruSections teGenerator(Standard_False, Standard_True);
    teGenerator.AddWire(BRepBuilderAPI_MakeWire(innerTEWire));
    teGenerator.AddWire(BRepBuilderAPI_MakeWire(outerTEWire));
    teGenerator.Build();
    trailingEdgeShape = teGenerator.Shape();
    // [[CAS_AES]] END

    surfacesAreValid = true;
}



// Returns the reference area of the quadrilateral portion of the wing segment
// by projecting the wing segment into the plane defined by the user
double CCPACSWingSegment::GetReferenceArea(TiglSymmetryAxis symPlane)
{
    CTiglPoint innerLepProj(GetChordPoint(0, 0.).XYZ());
    CTiglPoint outerLepProj(GetChordPoint(0, 1.).XYZ());
    CTiglPoint innerTepProj(GetChordPoint(1, 0.).XYZ());
    CTiglPoint outerTepProj(GetChordPoint(1, 1.).XYZ());

    // project into plane
    switch (symPlane) {
    case TIGL_X_Y_PLANE:
        innerLepProj.z = 0.;
        outerLepProj.z = 0.;
        innerTepProj.z = 0.;
        outerTepProj.z = 0.;
        break;

    case TIGL_X_Z_PLANE:
        innerLepProj.y = 0.;
        outerLepProj.y = 0.;
        innerTepProj.y = 0.;
        outerTepProj.y = 0.;
        break;

    case TIGL_Y_Z_PLANE:
        innerLepProj.x = 0.;
        outerLepProj.x = 0.;
        innerTepProj.x = 0.;
        outerTepProj.x = 0.;
        break;
    default:
        // don't project
        break;
    }

    return quadrilateral_area(innerTepProj, outerTepProj, outerLepProj, innerLepProj);
}

// Returns the lower Surface of this Segment
Handle(Geom_Surface) CCPACSWingSegment::GetLowerSurface()
{
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return lowerSurface;
}

// Returns the upper Surface of this Segment
Handle(Geom_Surface) CCPACSWingSegment::GetUpperSurface()
{
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return upperSurface;
}

// Returns the upper wing shape of this Segment
TopoDS_Shape& CCPACSWingSegment::GetUpperShape()
{
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return upperShape;
}

// Returns the lower wing shape of this Segment
TopoDS_Shape& CCPACSWingSegment::GetLowerShape()
{
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return lowerShape;
}

// [[CAS_AES]] added getter for trailing edge shape
const TopoDS_Shape& CCPACSWingSegment::GetTrailingEdgeShape()
{
    if (!surfacesAreValid) {
        MakeSurfaces();
    }
    return trailingEdgeShape;
}

// get guide curve for given UID
CCPACSGuideCurve& CCPACSWingSegment::GetGuideCurve(std::string UID)
{
    return guideCurves.GetGuideCurve(UID);
}

// check if guide curve with a given UID exists
bool CCPACSWingSegment::GuideCurveExists(std::string UID)
{
    return guideCurves.GuideCurveExists(UID);
}

TopTools_SequenceOfShape& CCPACSWingSegment::GetGuideCurveWires()
{
    if (guideCurveWires.IsEmpty()) {
        BuildGuideCurveWires();
    }
    return guideCurveWires;
}

// Creates all guide curves
void CCPACSWingSegment::BuildGuideCurveWires(void)
{
    guideCurveWires.Clear();
    if (guideCurvesPresent) {
        // get upper and lower part of inner profile in world coordinates
        CCPACSWingProfile& innerProfile = innerConnection.GetProfile();
        TopoDS_Edge upperInnerWire = TopoDS::Edge(transformProfileWire(GetWing().GetTransformation(), innerConnection, innerProfile.GetUpperWire()));
        TopoDS_Edge lowerInnerWire = TopoDS::Edge(transformProfileWire(GetWing().GetTransformation(), innerConnection, innerProfile.GetLowerWire()));

        // get upper and lower part of outer profile in world coordinates
        CCPACSWingProfile& outerProfile = outerConnection.GetProfile();
        TopoDS_Edge upperOuterWire = TopoDS::Edge(transformProfileWire(GetWing().GetTransformation(), outerConnection, outerProfile.GetUpperWire()));
        TopoDS_Edge lowerOuterWire = TopoDS::Edge(transformProfileWire(GetWing().GetTransformation(), outerConnection, outerProfile.GetLowerWire()));

        // concatenate inner profile wires for guide curve construction algorithm
        TopTools_SequenceOfShape concatenatedInnerWires;
        concatenatedInnerWires.Append(lowerInnerWire);
        concatenatedInnerWires.Append(upperInnerWire);

        // concatenate outer profile wires for guide curve construction algorithm
        TopTools_SequenceOfShape concatenatedOuterWires;
        concatenatedOuterWires.Append(lowerOuterWire);
        concatenatedOuterWires.Append(upperOuterWire);

        // get chord lengths for inner profile in word coordinates
        TopoDS_Wire innerChordLineWire = TopoDS::Wire(transformProfileWire(GetWing().GetTransformation(), innerConnection, innerProfile.GetChordLineWire()));
        TopoDS_Wire outerChordLineWire = TopoDS::Wire(transformProfileWire(GetWing().GetTransformation(), outerConnection, outerProfile.GetChordLineWire()));
        double innerScale = GetWireLength(innerChordLineWire);
        double outerScale = GetWireLength(outerChordLineWire);

        // loop through all guide curves and construct the corresponding wires
        int nGuideCurves = guideCurves.GetGuideCurveCount();
        for (int i=0; i!=nGuideCurves; i++) {
            // get guide curve
            CCPACSGuideCurve& guideCurve = guideCurves.GetGuideCurve(i+1);
            double fromRelativeCircumference;
            // check if fromRelativeCircumference is given in the current guide curve
            if (guideCurve.GetFromRelativeCircumferenceIsSet()) {
                fromRelativeCircumference = guideCurve.GetFromRelativeCircumference();
            }
            // otherwise get relative circumference from neighboring segment guide curve
            else {
                // get neighboring guide curve UID
                std::string neighborGuideCurveUID = guideCurve.GetFromGuideCurveUID();
                // get neighboring guide curve
                CCPACSGuideCurve& neighborGuideCurve = wing->GetGuideCurve(neighborGuideCurveUID);
                // get relative circumference from neighboring guide curve
                fromRelativeCircumference = neighborGuideCurve.GetToRelativeCircumference();
            }
            // get relative circumference of outer profile
            double toRelativeCircumference = guideCurve.GetToRelativeCircumference();
            // get guide curve profile UID
            std::string guideCurveProfileUID = guideCurve.GetGuideCurveProfileUID();
            // get relative circumference of inner profile

            // get guide curve profile
            CCPACSConfiguration& config = wing->GetConfiguration();
            CCPACSGuideCurveProfile& guideCurveProfile = config.GetGuideCurveProfile(guideCurveProfileUID);

            // construct guide curve algorithm
            TopoDS_Wire guideCurveWire = CCPACSGuideCurveAlgo<CCPACSWingProfileGetPointAlgo> (concatenatedInnerWires, concatenatedOuterWires, fromRelativeCircumference, toRelativeCircumference, innerScale, outerScale, guideCurveProfile);
            guideCurveWires.Append(guideCurveWire);
        }
    }
}

int CCPACSWingSegment::GetGuideCurveCount() const
{
    return guideCurves.GetGuideCurveCount();
}

} // end namespace tigl


