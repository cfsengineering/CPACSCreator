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

#include <cassert>
#include <CCPACSWingSparPosition.h>
#include "CCPACSWingSpars.h"
#include "CPACSSparPositions.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSSparPositions::CPACSSparPositions(CCPACSWingSpars* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSSparPositions::~CPACSSparPositions() {}
        
        CCPACSWingSpars* CPACSSparPositions::GetParent() const
        {
            return m_parent;
        }
        
        CTiglUIDManager& CPACSSparPositions::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSSparPositions::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSSparPositions::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element sparPosition
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/sparPosition")) {
                tixi::TixiReadElements(tixiHandle, xpath + "/sparPosition", m_sparPositions, reinterpret_cast<CCPACSWingSparPositions*>(this), m_uidMgr);
            }
            
        }
        
        void CPACSSparPositions::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element sparPosition
            tixi::TixiSaveElements(tixiHandle, xpath + "/sparPosition", m_sparPositions);
            
        }
        
        const std::vector<unique_ptr<CCPACSWingSparPosition> >& CPACSSparPositions::GetSparPositions() const
        {
            return m_sparPositions;
        }
        
        std::vector<unique_ptr<CCPACSWingSparPosition> >& CPACSSparPositions::GetSparPositions()
        {
            return m_sparPositions;
        }
        
        CCPACSWingSparPosition& CPACSSparPositions::AddSparPosition()
        {
            m_sparPositions.push_back(make_unique<CCPACSWingSparPosition>(reinterpret_cast<CCPACSWingSparPositions*>(this), m_uidMgr));
            return *m_sparPositions.back();
        }
        
        void CPACSSparPositions::RemoveSparPosition(CCPACSWingSparPosition& ref)
        {
            for (std::size_t i = 0; i < m_sparPositions.size(); i++) {
                if (m_sparPositions[i].get() == &ref) {
                    m_sparPositions.erase(m_sparPositions.begin() + i);
                    return;
                }
            }
            throw CTiglError("Element not found");
        }
        
    }
}
