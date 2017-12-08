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
#include <string>
#include <tixi.h>
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    class CCPACSWingSparPositions;
    
    namespace generated
    {
        // This class is used in:
        // CPACSSparPositions
        
        // generated from /xsd:schema/xsd:complexType[791]
        class CPACSSparPosition
        {
        public:
            TIGL_EXPORT CPACSSparPosition(CCPACSWingSparPositions* parent, CTiglUIDManager* uidMgr);
            
            TIGL_EXPORT virtual ~CPACSSparPosition();
            
            TIGL_EXPORT CCPACSWingSparPositions* GetParent() const;
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT bool ValidateChoices() const;
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            TIGL_EXPORT virtual void SetUID(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const double& GetXsi() const;
            TIGL_EXPORT virtual void SetXsi(const double& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetEta_choice1() const;
            TIGL_EXPORT virtual void SetEta_choice1(const double& value);
            TIGL_EXPORT virtual void SetEta_choice1(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetElementUID_choice2() const;
            TIGL_EXPORT virtual void SetElementUID_choice2(const std::string& value);
            TIGL_EXPORT virtual void SetElementUID_choice2(const boost::optional<std::string>& value);
            
        protected:
            CCPACSWingSparPositions* m_parent;
            
            CTiglUIDManager* m_uidMgr;
            
            boost::optional<std::string> m_uID;
            double                       m_xsi;
            boost::optional<double>      m_eta_choice1;
            boost::optional<std::string> m_elementUID_choice2;
            
        private:
            #ifdef HAVE_CPP11
            CPACSSparPosition(const CPACSSparPosition&) = delete;
            CPACSSparPosition& operator=(const CPACSSparPosition&) = delete;
            
            CPACSSparPosition(CPACSSparPosition&&) = delete;
            CPACSSparPosition& operator=(CPACSSparPosition&&) = delete;
            #else
            CPACSSparPosition(const CPACSSparPosition&);
            CPACSSparPosition& operator=(const CPACSSparPosition&);
            #endif
        };
    }
    
    // CPACSSparPosition is customized, use type CCPACSWingSparPosition directly
}
