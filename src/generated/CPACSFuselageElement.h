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

#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <CCPACSTransformation.h>
#include <string>
#include <tixi.h>
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    class CCPACSFuselageSectionElements;
    
    namespace generated
    {
        // This class is used in:
        // CPACSFuselageElements
        
        // generated from /xsd:schema/xsd:complexType[371]
        class CPACSFuselageElement
        {
        public:
            TIGL_EXPORT CPACSFuselageElement(CCPACSFuselageSectionElements* parent, CTiglUIDManager* uidMgr);
            
            TIGL_EXPORT virtual ~CPACSFuselageElement();
            
            TIGL_EXPORT CCPACSFuselageSectionElements* GetParent() const;
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const std::string& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            
            TIGL_EXPORT virtual const std::string& GetName() const;
            TIGL_EXPORT virtual void SetName(const std::string& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
            TIGL_EXPORT virtual void SetDescription(const std::string& value);
            TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const std::string& GetProfileUID() const;
            TIGL_EXPORT virtual void SetProfileUID(const std::string& value);
            
            TIGL_EXPORT virtual const CCPACSTransformation& GetTransformation() const;
            TIGL_EXPORT virtual CCPACSTransformation& GetTransformation();
            
        protected:
            CCPACSFuselageSectionElements* m_parent;
            
            CTiglUIDManager* m_uidMgr;
            
            std::string                  m_uID;
            std::string                  m_name;
            boost::optional<std::string> m_description;
            std::string                  m_profileUID;
            CCPACSTransformation         m_transformation;
            
        private:
            #ifdef HAVE_CPP11
            CPACSFuselageElement(const CPACSFuselageElement&) = delete;
            CPACSFuselageElement& operator=(const CPACSFuselageElement&) = delete;
            
            CPACSFuselageElement(CPACSFuselageElement&&) = delete;
            CPACSFuselageElement& operator=(CPACSFuselageElement&&) = delete;
            #else
            CPACSFuselageElement(const CPACSFuselageElement&);
            CPACSFuselageElement& operator=(const CPACSFuselageElement&);
            #endif
        };
    }
    
    // CPACSFuselageElement is customized, use type CCPACSFuselageSectionElement directly
}
