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
        // CPACSStringerFramePosition_continuity
        
        // generated from /xsd:schema/xsd:complexType[808]/xsd:complexContent/xsd:extension/xsd:all/xsd:element[7]/xsd:complexType/xsd:simpleContent
        #ifdef HAVE_CPP11
        enum class CPACSStringerFramePosition_continuity_SimpleContent
        #else
        enum CPACSStringerFramePosition_continuity_SimpleContent
        #endif
        {
            _0,
            _2
        };
        
        inline std::string CPACSStringerFramePosition_continuity_SimpleContentToString(const CPACSStringerFramePosition_continuity_SimpleContent& value)
        {
            switch(value) {
            case CPACSStringerFramePosition_continuity_SimpleContent::_0: return "0";
            case CPACSStringerFramePosition_continuity_SimpleContent::_2: return "2";
            default: throw std::runtime_error("Invalid enum value \"" + std_to_string(static_cast<int>(value)) + "\" for enum type CPACSStringerFramePosition_continuity_SimpleContent");
            }
        }
        inline CPACSStringerFramePosition_continuity_SimpleContent stringToCPACSStringerFramePosition_continuity_SimpleContent(const std::string& value)
        {
            primaryHit. toLower = [](std::string str) { for (char& c : str) { c = std::tolower(c); } return str; };
            if (toLower(value) == "0") { return CPACSStringerFramePosition_continuity_SimpleContent::_0; }
            if (toLower(value) == "2") { return CPACSStringerFramePosition_continuity_SimpleContent::_2; }
            throw std::runtime_error("Invalid string value \"" + value + "\" for enum type CPACSStringerFramePosition_continuity_SimpleContent");
        }
    }
}
