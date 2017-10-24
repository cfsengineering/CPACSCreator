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
#include <CCPACSFuselage.h>
#include "CCPACSAircraftModel.h"
#include "CCPACSRotorcraftModel.h"
#include "CPACSFuselages.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSFuselages::CPACSFuselages(CCPACSAircraftModel* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
            m_parentType = &typeid(CCPACSAircraftModel);
        }
        
        CPACSFuselages::CPACSFuselages(CCPACSRotorcraftModel* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
            m_parentType = &typeid(CCPACSRotorcraftModel);
        }
        
        CPACSFuselages::~CPACSFuselages() {}
        
        CTiglUIDManager& CPACSFuselages::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSFuselages::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSFuselages::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element fuselage
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/fuselage")) {
                tixi::TixiReadElements(tixiHandle, xpath + "/fuselage", m_fuselages, reinterpret_cast<CCPACSFuselages*>(this), m_uidMgr);
            }
            
        }
        
        void CPACSFuselages::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element fuselage
            tixi::TixiSaveElements(tixiHandle, xpath + "/fuselage", m_fuselages);
            
        }
        
        const std::vector<unique_ptr<CCPACSFuselage> >& CPACSFuselages::GetFuselages() const
        {
            return m_fuselages;
        }
        
        std::vector<unique_ptr<CCPACSFuselage> >& CPACSFuselages::GetFuselages()
        {
            return m_fuselages;
        }
        
        CCPACSFuselage& CPACSFuselages::AddFuselage()
        {
            m_fuselages.push_back(make_unique<CCPACSFuselage>(reinterpret_cast<CCPACSFuselages*>(this), m_uidMgr));
            return *m_fuselages.back();
        }
        
        void CPACSFuselages::RemoveFuselage(CCPACSFuselage& ref)
        {
            for (std::size_t i = 0; i < m_fuselages.size(); i++) {
                if (m_fuselages[i].get() == &ref) {
                    m_fuselages.erase(m_fuselages.begin() + i);
                    return;
                }
            }
            throw CTiglError("Element not found");
        }
        
    }
}
