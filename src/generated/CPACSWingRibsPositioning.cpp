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
#include "CCPACSWingRibsDefinition.h"
#include "TixiHelper.h"
#include "CTiglLogging.h"
#include "CTiglError.h"
#include "CPACSWingRibsPositioning.h"

namespace tigl
{
    namespace generated
    {
        CPACSWingRibsPositioning::CPACSWingRibsPositioning(CCPACSWingRibsDefinition* parent) :
            m_ribRotation(reinterpret_cast<CCPACSWingRibsPositioning*>(this))
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSWingRibsPositioning::~CPACSWingRibsPositioning() {}
        
        CCPACSWingRibsDefinition* CPACSWingRibsPositioning::GetParent() const
        {
            return m_parent;
        }
        
        void CPACSWingRibsPositioning::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element ribReference
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ribReference")) {
                m_ribReference = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/ribReference");
            }
            else {
                LOG(ERROR) << "Required element ribReference is missing at xpath " << xpath;
            }
            
            // read element ribStart
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ribStart")) {
                m_ribStart = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/ribStart");
            }
            else {
                LOG(ERROR) << "Required element ribStart is missing at xpath " << xpath;
            }
            
            // read element ribEnd
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ribEnd")) {
                m_ribEnd = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/ribEnd");
            }
            else {
                LOG(ERROR) << "Required element ribEnd is missing at xpath " << xpath;
            }
            
            // read element ribCrossingBehaviour
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ribCrossingBehaviour")) {
                m_ribCrossingBehaviour.ReadCPACS(tixiHandle, xpath + "/ribCrossingBehaviour");
            }
            else {
                LOG(ERROR) << "Required element ribCrossingBehaviour is missing at xpath " << xpath;
            }
            
            // read element ribRotation
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ribRotation")) {
                m_ribRotation.ReadCPACS(tixiHandle, xpath + "/ribRotation");
            }
            else {
                LOG(ERROR) << "Required element ribRotation is missing at xpath " << xpath;
            }
            
            // read element etaStart
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/etaStart")) {
                m_etaStart_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/etaStart");
            }
            
            // read element elementStartUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/elementStartUID")) {
                m_elementStartUID_choice2 = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/elementStartUID");
            }
            
            // read element etaEnd
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/etaEnd")) {
                m_etaEnd_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/etaEnd");
            }
            
            // read element elementEndUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/elementEndUID")) {
                m_elementEndUID_choice2 = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/elementEndUID");
            }
            
            // read element spacing
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/spacing")) {
                m_spacing_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/spacing");
            }
            
            // read element numberOfRibs
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/numberOfRibs")) {
                m_numberOfRibs_choice2 = tixihelper::TixiGetElement<int>(tixiHandle, xpath + "/numberOfRibs");
            }
            
        }
        
        void CPACSWingRibsPositioning::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element ribReference
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ribReference");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/ribReference", m_ribReference);
            
            // write element ribStart
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ribStart");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/ribStart", m_ribStart);
            
            // write element ribEnd
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ribEnd");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/ribEnd", m_ribEnd);
            
            // write element ribCrossingBehaviour
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ribCrossingBehaviour");
            m_ribCrossingBehaviour.WriteCPACS(tixiHandle, xpath + "/ribCrossingBehaviour");
            
            // write element ribRotation
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ribRotation");
            m_ribRotation.WriteCPACS(tixiHandle, xpath + "/ribRotation");
            
            // write element etaStart
            if (m_etaStart_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/etaStart");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/etaStart", *m_etaStart_choice1);
            }
            
            // write element elementStartUID
            if (m_elementStartUID_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/elementStartUID");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/elementStartUID", *m_elementStartUID_choice2);
            }
            
            // write element etaEnd
            if (m_etaEnd_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/etaEnd");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/etaEnd", *m_etaEnd_choice1);
            }
            
            // write element elementEndUID
            if (m_elementEndUID_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/elementEndUID");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/elementEndUID", *m_elementEndUID_choice2);
            }
            
            // write element spacing
            if (m_spacing_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/spacing");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/spacing", *m_spacing_choice1);
            }
            
            // write element numberOfRibs
            if (m_numberOfRibs_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/numberOfRibs");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/numberOfRibs", *m_numberOfRibs_choice2);
            }
            
        }
        
        const std::string& CPACSWingRibsPositioning::GetRibReference() const
        {
            return m_ribReference;
        }
        
        void CPACSWingRibsPositioning::SetRibReference(const std::string& value)
        {
            m_ribReference = value;
        }
        
        const std::string& CPACSWingRibsPositioning::GetRibStart() const
        {
            return m_ribStart;
        }
        
        void CPACSWingRibsPositioning::SetRibStart(const std::string& value)
        {
            m_ribStart = value;
        }
        
        const std::string& CPACSWingRibsPositioning::GetRibEnd() const
        {
            return m_ribEnd;
        }
        
        void CPACSWingRibsPositioning::SetRibEnd(const std::string& value)
        {
            m_ribEnd = value;
        }
        
        const CPACSWingRibsPositioning_ribCrossingBehaviour& CPACSWingRibsPositioning::GetRibCrossingBehaviour() const
        {
            return m_ribCrossingBehaviour;
        }
        
        CPACSWingRibsPositioning_ribCrossingBehaviour& CPACSWingRibsPositioning::GetRibCrossingBehaviour()
        {
            return m_ribCrossingBehaviour;
        }
        
        const CCPACSWingRibRotation& CPACSWingRibsPositioning::GetRibRotation() const
        {
            return m_ribRotation;
        }
        
        CCPACSWingRibRotation& CPACSWingRibsPositioning::GetRibRotation()
        {
            return m_ribRotation;
        }
        
        bool CPACSWingRibsPositioning::HasEtaStart_choice1() const
        {
            return static_cast<bool>(m_etaStart_choice1);
        }
        
        const double& CPACSWingRibsPositioning::GetEtaStart_choice1() const
        {
            return *m_etaStart_choice1;
        }
        
        void CPACSWingRibsPositioning::SetEtaStart_choice1(const double& value)
        {
            m_etaStart_choice1 = value;
        }
        
        bool CPACSWingRibsPositioning::HasElementStartUID_choice2() const
        {
            return static_cast<bool>(m_elementStartUID_choice2);
        }
        
        const std::string& CPACSWingRibsPositioning::GetElementStartUID_choice2() const
        {
            return *m_elementStartUID_choice2;
        }
        
        void CPACSWingRibsPositioning::SetElementStartUID_choice2(const std::string& value)
        {
            m_elementStartUID_choice2 = value;
        }
        
        bool CPACSWingRibsPositioning::HasEtaEnd_choice1() const
        {
            return static_cast<bool>(m_etaEnd_choice1);
        }
        
        const double& CPACSWingRibsPositioning::GetEtaEnd_choice1() const
        {
            return *m_etaEnd_choice1;
        }
        
        void CPACSWingRibsPositioning::SetEtaEnd_choice1(const double& value)
        {
            m_etaEnd_choice1 = value;
        }
        
        bool CPACSWingRibsPositioning::HasElementEndUID_choice2() const
        {
            return static_cast<bool>(m_elementEndUID_choice2);
        }
        
        const std::string& CPACSWingRibsPositioning::GetElementEndUID_choice2() const
        {
            return *m_elementEndUID_choice2;
        }
        
        void CPACSWingRibsPositioning::SetElementEndUID_choice2(const std::string& value)
        {
            m_elementEndUID_choice2 = value;
        }
        
        bool CPACSWingRibsPositioning::HasSpacing_choice1() const
        {
            return static_cast<bool>(m_spacing_choice1);
        }
        
        const double& CPACSWingRibsPositioning::GetSpacing_choice1() const
        {
            return *m_spacing_choice1;
        }
        
        void CPACSWingRibsPositioning::SetSpacing_choice1(const double& value)
        {
            m_spacing_choice1 = value;
        }
        
        bool CPACSWingRibsPositioning::HasNumberOfRibs_choice2() const
        {
            return static_cast<bool>(m_numberOfRibs_choice2);
        }
        
        const int& CPACSWingRibsPositioning::GetNumberOfRibs_choice2() const
        {
            return *m_numberOfRibs_choice2;
        }
        
        void CPACSWingRibsPositioning::SetNumberOfRibs_choice2(const int& value)
        {
            m_numberOfRibs_choice2 = value;
        }
        
    }
}
