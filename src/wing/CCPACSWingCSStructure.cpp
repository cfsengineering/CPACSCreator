/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-05-28 Martin Siggel <Martin.Siggel@dlr.de>
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

#include "CCPACSWingCSStructure.h"

#include "CTiglError.h"
#include "CTiglLogging.h"

#include "CCPACSWingCell.h"
#include "CCPACSWingSpars.h"
#include "CCPACSWingSparSegment.h"
#include "CCPACSWingSparSegments.h"
#include "CCPACSWingRibsDefinitions.h"
//#include "CCPACSTrailingEdgeDevice.h"

namespace tigl
{
CCPACSWingCSStructure::CCPACSWingCSStructure(CCPACSWingComponentSegment* parent)
    : generated::CPACSWingComponentSegmentStructure(parent) {}

//CCPACSWingCSStructure::CCPACSWingCSStructure(CPACSTrailingEdgeDevice* parent)
//    : generated::CPACSWingComponentSegmentStructure(parent) {}

CTiglWingStructureReference CCPACSWingCSStructure::GetWingStructureReference() {
    //if (IsParent<CCPACSWingComponentSegment>()) return CTiglWingStructureReference(*GetParent<CCPACSWingComponentSegment>());
    //throw std::logic_error("Unknown parent type of CCPACSWingCSStructure when retrieving CTiglWingStructureReference");
    return CTiglWingStructureReference(*GetParent());
}

const CTiglWingStructureReference CCPACSWingCSStructure::GetWingStructureReference() const {
    return const_cast<CCPACSWingCSStructure&>(*this).GetWingStructureReference();
}

bool CCPACSWingCSStructure::HasSpars() const {
    return static_cast<bool>(m_spars);
}

CCPACSWingSpars& CCPACSWingCSStructure::GetSpars() {
    if (!m_spars) {
        throw CTiglError("Error: spars not available but requested in CCPACSWingCSStructure::GetSpars!");
    }
    return *m_spars;
}

const CCPACSWingSpars& CCPACSWingCSStructure::GetSpars() const {
    if (!m_spars) {
        throw CTiglError("Error: spars not available but requested in CCPACSWingCSStructure::GetSpars!");
    }
    return *m_spars;
}

int CCPACSWingCSStructure::GetSparSegmentCount() const {
    int sparSegmentCount = 0;

    if (m_spars) {
        sparSegmentCount = m_spars->GetSparSegments().GetSparSegmentCount();
    }

    return sparSegmentCount;
}

CCPACSWingSparSegment& CCPACSWingCSStructure::GetSparSegment(int index) {
    if (!m_spars) {
        throw CTiglError("Error: no spars existing in CCPACSWingCSStructure::GetSparSegment!");
    }
    return m_spars->GetSparSegments().GetSparSegment(index);
}

CCPACSWingSparSegment& CCPACSWingCSStructure::GetSparSegment(const std::string& uid) {
    if (!m_spars) {
        throw CTiglError("Error: no spars existing in CCPACSWingCSStructure::GetSparSegment!");
    }
    return m_spars->GetSparSegments().GetSparSegment(uid);
}

const CCPACSWingSparSegment& CCPACSWingCSStructure::GetSparSegment(int index) const {
    if (!m_spars) {
        throw CTiglError("Error: no spars existing in CCPACSWingCSStructure::GetSparSegment!");
    }
    return m_spars->GetSparSegments().GetSparSegment(index);
}

const CCPACSWingSparSegment& CCPACSWingCSStructure::GetSparSegment(const std::string& uid) const {
    if (!m_spars) {
        throw CTiglError("Error: no spars existing in CCPACSWingCSStructure::GetSparSegment!");
    }
    return m_spars->GetSparSegments().GetSparSegment(uid);
}

bool CCPACSWingCSStructure::HasRibsDefinitions() const {
    return static_cast<bool>(m_ribsDefinitions);
}

int CCPACSWingCSStructure::GetRibsDefinitionCount() const {
    int ribsDefinitionCount = 0;

    if (m_ribsDefinitions) {
        ribsDefinitionCount = m_ribsDefinitions->GetRibsDefinitionCount();
    }

    return ribsDefinitionCount;
}

CCPACSWingRibsDefinition& CCPACSWingCSStructure::GetRibsDefinition(int index) {
    if (!m_ribsDefinitions) {
        throw CTiglError("Error: no ribsDefinitions existing in CCPACSWingCSStructure::GetRibsDefinition!");
    }
    return m_ribsDefinitions->GetRibsDefinition(index);
}

CCPACSWingRibsDefinition& CCPACSWingCSStructure::GetRibsDefinition(const std::string& uid) {
    if (!m_ribsDefinitions) {
        throw CTiglError("Error: no ribsDefinitions existing in CCPACSWingCSStructure::GetRibsDefinition!");
    }
    return m_ribsDefinitions->GetRibsDefinition(uid);
}

const CCPACSWingRibsDefinition& CCPACSWingCSStructure::GetRibsDefinition(int index) const {
    if (!m_ribsDefinitions) {
        throw CTiglError("Error: no ribsDefinitions existing in CCPACSWingCSStructure::GetRibsDefinition!");
    }
    return m_ribsDefinitions->GetRibsDefinition(index);
}

const CCPACSWingRibsDefinition& CCPACSWingCSStructure::GetRibsDefinition(const std::string& uid) const {
    if (!m_ribsDefinitions) {
        throw CTiglError("Error: no ribsDefinitions existing in CCPACSWingCSStructure::GetRibsDefinition!");
    }
    return m_ribsDefinitions->GetRibsDefinition(uid);
}


void CCPACSWingCSStructure::Invalidate()
{
    // forward invalidation
    if (m_spars) {
        m_spars->Invalidate();
    }
    if (m_ribsDefinitions) {
        m_ribsDefinitions->Invalidate();
    }
    m_upperShell.Invalidate();
    m_lowerShell.Invalidate();
}

} // namespace tigl
