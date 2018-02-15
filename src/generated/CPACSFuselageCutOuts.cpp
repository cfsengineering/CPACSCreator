// Copyright (c) 2018 RISC Software GmbH
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

#include "CPACSFuselageCutOut.h"
#include "CPACSFuselageCutOuts.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSFuselageCutOuts::CPACSFuselageCutOuts(CTiglUIDManager* uidMgr)
        : m_uidMgr(uidMgr)
    {
    }

    CPACSFuselageCutOuts::~CPACSFuselageCutOuts()
    {
    }

    CTiglUIDManager& CPACSFuselageCutOuts::GetUIDManager()
    {
        return *m_uidMgr;
    }

    const CTiglUIDManager& CPACSFuselageCutOuts::GetUIDManager() const
    {
        return *m_uidMgr;
    }

    void CPACSFuselageCutOuts::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read element element
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/element")) {
            tixi::TixiReadElements(tixiHandle, xpath + "/element", m_elements, m_uidMgr);
        }

    }

    void CPACSFuselageCutOuts::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write element element
        tixi::TixiSaveElements(tixiHandle, xpath + "/element", m_elements);

    }

    const std::vector<unique_ptr<CPACSFuselageCutOut> >& CPACSFuselageCutOuts::GetElements() const
    {
        return m_elements;
    }

    std::vector<unique_ptr<CPACSFuselageCutOut> >& CPACSFuselageCutOuts::GetElements()
    {
        return m_elements;
    }

    CPACSFuselageCutOut& CPACSFuselageCutOuts::AddElement()
    {
        m_elements.push_back(make_unique<CPACSFuselageCutOut>(m_uidMgr));
        return *m_elements.back();
    }

    void CPACSFuselageCutOuts::RemoveElement(CPACSFuselageCutOut& ref)
    {
        for (std::size_t i = 0; i < m_elements.size(); i++) {
            if (m_elements[i].get() == &ref) {
                m_elements.erase(m_elements.begin() + i);
                return;
            }
        }
        throw CTiglError("Element not found");
    }

} // namespace generated
} // namespace tigl
