/*
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-12-17 Tobias Stollenwerk <Tobias.Stollenwerk@dlr.de>
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
* @brief  Implementation of CPACS wing profile as a CST profile
*
* The wing profile is defined by the (C)lass function / (S)hape function (T)ransformation
* geometry representation method.
*/

#include "CTiglError.h"
#include "CTiglTypeRegistry.h"
#include "CTiglLogging.h"
#include "CTiglTransformation.h"
#include "CCPACSWingProfileFactory.h"
#include "math.h"

#include "gp_Pnt2d.hxx"
#include "gp_Vec2d.hxx"
#include "gp_Dir2d.hxx"
#include "gp_Pln.hxx"
#include "Bnd_Box.hxx"
#include "Geom2d_Line.hxx"
#include "Geom2d_TrimmedCurve.hxx"
#include "TopoDS.hxx"
#include "TopExp_Explorer.hxx"
#include "TopAbs_ShapeEnum.hxx"
#include "TopoDS_Edge.hxx"
#include "GCE2d_MakeSegment.hxx"
#include "BRep_Tool.hxx"
#include "BRepTools.hxx"
#include "BRepAlgo.hxx"
#include "BRepAdaptor_CompCurve.hxx"
#include "Geom2dAPI_InterCurveCurve.hxx"
#include "GeomAPI_ProjectPointOnCurve.hxx"
#include "GeomAPI.hxx"
#include "gce_MakeDir.hxx"
#include "gce_MakePln.hxx"
#include "BRepTools_WireExplorer.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "BRepBndLib.hxx"
#include "ShapeFix_Wire.hxx"
#include "math/tiglmathfunctions.h"
#include "CTiglInterpolateBsplineWire.h"
#include "CTiglInterpolateLinearWire.h"
#include "ITiglWingProfileAlgo.h"
#include "CCPACSWingProfileCST.h"
#include <GeomAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <algorithm>


