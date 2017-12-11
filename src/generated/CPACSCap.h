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

#include <CCPACSMaterialDefinition.h>
#include <string>
#include <tixi.h>
#include <typeinfo>
#include "CTiglError.h"
#include "tigl_internal.h"

namespace tigl
{
    namespace generated
    {
        // This class is used in:
        // CPACSSparCell
        // CPACSSparCrossSection
        // CPACSWingRibCell
        // CPACSWingRibCrossSection
        
        // generated from /xsd:schema/xsd:complexType[111]
        class CPACSCap
        {
        public:
            TIGL_EXPORT CPACSCap();
            TIGL_EXPORT virtual ~CPACSCap();
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const double& GetArea() const;
            TIGL_EXPORT virtual void SetArea(const double& value);
            
            TIGL_EXPORT virtual const CCPACSMaterialDefinition& GetMaterial() const;
            TIGL_EXPORT virtual CCPACSMaterialDefinition& GetMaterial();
            
        protected:
            double                   m_area;
            CCPACSMaterialDefinition m_material;
            
        private:
            #ifdef HAVE_CPP11
            CPACSCap(const CPACSCap&) = delete;
            CPACSCap& operator=(const CPACSCap&) = delete;
            
            CPACSCap(CPACSCap&&) = delete;
            CPACSCap& operator=(CPACSCap&&) = delete;
            #else
            CPACSCap(const CPACSCap&);
            CPACSCap& operator=(const CPACSCap&);
            #endif
        };
    }
    
    // Aliases in tigl namespace
    #ifdef HAVE_CPP11
    using CCPACSCap = generated::CPACSCap;
    #else
    typedef generated::CPACSCap CCPACSCap;
    #endif
}
