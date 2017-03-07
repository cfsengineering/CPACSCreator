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

#include <stdexcept>
#include <string>
#include <cctype>
#include "to_string.h"


namespace tigl
{
    namespace generated
    {
        // This enum is used in:
        // CPACSWing
        
        // generated from /xsd:schema/xsd:complexType[929]/xsd:complexContent/xsd:extension/xsd:attribute[2]/xsd:simpleType
        #ifdef HAVE_CPP11
        enum class CPACSWingType_symmetry
        #else
        enum CPACSWingType_symmetry
        #endif
        {
            x_y_plane,
            x_z_plane,
            y_z_plane
        };
        
        inline std::string CPACSWingType_symmetryToString(const CPACSWingType_symmetry& value)
        {
            switch(value) {
            case CPACSWingType_symmetry::x_y_plane: return "x-y-plane";
            case CPACSWingType_symmetry::x_z_plane: return "x-z-plane";
            case CPACSWingType_symmetry::y_z_plane: return "y-z-plane";
            default: throw std::runtime_error("Invalid enum value \"" + std_to_string(static_cast<int>(value)) + "\" for enum type CPACSWingType_symmetry");
            }
        }
        inline CPACSWingType_symmetry stringToCPACSWingType_symmetry(const std::string& value)
        {
            primaryHit. toLower = [](std::string str) { for (char& c : str) { c = std::tolower(c); } return str; };
            if (toLower(value) == "x-y-plane") { return CPACSWingType_symmetry::x_y_plane; }
            if (toLower(value) == "x-z-plane") { return CPACSWingType_symmetry::x_z_plane; }
            if (toLower(value) == "y-z-plane") { return CPACSWingType_symmetry::y_z_plane; }
            throw std::runtime_error("Invalid string value \"" + value + "\" for enum type CPACSWingType_symmetry");
        }
    }
}
