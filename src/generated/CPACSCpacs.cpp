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

#include "CPACSCpacs.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSCpacs::CPACSCpacs(CTiglUIDManager* uidMgr)
        : m_uidMgr(uidMgr)
    {
    }

    CPACSCpacs::~CPACSCpacs()
    {
    }

    CTiglUIDManager& CPACSCpacs::GetUIDManager()
    {
        return *m_uidMgr;
    }

    const CTiglUIDManager& CPACSCpacs::GetUIDManager() const
    {
        return *m_uidMgr;
    }

    void CPACSCpacs::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read element header
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/header")) {
            m_header.ReadCPACS(tixiHandle, xpath + "/header");
        }
        else {
            LOG(ERROR) << "Required element header is missing at xpath " << xpath;
        }

        // read element vehicles
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/vehicles")) {
            m_vehicles = boost::in_place(m_uidMgr);
            try {
                m_vehicles->ReadCPACS(tixiHandle, xpath + "/vehicles");
            } catch(const std::exception& e) {
                LOG(ERROR) << "Failed to read vehicles at xpath " << xpath << ": " << e.what();
                m_vehicles = boost::none;
            }
        }

        // read element toolspecific
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/toolspecific")) {
            m_toolspecific = boost::in_place();
            try {
                m_toolspecific->ReadCPACS(tixiHandle, xpath + "/toolspecific");
            } catch(const std::exception& e) {
                LOG(ERROR) << "Failed to read toolspecific at xpath " << xpath << ": " << e.what();
                m_toolspecific = boost::none;
            }
        }

    }

    void CPACSCpacs::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write element header
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/header");
        m_header.WriteCPACS(tixiHandle, xpath + "/header");

        // write element vehicles
        if (m_vehicles) {
            tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/vehicles");
            m_vehicles->WriteCPACS(tixiHandle, xpath + "/vehicles");
        }
        else {
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/vehicles")) {
                tixi::TixiRemoveElement(tixiHandle, xpath + "/vehicles");
            }
        }

        // write element toolspecific
        if (m_toolspecific) {
            tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/toolspecific");
            m_toolspecific->WriteCPACS(tixiHandle, xpath + "/toolspecific");
        }
        else {
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/toolspecific")) {
                tixi::TixiRemoveElement(tixiHandle, xpath + "/toolspecific");
            }
        }

    }

    const CPACSHeader& CPACSCpacs::GetHeader() const
    {
        return m_header;
    }

    CPACSHeader& CPACSCpacs::GetHeader()
    {
        return m_header;
    }

    const boost::optional<CPACSVehicles>& CPACSCpacs::GetVehicles() const
    {
        return m_vehicles;
    }

    boost::optional<CPACSVehicles>& CPACSCpacs::GetVehicles()
    {
        return m_vehicles;
    }

    const boost::optional<CPACSToolspecific>& CPACSCpacs::GetToolspecific() const
    {
        return m_toolspecific;
    }

    boost::optional<CPACSToolspecific>& CPACSCpacs::GetToolspecific()
    {
        return m_toolspecific;
    }

    CPACSVehicles& CPACSCpacs::GetVehicles(CreateIfNotExistsTag)
    {
        if (!m_vehicles)
            m_vehicles = boost::in_place(m_uidMgr);
        return *m_vehicles;
    }

    void CPACSCpacs::RemoveVehicles()
    {
        m_vehicles = boost::none;
    }

    CPACSToolspecific& CPACSCpacs::GetToolspecific(CreateIfNotExistsTag)
    {
        if (!m_toolspecific)
            m_toolspecific = boost::in_place();
        return *m_toolspecific;
    }

    void CPACSCpacs::RemoveToolspecific()
    {
        m_toolspecific = boost::none;
    }

} // namespace generated
} // namespace tigl
