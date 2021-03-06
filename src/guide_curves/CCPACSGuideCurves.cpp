/*
* Copyright (C) 2007-2014 German Aerospace Center (DLR/SC)
*
* Created: 2014-02-10 Tobias Stollenwerk <tobias.stollenwerk@dlr.de>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
* @file
* @brief  Implementation of CPACS guide curve container handling routines
*/

#include "CCPACSGuideCurves.h"
#include "CCPACSGuideCurve.h"


namespace tigl
{
CCPACSGuideCurves::CCPACSGuideCurves(CTiglUIDManager* uidMgr)
    : generated::CPACSGuideCurves(uidMgr) {}

namespace {
    struct UidCompare {
        bool operator()(const unique_ptr<CCPACSGuideCurve>& a, const unique_ptr<CCPACSGuideCurve>& b) {
            return a->GetUID() < b->GetUID();
        }
    };
}

void CCPACSGuideCurves::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) {
    generated::CPACSGuideCurves::ReadCPACS(tixiHandle, xpath);

    // sort by uid as some unit tests rely on this (TODO: should we fix the tests?)
    // WARN: this destroys the order of the guide curves as stored in the CPACS file
    std::sort(m_guideCurves.begin(), m_guideCurves.end(), UidCompare());
}

// Returns the total count of guide curves in this configuration
int CCPACSGuideCurves::GetGuideCurveCount() const
{
    return static_cast<int>(m_guideCurves.size());
}

// Returns the guide curve for a given index
const CCPACSGuideCurve& CCPACSGuideCurves::GetGuideCurve(int index) const
{
    index--;
    if (index < 0 || index >= GetGuideCurveCount()) {
        throw CTiglError("Invalid index in CCPACSGuideCurves::GetGuideCurve", TIGL_INDEX_ERROR);
    }
    return *m_guideCurves[index];
}

// Returns the guide curve for a given index
CCPACSGuideCurve& CCPACSGuideCurves::GetGuideCurve(int index)
{
    return const_cast<CCPACSGuideCurve&>(static_cast<const CCPACSGuideCurves*>(this)->GetGuideCurve(index));
}

// Returns the guide curve for a given uid.
const CCPACSGuideCurve& CCPACSGuideCurves::GetGuideCurve(std::string uid) const
{
    for (std::size_t i = 0; i < m_guideCurves.size(); i++) {
        if (m_guideCurves[i]->GetUID() == uid) {
            return *m_guideCurves[i];
        }
    }
    throw CTiglError("CCPACSGuideCurve::GetGuideCurve: Guide curve \"" + uid + "\" not found in CPACS file!", TIGL_UID_ERROR);
}

// Returns the guide curve for a given uid.
CCPACSGuideCurve& CCPACSGuideCurves::GetGuideCurve(std::string uid)
{
    return const_cast<CCPACSGuideCurve&>(static_cast<const CCPACSGuideCurves*>(this)->GetGuideCurve(uid));
}

// Returns the guide curve for a given uid.
bool CCPACSGuideCurves::GuideCurveExists(std::string uid) const
{
    for (std::size_t i = 0; i < m_guideCurves.size(); i++) {
        if (m_guideCurves[i]->GetUID() == uid) {
            return true;
        }
    }
    return false;
}


} // end namespace tigl


