/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-05-28 Martin Siggel <Martin.Siggel@dlr.de>
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

#include "CCPACSWingCell.h"

#include "tixi.h"

#include "CTiglError.h"
#include "CTiglLogger.h"

namespace {
    struct Point2D{
        double x;
        double y;
    };
    
    // calculates crossproduct (p1-p3)x(p2-p3)
    double sign(Point2D p1, Point2D p2, Point2D p3){
      return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }
}

namespace tigl {

CCPACSWingCell::CCPACSWingCell()
{
    reset();
}


void CCPACSWingCell::reset(){
    innerBorderEta1 = 0.;
    innerBorderEta1 = 0.;
    outerBorderEta1 = 0.;
    outerBorderEta2 = 0.;
    leadingEdgeXsi1 = 0.;
    leadingEdgeXsi2 = 0.;
    trailingEdgeXsi1 = 0.;
    trailingEdgeXsi2 = 0.;
    
    uid = "";

}

bool CCPACSWingCell::IsInside(double eta, double xsi) const{
    Point2D p, p1, p2;
    p.x = eta; p.y = xsi;
    
    // calculate for all 4 edges the relative position of eta/xsi

    // trailing edge
    GetTrailingEdgeInnerPoint(&p1.x, &p1.y);
    GetTrailingEdgeOuterPoint(&p2.x, &p2.y);
    bool s1 = sign(p, p1, p2) > 0.;
    
    // outer border
    GetTrailingEdgeOuterPoint(&p1.x, &p1.y);
    GetLeadingEdgeOuterPoint (&p2.x, &p2.y);
    bool s2 = sign(p, p1, p2) > 0.;
    
    // leading edge
    GetLeadingEdgeOuterPoint(&p1.x, &p1.y);
    GetLeadingEdgeInnerPoint(&p2.x, &p2.y);
    bool s3 = sign(p, p1, p2) > 0.;
    
    // inner border
    GetLeadingEdgeInnerPoint (&p1.x, &p1.y);
    GetTrailingEdgeInnerPoint(&p2.x, &p2.y);
    bool s4 = sign(p, p1, p2) > 0.;
    
    return (s1 == s2) && (s2 == s3) && (s3 == s4);
}

void CCPACSWingCell::ReadCPACS(TixiDocumentHandle tixiHandle, const std::string &cellXPath){
    // check path
    if( tixiCheckElement(tixiHandle, cellXPath.c_str()) != SUCCESS){
        LOG(ERROR) << "Wing Cell " << cellXPath << " not found in CPACS file!" << std::endl;
        return;
    }
    
    reset();
    
    // Get UID
    char * nameStr = NULL;
    if ( tixiGetTextAttribute(tixiHandle, cellXPath.c_str(), "uID", &nameStr) != SUCCESS )
        throw tigl::CTiglError("No UID given for wing cell " + cellXPath + "!", TIGL_UID_ERROR);
    
    double iBE1, iBE2, oBE1, oBE2, lEX1, lEX2, tEX1, tEX2;
    
    // get postionings of cell
    std::string positioningString;
    positioningString = cellXPath + "/positioningLeadingEdge/sparUID";
    if( tixiCheckElement(tixiHandle, positioningString.c_str()) == SUCCESS){
        LOG(WARNING) << "In " << cellXPath << ": Cell positiongs via spars is currently not supported by TiGL. Please use eta/xsi definitions.";
    }
    else {
        positioningString = cellXPath + "/positioningLeadingEdge/xsi1";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &lEX1) != SUCCESS)
            throw tigl::CTiglError("No leading edge xsi1 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
        
        positioningString = cellXPath + "/positioningLeadingEdge/xsi2";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &lEX2) != SUCCESS)
            throw tigl::CTiglError("No leading edge xsi2 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
    }

    positioningString = cellXPath + "/positioningTrailingEdge/sparUID";
    if( tixiCheckElement(tixiHandle, positioningString.c_str()) == SUCCESS){
        LOG(WARNING) << "In " << cellXPath << ": Cell positiongs via spars is currently not supported by TiGL. Please use eta/xsi definitions.";
    }
    else {
        positioningString = cellXPath + "/positioningTrailingEdge/xsi1";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &tEX1) != SUCCESS)
            throw tigl::CTiglError("No leading edge xsi1 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
        
        positioningString = cellXPath + "/positioningTrailingEdge/xsi2";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &tEX2) != SUCCESS)
            throw tigl::CTiglError("No leading edge xsi1 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
        
    }
    
    positioningString = cellXPath + "/positioningInnerBorder/ribDefinitionUID";
    if( tixiCheckElement(tixiHandle, positioningString.c_str()) == SUCCESS){
        LOG(WARNING) << "In " << cellXPath << ": Cell positiongs via ribs is currently not supported by TiGL. Please use eta/xsi definitions.";
    }
    else {
        positioningString = cellXPath + "/positioningInnerBorder/eta1";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &iBE1) != SUCCESS)
            throw tigl::CTiglError("No inner border eta1 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
        
        positioningString = cellXPath + "/positioningInnerBorder/eta2";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &iBE2) != SUCCESS)
            throw tigl::CTiglError("No inner border eta2 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
    }
    
    positioningString = cellXPath + "/positioningOuterBorder/ribDefinitionUID";
    if( tixiCheckElement(tixiHandle, positioningString.c_str()) == SUCCESS){
        LOG(WARNING) << "In " << cellXPath << ": Cell positiongs via ribs is currently not supported by TiGL. Please use eta/xsi definitions.";
    }
    else {
        positioningString = cellXPath + "/positioningOuterBorder/eta1";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &oBE1) != SUCCESS)
            throw tigl::CTiglError("No outer border eta1 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
        
        positioningString = cellXPath + "/positioningOuterBorder/eta2";
        if( tixiGetDoubleElement(tixiHandle, positioningString.c_str(), &oBE2) != SUCCESS)
            throw tigl::CTiglError("No outer border eta2 positioning given for wing cell " + cellXPath + "!", TIGL_ERROR);
    }
    
    // read material
    std::string materialString;
    materialString = cellXPath + "/skin/material";
    if( tixiCheckElement(tixiHandle, materialString.c_str()) == SUCCESS){
        material.ReadCPACS(tixiHandle, materialString.c_str());
    }
    else {
        // @todo: should that be an error?
        LOG(WARNING) << "No material definition found for cell " << cellXPath;
    }
    
    // apply everything
    uid = nameStr;
    
    innerBorderEta1 = iBE1;
    innerBorderEta2 = iBE2;
    outerBorderEta1 = oBE1;
    outerBorderEta2 = oBE2;
    leadingEdgeXsi1 = lEX1;
    leadingEdgeXsi2 = lEX2;
    trailingEdgeXsi1 = tEX1;
    trailingEdgeXsi2 = tEX2;
}