namespace tigl
{

namespace
{
    // helper function to read in tixi vector
    std::vector<double> readTixiVector (TixiDocumentHandle tixiHandle, const std::string& xpath, const std::string& name, const std::string& funcname)
    {
        std::string fullpath = xpath + name;
        int count;
        if (tixiGetVectorSize(tixiHandle, fullpath.c_str(), &count) != SUCCESS) {
            throw CTiglError("Error: XML error while reading vector <" + name + "> in " + funcname, TIGL_XML_ERROR);
        }
        double *tmp;
        if (tixiGetFloatVector(tixiHandle, fullpath.c_str(), &tmp, count) != SUCCESS)  {
            throw CTiglError("Error: XML error while reading vector <" + name + "> in " + funcname, TIGL_XML_ERROR);
        }
        std::vector<double> res(tmp, tmp+count);
        return res;
    }
    // helper function to read in tixi double
    double readTixiDouble (TixiDocumentHandle tixiHandle, const std::string& xpath, const std::string& name, const std::string& funcname)
    {
        std::string fullpath = xpath + name;
        double res;
        if (tixiGetDoubleElement(tixiHandle, fullpath.c_str(), &res) != SUCCESS) {
            throw CTiglError("Error: XML error while reading double <" + name + "> in " + funcname, TIGL_XML_ERROR);
        }
        return res;
    }
} // anonymous namespace


// register profile algo at factory
PTiglWingProfileAlgo CreateProfileCST(const CCPACSWingProfile& profile, const std::string& cpacsPath)
{
    return PTiglWingProfileAlgo(new CCPACSWingProfileCST(profile, cpacsPath));
}

AUTORUN(CCPACSWingProfileCST)
{
    return CCPACSWingProfileFactory::Instance().RegisterAlgo(CCPACSWingProfileCST::CPACSID(), CreateProfileCST);
}

// Constructor
CCPACSWingProfileCST::CCPACSWingProfileCST(const CCPACSWingProfile&, const std::string& path)
{
    ProfileDataXPath=path + "/" + CPACSID();
    trailingEdge.Nullify();
}

// Destructor
CCPACSWingProfileCST::~CCPACSWingProfileCST(void)
{
}

std::string CCPACSWingProfileCST::CPACSID()
{
    return "cst2D";
}

// Cleanup routine
void CCPACSWingProfileCST::Cleanup(void)
{
    for (CCPACSCoordinateContainer::size_type i = 0; i < upperCoordinates.size(); i++) {
        delete upperCoordinates[i];
    }
    upperCoordinates.clear();
    for (CCPACSCoordinateContainer::size_type i = 0; i < lowerCoordinates.size(); i++) {
        delete lowerCoordinates[i];
    }
    lowerCoordinates.clear();
    coordinates.clear();

    psi.clear();
    upperB.clear();
    lowerB.clear();
    trailingEdge.Nullify();
}

void CCPACSWingProfileCST::Update(void)
{
    BuildLETEPoints();
    BuildWires();
}

// Read wing profile file
void CCPACSWingProfileCST::ReadCPACS(TixiDocumentHandle tixiHandle)
{
    psi=readTixiVector(tixiHandle, ProfileDataXPath, "/psi", "CCPACSWingProfileCST::ReadCPACS"); 
    upperB=readTixiVector(tixiHandle, ProfileDataXPath, "/upperB", "CCPACSWingProfileCST::ReadCPACS"); 
    lowerB=readTixiVector(tixiHandle, ProfileDataXPath, "/lowerB", "CCPACSWingProfileCST::ReadCPACS"); 
    upperN1=readTixiDouble(tixiHandle, ProfileDataXPath, "/upperN1", "CCPACSWingProfileCST::ReadCPACS"); 
    upperN2=readTixiDouble(tixiHandle, ProfileDataXPath, "/upperN2", "CCPACSWingProfileCST::ReadCPACS"); 
    lowerN1=readTixiDouble(tixiHandle, ProfileDataXPath, "/lowerN1", "CCPACSWingProfileCST::ReadCPACS"); 
    lowerN2=readTixiDouble(tixiHandle, ProfileDataXPath, "/lowerN2", "CCPACSWingProfileCST::ReadCPACS"); 
        
    // create sample points on the wing profile with x-coordinate given by psi
    // make sure, that psi has 0.0 at beginning and 1.0 at end and is bounded by 0.0 and 1.0
    if (psi.size()<=2) {
        // ignore psi and set 0.0 and 1.0
        psi.clear(),
        psi.push_back(0.0);
        psi.push_back(1.0);
    }
    else {
        // sort psi
        std::sort(psi.begin(), psi.end());
        // get maximal psi value 
        double psimax=psi[psi.size()-1];
        // get minimal psi value 
        double psimin=psi[0];
        if (psimax>1.0) {
            throw CTiglError("Error: CCPACSWingProfileCST::ReadCPACS: Psi values greater than 1.0", TIGL_ERROR);
        }
        // force end value of 1.0
        else if (psimax<1.0-Precision::Confusion()) {
            psi.push_back(1.0);
        }
        if (psimin<0.0) {
            throw CTiglError("Error: CCPACSWingProfileCST::ReadCPACS: Negative psi values", TIGL_ERROR);
        }
        // force start value of 0.0
        else if (psimin>0.0+Precision::Confusion()) {
            psi.insert(psi.begin(),0.0);
        }
    }
    // get upper and lower sample points
    for (size_t i = 0; i<psi.size(); i++) {
        CTiglPoint* point1 = new CTiglPoint(psi[i], 0.0, cstcurve(upperN1, upperN2, upperB, psi[i]));
        upperCoordinates.push_back(point1);
        CTiglPoint* point2 = new CTiglPoint(psi[i], 0.0, -cstcurve(lowerN1, lowerN2, lowerB, psi[i]));
        lowerCoordinates.push_back(point2);
    }

    // Loop forwards over lower CST points (leave out last point)
    for (size_t i = psi.size()-1; i > 0; i--) {
        coordinates.push_back(upperCoordinates[i]);
    }
    // Loop forwards over lower CST points
    for (size_t i = 0; i < psi.size()-1; i++) {
        coordinates.push_back(lowerCoordinates[i]);
    }
}

// Builds the wing profile wire. The returned wire is already transformed by the
// wing profile element transformation.
void CCPACSWingProfileCST::BuildWires()
{
    // Build upper wire

    // fill in upper points from front to back
    Handle(TColgp_HArray1OfPnt) hUpperPoints = new TColgp_HArray1OfPnt(1, upperCoordinates.size());
    for (size_t i = 0; i < upperCoordinates.size(); i++) {
        hUpperPoints->SetValue(i + 1, upperCoordinates[i]->Get_gp_Pnt());
    }

    // set the tangency conditions
    gp_Vec tu1, tu2;
    if (upperN1 < 1.) {
        tu1 = gp_Vec(0.0, 0.0, 1.0);
    }
    else {
        tu1 = gp_Vec(1.0, 0.0, cstcurve_deriv(upperN1, upperN2, upperB, 1, 0.0));
    }

    if (upperN2 < 1.) {
        tu2 = gp_Vec(0.0, 0.0, 1.0);
    }
    else {
        tu2 = gp_Vec(1.0, 0.0, cstcurve_deriv(upperN1, upperN2, upperB, 1, 1.0));
    }

    // interpolate
    GeomAPI_Interpolate upperInter(hUpperPoints, Standard_False, 1e-6);
    upperInter.Load(tu1,tu2, Standard_False);
    upperInter.Perform();
    Handle(Geom_BSplineCurve) hUpperCurve = upperInter.Curve();

    upperWire = BRepBuilderAPI_MakeEdge(hUpperCurve);
    if (upperWire.IsNull() == Standard_True) {
        throw CTiglError("Error: TopoDS_Wire upperWire is null in CCPACSWingProfileCST::BuildWires", TIGL_ERROR);
    }

    // Build lower wire
    // Copy points

    // fill in lower points from back to front
    Handle(TColgp_HArray1OfPnt) hLowerPoints = new TColgp_HArray1OfPnt(1, lowerCoordinates.size());
    for (size_t i = 0; i < lowerCoordinates.size(); i++) {
        hLowerPoints->SetValue(i + 1, lowerCoordinates[i]->Get_gp_Pnt());
    }

    // set the tangency conditions
    gp_Vec tl1, tl2;
    if (lowerN1 < 1.) {
        tl1 = gp_Vec(0.0, 0.0, -1.0);
    }
    else {
        tl1 = gp_Vec(1.0, 0.0, -cstcurve_deriv(lowerN1, lowerN2, lowerB, 1, 0.0));
    }

    if (lowerN2 < 1.) {
        tl2 = gp_Vec(0.0, 0.0, -1.0);
    }
    else {
        tl2 = gp_Vec(1.0, 0.0, -cstcurve_deriv(lowerN1, lowerN2, lowerB, 1, 1.0));
    }

    // interpolate
    GeomAPI_Interpolate lowerInter(hLowerPoints, Standard_False, 1e-6);
    lowerInter.Load(tl1,tl2, Standard_False);
    lowerInter.Perform();
    Handle(Geom_BSplineCurve) hLowerCurve = lowerInter.Curve();
    hLowerCurve->Reverse();
    
    lowerWire = BRepBuilderAPI_MakeEdge(hLowerCurve);
    if (lowerWire.IsNull() == Standard_True) {
        throw CTiglError("Error: TopoDS_Wire lowerWire is null in CCPACSWingProfileCST::BuildWires", TIGL_ERROR);
    }
    
    // fill in all points to create edge from lower to upper
    Standard_Integer totalPoints = upperCoordinates.size() + lowerCoordinates.size() - 1;
    Handle(TColgp_HArray1OfPnt) hTotalPoints = 
            new TColgp_HArray1OfPnt(1, totalPoints);
    Standard_Integer occIndex = 1;
    for (size_t i = lowerCoordinates.size(); i > 0; i--) {
        hTotalPoints->SetValue(occIndex, lowerCoordinates[i-1]->Get_gp_Pnt());
        occIndex++;
    }
    for (size_t i = 1; i < upperCoordinates.size(); i++) {
        hTotalPoints->SetValue(occIndex, upperCoordinates[i]->Get_gp_Pnt());
        occIndex++;
    }
    
    
    GeomAPI_Interpolate totalInter(hTotalPoints, Standard_False, 1e-6);
    TColgp_Array1OfVec tangents(1, totalPoints);
    Handle(TColStd_HArray1OfBoolean) bools = new TColStd_HArray1OfBoolean(1, totalPoints);
    // reset, disable all tangents
    for (int i = 1; i <= totalPoints; ++i) {
        tangents.SetValue(i, gp_Vec(0,0,0));
        bools->SetValue(i, Standard_False);
    }
    // set start and end tangent
    tangents.SetValue(1, -tl2);
    tangents.SetValue(totalPoints, tu2);
    bools->SetValue(1, Standard_True);
    bools->SetValue(totalPoints, Standard_True);
    
    // set leading edge tangent
    gp_Vec meanVec = (tu1 - tl1)/2.;
    Standard_Integer lePointPosition = lowerCoordinates.size();
    tangents.SetValue(lePointPosition, meanVec);
    bools->SetValue(lePointPosition, Standard_True);
    
    totalInter.Load(tangents, bools, Standard_False);
    totalInter.Perform();
    Handle(Geom_BSplineCurve) hTotalCurve = totalInter.Curve();
    
    upperLowerEdge = BRepBuilderAPI_MakeEdge(hTotalCurve);
    if (upperLowerEdge.IsNull() == Standard_True) {
        throw CTiglError("Error: TopoDS_Wire upperLowerEdge is null in CCPACSWingProfileCST::BuildWires", TIGL_ERROR);
    }
}

// Builds leading and trailing edge points of the wing profile wire.
void CCPACSWingProfileCST::BuildLETEPoints(void)
{
    lePoint = upperCoordinates[0]->Get_gp_Pnt();
    tePoint = lowerCoordinates[lowerCoordinates.size()-1]->Get_gp_Pnt();
}

// Returns sample points
std::vector<CTiglPoint*> CCPACSWingProfileCST::GetSamplePoints() const
{
    return coordinates;
}

// get profiles CPACS XML path
const std::string & CCPACSWingProfileCST::GetProfileDataXPath() const
{
    return ProfileDataXPath;
}
        
// get upper wing profile wire
const TopoDS_Edge & CCPACSWingProfileCST::GetUpperWire() const
{
    return upperWire;
}
            
// get lower wing profile wire
const TopoDS_Edge & CCPACSWingProfileCST::GetLowerWire() const
{
    return lowerWire;
}

// gets the upper and lower wing profile into on edge
const TopoDS_Edge & CCPACSWingProfileCST::GetUpperLowerWire() const
{
    return upperLowerEdge;
}

// get trailing edge
const TopoDS_Edge & CCPACSWingProfileCST::GetTrailingEdge() const 
{
    return trailingEdge;
}

// get leading edge point();
const gp_Pnt & CCPACSWingProfileCST::GetLEPoint() const
{
    return lePoint;
}
        
// get trailing edge point();
const gp_Pnt & CCPACSWingProfileCST::GetTEPoint() const
{
    return tePoint;
}

} // end namespace tigl
