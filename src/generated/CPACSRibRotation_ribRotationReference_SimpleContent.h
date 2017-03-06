// Copyright (c) 2016 RISC Software GmbH
//
// This file was generated by CPACSGen from CPACS XML Schema (c) German Aerospace Center (DLR/SC).
// Do not edit, all changes are lost when files are re-generated.
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>
#include <cctype>

#include "CTiglError.h"

namespace tigl
{
    namespace generated
    {
        // This enum is used in:
        // CPACSRibRotation_ribRotationReference
        
        // generated from /xsd:schema/xsd:complexType[730]/xsd:complexContent/xsd:extension/xsd:sequence/xsd:element[1]/xsd:complexType/xsd:simpleContent
        #ifdef HAVE_CPP11
        enum class CPACSRibRotation_ribRotationReference_SimpleContent
        #else
        enum CPACSRibRotation_ribRotationReference_SimpleContent
        #endif
        {
            LeadingEdge,
            TrailingEdge,
            FrontSpar,
            RearSpar,
            globalX,
            globalY,
            globalZ
        };
        
        #ifdef HAVE_CPP11
        inline std::string CPACSRibRotation_ribRotationReference_SimpleContentToString(const CPACSRibRotation_ribRotationReference_SimpleContent& value)
        {
            switch(value) {
            case CPACSRibRotation_ribRotationReference_SimpleContent::LeadingEdge: return "LeadingEdge";
            case CPACSRibRotation_ribRotationReference_SimpleContent::TrailingEdge: return "TrailingEdge";
            case CPACSRibRotation_ribRotationReference_SimpleContent::FrontSpar: return "FrontSpar";
            case CPACSRibRotation_ribRotationReference_SimpleContent::RearSpar: return "RearSpar";
            case CPACSRibRotation_ribRotationReference_SimpleContent::globalX: return "globalX";
            case CPACSRibRotation_ribRotationReference_SimpleContent::globalY: return "globalY";
            case CPACSRibRotation_ribRotationReference_SimpleContent::globalZ: return "globalZ";
            default: throw CTiglError("Invalid enum value \"" + std::to_string(static_cast<int>(value)) + "\" for enum type CPACSRibRotation_ribRotationReference_SimpleContent");
            }
        }
        inline CPACSRibRotation_ribRotationReference_SimpleContent stringToCPACSRibRotation_ribRotationReference_SimpleContent(const std::string& value)
        {
            auto toLower = [](std::string str) { for (char& c : str) { c = std::tolower(c); } return str; };
            if (toLower(value) == "leadingedge") { return CPACSRibRotation_ribRotationReference_SimpleContent::LeadingEdge; }
            if (toLower(value) == "trailingedge") { return CPACSRibRotation_ribRotationReference_SimpleContent::TrailingEdge; }
            if (toLower(value) == "frontspar") { return CPACSRibRotation_ribRotationReference_SimpleContent::FrontSpar; }
            if (toLower(value) == "rearspar") { return CPACSRibRotation_ribRotationReference_SimpleContent::RearSpar; }
            if (toLower(value) == "globalx") { return CPACSRibRotation_ribRotationReference_SimpleContent::globalX; }
            if (toLower(value) == "globaly") { return CPACSRibRotation_ribRotationReference_SimpleContent::globalY; }
            if (toLower(value) == "globalz") { return CPACSRibRotation_ribRotationReference_SimpleContent::globalZ; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSRibRotation_ribRotationReference_SimpleContent");
        }
        #else
        inline std::string CPACSRibRotation_ribRotationReference_SimpleContentToString(const CPACSRibRotation_ribRotationReference_SimpleContent& value)
        {
            switch(value) {
            case LeadingEdge: return "LeadingEdge";
            case TrailingEdge: return "TrailingEdge";
            case FrontSpar: return "FrontSpar";
            case RearSpar: return "RearSpar";
            case globalX: return "globalX";
            case globalY: return "globalY";
            case globalZ: return "globalZ";
            default: throw CTiglError("Invalid enum value \"" + std::to_string(static_cast<int>(value)) + "\" for enum type CPACSRibRotation_ribRotationReference_SimpleContent");
            }
        }
        inline CPACSRibRotation_ribRotationReference_SimpleContent stringToCPACSRibRotation_ribRotationReference_SimpleContent(const std::string& value)
        {
            struct ToLower { std::string operator()(std::string str) { for (char& c : str) { c = std::tolower(c); } return str; } } toLower;
            if (toLower(value) == "leadingedge") { return LeadingEdge; }
            if (toLower(value) == "trailingedge") { return TrailingEdge; }
            if (toLower(value) == "frontspar") { return FrontSpar; }
            if (toLower(value) == "rearspar") { return RearSpar; }
            if (toLower(value) == "globalx") { return globalX; }
            if (toLower(value) == "globaly") { return globalY; }
            if (toLower(value) == "globalz") { return globalZ; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSRibRotation_ribRotationReference_SimpleContent");
        }
        #endif
    }
}