void CCPACSWingCell::SetLeadingEdgeInnerPoint(double eta, double xsi){
    leadingEdgeXsi1 = xsi;
    innerBorderEta1 = eta;
}

void CCPACSWingCell::SetLeadingEdgeOuterPoint(double eta, double xsi){
    leadingEdgeXsi2 = xsi;
    outerBorderEta1 = eta;
}

void CCPACSWingCell::SetTrailingEdgeInnerPoint(double eta, double xsi){
    trailingEdgeXsi1 = xsi;
    innerBorderEta2 = eta;
}

void CCPACSWingCell::SetTrailingEdgeOuterPoint(double eta, double xsi){
    trailingEdgeXsi2 = xsi;
    outerBorderEta2 = eta;
}

void CCPACSWingCell::GetLeadingEdgeInnerPoint(double* eta, double* xsi) const{
    *xsi = leadingEdgeXsi1;
    *eta = innerBorderEta1;
}

void CCPACSWingCell::GetLeadingEdgeOuterPoint(double* eta, double* xsi) const{
    *xsi = leadingEdgeXsi2;
    *eta = outerBorderEta1;
}

void CCPACSWingCell::GetTrailingEdgeInnerPoint(double* eta, double* xsi) const{
    *xsi = trailingEdgeXsi1;
    *eta = innerBorderEta2;
}

void CCPACSWingCell::GetTrailingEdgeOuterPoint(double* eta, double* xsi) const{
    *xsi = trailingEdgeXsi2;
    *eta = outerBorderEta2;
}

} // namespace tigl
