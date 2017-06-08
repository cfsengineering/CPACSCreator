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

#include "CPACSGuideCurve.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSGuideCurve::CPACSGuideCurve(CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr), 
            m_toRelativeCircumference(0) {}
        
        CPACSGuideCurve::~CPACSGuideCurve()
        {
            if (m_uidMgr) m_uidMgr->TryUnregisterObject(m_uID);
        }
        
        CTiglUIDManager& CPACSGuideCurve::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSGuideCurve::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSGuideCurve::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
                if (m_uID.empty()) {
                    LOG(ERROR) << "Required attribute uID is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required attribute uID is missing at xpath " << xpath;
            }
            
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
                if (m_name.empty()) {
                    LOG(ERROR) << "Required element name is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element name is missing at xpath " << xpath;
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
                if (m_description->empty()) {
                    LOG(ERROR) << "Optional element description is present but empty at xpath " << xpath;
                }
            }
            
            // read element guideCurveProfileUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/guideCurveProfileUID")) {
                m_guideCurveProfileUID = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/guideCurveProfileUID");
                if (m_guideCurveProfileUID.empty()) {
                    LOG(ERROR) << "Required element guideCurveProfileUID is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element guideCurveProfileUID is missing at xpath " << xpath;
            }
            
            // read element fromGuideCurveUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fromGuideCurveUID")) {
                m_fromGuideCurveUID_choice1 = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/fromGuideCurveUID");
                if (m_fromGuideCurveUID_choice1->empty()) {
                    LOG(ERROR) << "Optional element fromGuideCurveUID is present but empty at xpath " << xpath;
                }
            }
            
            // read element continuity
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/continuity")) {
                m_continuity_choice1 = stringToCPACSGuideCurve_continuity(tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/continuity"));
            }
            
            // read element fromRelativeCircumference
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fromRelativeCircumference")) {
                m_fromRelativeCircumference_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/fromRelativeCircumference");
            }
            
            // read element tangent
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tangent")) {
                m_tangent_choice2 = boost::in_place(m_uidMgr);
                try {
                    m_tangent_choice2->ReadCPACS(tixiHandle, xpath + "/tangent");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read tangent at xpath " << xpath << ": " << e.what();
                    m_tangent_choice2 = boost::none;
                }
            }
            
            // read element toRelativeCircumference
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/toRelativeCircumference")) {
                m_toRelativeCircumference = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/toRelativeCircumference");
            }
            else {
                LOG(ERROR) << "Required element toRelativeCircumference is missing at xpath " << xpath;
            }
            
            // read element tangent
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tangent")) {
                m_tangent = boost::in_place(m_uidMgr);
                try {
                    m_tangent->ReadCPACS(tixiHandle, xpath + "/tangent");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read tangent at xpath " << xpath << ": " << e.what();
                    m_tangent = boost::none;
                }
            }
            
            if (m_uidMgr) m_uidMgr->RegisterObject(m_uID, *this);
            if (!ValidateChoices()) {
                LOG(ERROR) << "Invalid choice configuration at xpath " << xpath;
            }
        }
        
        void CPACSGuideCurve::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/description");
                }
            }
            
            // write element guideCurveProfileUID
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/guideCurveProfileUID");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/guideCurveProfileUID", m_guideCurveProfileUID);
            
            // write element fromGuideCurveUID
            if (m_fromGuideCurveUID_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/fromGuideCurveUID");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/fromGuideCurveUID", *m_fromGuideCurveUID_choice1);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fromGuideCurveUID")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/fromGuideCurveUID");
                }
            }
            
            // write element continuity
            if (m_continuity_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/continuity");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/continuity", CPACSGuideCurve_continuityToString(*m_continuity_choice1));
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/continuity")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/continuity");
                }
            }
            
            // write element fromRelativeCircumference
            if (m_fromRelativeCircumference_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/fromRelativeCircumference");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/fromRelativeCircumference", *m_fromRelativeCircumference_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fromRelativeCircumference")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/fromRelativeCircumference");
                }
            }
            
            // write element tangent
            if (m_tangent_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tangent");
                m_tangent_choice2->WriteCPACS(tixiHandle, xpath + "/tangent");
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tangent")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/tangent");
                }
            }
            
            // write element toRelativeCircumference
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/toRelativeCircumference");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/toRelativeCircumference", m_toRelativeCircumference);
            
            // write element tangent
            if (m_tangent) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tangent");
                m_tangent->WriteCPACS(tixiHandle, xpath + "/tangent");
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tangent")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/tangent");
                }
            }
            
        }
        
        bool CPACSGuideCurve::ValidateChoices() const
        {
            return ((m_fromGuideCurveUID_choice1.is_initialized()) + (m_fromRelativeCircumference_choice2.is_initialized()) == 1);
        }
        
        const std::string& CPACSGuideCurve::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSGuideCurve::SetUID(const std::string& value)
        {
            if (m_uidMgr) {
                m_uidMgr->TryUnregisterObject(m_uID);
                m_uidMgr->RegisterObject(value, *this);
            }
            m_uID = value;
        }
        
        const std::string& CPACSGuideCurve::GetName() const
        {
            return m_name;
        }
        
        void CPACSGuideCurve::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSGuideCurve::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSGuideCurve::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSGuideCurve::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const std::string& CPACSGuideCurve::GetGuideCurveProfileUID() const
        {
            return m_guideCurveProfileUID;
        }
        
        void CPACSGuideCurve::SetGuideCurveProfileUID(const std::string& value)
        {
            m_guideCurveProfileUID = value;
        }
        
        const boost::optional<std::string>& CPACSGuideCurve::GetFromGuideCurveUID_choice1() const
        {
            return m_fromGuideCurveUID_choice1;
        }
        
        void CPACSGuideCurve::SetFromGuideCurveUID_choice1(const std::string& value)
        {
            m_fromGuideCurveUID_choice1 = value;
        }
        
        void CPACSGuideCurve::SetFromGuideCurveUID_choice1(const boost::optional<std::string>& value)
        {
            m_fromGuideCurveUID_choice1 = value;
        }
        
        const boost::optional<CPACSGuideCurve_continuity>& CPACSGuideCurve::GetContinuity_choice1() const
        {
            return m_continuity_choice1;
        }
        
        void CPACSGuideCurve::SetContinuity_choice1(const CPACSGuideCurve_continuity& value)
        {
            m_continuity_choice1 = value;
        }
        
        void CPACSGuideCurve::SetContinuity_choice1(const boost::optional<CPACSGuideCurve_continuity>& value)
        {
            m_continuity_choice1 = value;
        }
        
        const boost::optional<double>& CPACSGuideCurve::GetFromRelativeCircumference_choice2() const
        {
            return m_fromRelativeCircumference_choice2;
        }
        
        void CPACSGuideCurve::SetFromRelativeCircumference_choice2(const double& value)
        {
            m_fromRelativeCircumference_choice2 = value;
        }
        
        void CPACSGuideCurve::SetFromRelativeCircumference_choice2(const boost::optional<double>& value)
        {
            m_fromRelativeCircumference_choice2 = value;
        }
        
        const boost::optional<CPACSPointXYZ>& CPACSGuideCurve::GetTangent_choice2() const
        {
            return m_tangent_choice2;
        }
        
        boost::optional<CPACSPointXYZ>& CPACSGuideCurve::GetTangent_choice2()
        {
            return m_tangent_choice2;
        }
        
        const double& CPACSGuideCurve::GetToRelativeCircumference() const
        {
            return m_toRelativeCircumference;
        }
        
        void CPACSGuideCurve::SetToRelativeCircumference(const double& value)
        {
            m_toRelativeCircumference = value;
        }
        
        const boost::optional<CPACSPointXYZ>& CPACSGuideCurve::GetTangent() const
        {
            return m_tangent;
        }
        
        boost::optional<CPACSPointXYZ>& CPACSGuideCurve::GetTangent()
        {
            return m_tangent;
        }
        
    }
}
