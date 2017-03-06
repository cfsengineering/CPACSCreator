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
        // CPACSSteffsOutputParameters_consideredLoadCasesRatingType
        
        // generated from /xsd:schema/xsd:complexType[796]/xsd:complexContent/xsd:extension/xsd:sequence/xsd:element[14]/xsd:complexType/xsd:simpleContent
        #ifdef HAVE_CPP11
        enum class CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent
        #else
        enum CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent
        #endif
        {
            relative,
            absolute
        };
        
        #ifdef HAVE_CPP11
        inline std::string CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContentToString(const CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent& value)
        {
            switch(value) {
            case CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent::relative: return "relative";
            case CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent::absolute: return "absolute";
            default: throw CTiglError("Invalid enum value \"" + std::to_string(static_cast<int>(value)) + "\" for enum type CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent");
            }
        }
        inline CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent stringToCPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent(const std::string& value)
        {
            auto toLower = [](std::string str) { for (char& c : str) { c = std::tolower(c); } return str; };
            if (toLower(value) == "relative") { return CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent::relative; }
            if (toLower(value) == "absolute") { return CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent::absolute; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent");
        }
        #else
        inline std::string CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContentToString(const CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent& value)
        {
            switch(value) {
            case relative: return "relative";
            case absolute: return "absolute";
            default: throw CTiglError("Invalid enum value \"" + std::to_string(static_cast<int>(value)) + "\" for enum type CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent");
            }
        }
        inline CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent stringToCPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent(const std::string& value)
        {
            struct ToLower { std::string operator()(std::string str) { for (char& c : str) { c = std::tolower(c); } return str; } } toLower;
            if (toLower(value) == "relative") { return relative; }
            if (toLower(value) == "absolute") { return absolute; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSSteffsOutputParameters_consideredLoadCasesRatingType_SimpleContent");
        }
        #endif
    }
}
