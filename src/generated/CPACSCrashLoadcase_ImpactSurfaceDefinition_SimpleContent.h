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
        // CPACSCrashLoadcase_ImpactSurfaceDefinition
        
        // generated from /xsd:schema/xsd:complexType[229]/xsd:complexContent/xsd:extension/xsd:all/xsd:element[10]/xsd:complexType/xsd:simpleContent
        #ifdef HAVE_CPP11
        enum class CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent
        #else
        enum CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent
        #endif
        {
            rigid,
            water,
            softSoil
        };
        
        #ifdef HAVE_CPP11
        inline std::string CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContentToString(const CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent& value)
        {
            switch(value) {
            case CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent::rigid: return "rigid";
            case CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent::water: return "water";
            case CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent::softSoil: return "softSoil";
            default: throw CTiglError("Invalid enum value \"" + std::to_string(static_cast<int>(value)) + "\" for enum type CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent");
            }
        }
        inline CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent stringToCPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent(const std::string& value)
        {
            auto toLower = [](std::string str) { for (char& c : str) { c = std::tolower(c); } return str; };
            if (toLower(value) == "rigid") { return CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent::rigid; }
            if (toLower(value) == "water") { return CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent::water; }
            if (toLower(value) == "softsoil") { return CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent::softSoil; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent");
        }
        #else
        inline std::string CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContentToString(const CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent& value)
        {
            switch(value) {
            case rigid: return "rigid";
            case water: return "water";
            case softSoil: return "softSoil";
            default: throw CTiglError("Invalid enum value \"" + std::to_string(static_cast<int>(value)) + "\" for enum type CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent");
            }
        }
        inline CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent stringToCPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent(const std::string& value)
        {
            struct ToLower { std::string operator()(std::string str) { for (char& c : str) { c = std::tolower(c); } return str; } } toLower;
            if (toLower(value) == "rigid") { return rigid; }
            if (toLower(value) == "water") { return water; }
            if (toLower(value) == "softsoil") { return softSoil; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSCrashLoadcase_ImpactSurfaceDefinition_SimpleContent");
        }
        #endif
    }
}
