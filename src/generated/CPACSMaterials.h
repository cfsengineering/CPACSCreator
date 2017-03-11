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
#include <vector>
#include "UniquePtr.h"
#include <boost/optional.hpp>
#include "tigl_internal.h"
#include "CPACSComposites.h"

namespace tigl
{
    namespace generated
    {
        class CPACSMaterial;
        
        // This class is used in:
        // CPACSVehicles
        
        // generated from /xsd:schema/xsd:complexType[642]
        class CPACSMaterials
        {
        public:
            TIGL_EXPORT CPACSMaterials();
            TIGL_EXPORT virtual ~CPACSMaterials();
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT const std::vector<unique_ptr<CPACSMaterial> >& GetMaterial() const;
            TIGL_EXPORT std::vector<unique_ptr<CPACSMaterial> >& GetMaterial();
            
            TIGL_EXPORT bool HasComposites() const;
            TIGL_EXPORT const CPACSComposites& GetComposites() const;
            TIGL_EXPORT CPACSComposites& GetComposites();
            
        protected:
            std::vector<unique_ptr<CPACSMaterial> > m_material;
            boost::optional<CPACSComposites>        m_composites;
            
        private:
            #ifdef HAVE_CPP11
            CPACSMaterials(const CPACSMaterials&) = delete;
            CPACSMaterials& operator=(const CPACSMaterials&) = delete;
            
            CPACSMaterials(CPACSMaterials&&) = delete;
            CPACSMaterials& operator=(CPACSMaterials&&) = delete;
            #else
            CPACSMaterials(const CPACSMaterials&);
            CPACSMaterials& operator=(const CPACSMaterials&);
            #endif
        };
    }
    
    // This type is not customized, create alias in tigl namespace
    #ifdef HAVE_CPP11
    using CCPACSMaterials = generated::CPACSMaterials;
    #else
    typedef generated::CPACSMaterials CCPACSMaterials;
    #endif
    
    using generated::CPACSMaterial;
}
