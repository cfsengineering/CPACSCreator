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

#include <tixi.h>
#include <string>
#include "tigl_internal.h"
#include "CPACSTool.h"
#include <CCPACSFarField.h>

namespace tigl
{
    namespace generated
    {
        // This class is used in:
        // CPACSToolspecific
        
        // generated from /xsd:schema/xsd:complexType[100]
        class CPACSCFDTool
        {
        public:
            TIGL_EXPORT CPACSCFDTool();
            TIGL_EXPORT virtual ~CPACSCFDTool();
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT const CPACSTool& GetTool() const;
            TIGL_EXPORT CPACSTool& GetTool();
            
            TIGL_EXPORT const std::string& GetAircraftModelUID() const;
            TIGL_EXPORT void SetAircraftModelUID(const std::string& value);
            
            TIGL_EXPORT const CCPACSFarField& GetFarField() const;
            TIGL_EXPORT CCPACSFarField& GetFarField();
            
        protected:
            CPACSTool      m_tool;
            std::string    m_aircraftModelUID;
            CCPACSFarField m_farField;
            
        private:
            #ifdef HAVE_CPP11
            CPACSCFDTool(const CPACSCFDTool&) = delete;
            CPACSCFDTool& operator=(const CPACSCFDTool&) = delete;
            
            CPACSCFDTool(CPACSCFDTool&&) = delete;
            CPACSCFDTool& operator=(CPACSCFDTool&&) = delete;
            #else
            CPACSCFDTool(const CPACSCFDTool&);
            CPACSCFDTool& operator=(const CPACSCFDTool&);
            #endif
        };
    }
    
    // This type is not customized, create alias in tigl namespace
    #ifdef HAVE_CPP11
    using CCPACSCFDTool = generated::CPACSCFDTool;
    #else
    typedef generated::CPACSCFDTool CCPACSCFDTool;
    #endif
}
