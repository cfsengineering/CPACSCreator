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
#include "CCPACSWingRibsPositioning.h"
#include "CPACSRibRotation.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSRibRotation::CPACSRibRotation(CCPACSWingRibsPositioning* parent) :
            m_z(0)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSRibRotation::~CPACSRibRotation() {}
        
        CCPACSWingRibsPositioning* CPACSRibRotation::GetParent() const
        {
            return m_parent;
        }
        
        void CPACSRibRotation::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element ribRotationReference
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/ribRotationReference")) {
                m_ribRotationReference = stringToCPACSRibRotation_ribRotationReference(tixi::TixiGetElement<std::string>(tixiHandle, xpath + "/ribRotationReference"));
            }
            
            // read element z
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/z")) {
                m_z = tixi::TixiGetElement<double>(tixiHandle, xpath + "/z");
            }
            else {
                LOG(ERROR) << "Required element z is missing at xpath " << xpath;
            }
            
        }
        
        void CPACSRibRotation::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element ribRotationReference
            if (m_ribRotationReference) {
                tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ribRotationReference");
                tixi::TixiSaveElement(tixiHandle, xpath + "/ribRotationReference", CPACSRibRotation_ribRotationReferenceToString(*m_ribRotationReference));
            } else {
                if (tixi::TixiCheckElement(tixiHandle, xpath + "/ribRotationReference")) {
                    tixi::TixiRemoveElement(tixiHandle, xpath + "/ribRotationReference");
                }
            }
            
            // write element z
            tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/z");
            tixi::TixiSaveElement(tixiHandle, xpath + "/z", m_z);
            
        }
        
        const boost::optional<CPACSRibRotation_ribRotationReference>& CPACSRibRotation::GetRibRotationReference() const
        {
            return m_ribRotationReference;
        }
        
        void CPACSRibRotation::SetRibRotationReference(const boost::optional<CPACSRibRotation_ribRotationReference>& value)
        {
            m_ribRotationReference = value;
        }
        
        const double& CPACSRibRotation::GetZ() const
        {
            return m_z;
        }
        
        void CPACSRibRotation::SetZ(const double& value)
        {
            m_z = value;
        }
        
    }
}
