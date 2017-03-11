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

#include "TixiHelper.h"
#include "CTiglLogging.h"
#include "CTiglError.h"
#include "CPACSPositioning.h"

namespace tigl
{
    namespace generated
    {
        CPACSPositioning::CPACSPositioning(){}
        CPACSPositioning::~CPACSPositioning() {}
        
        void CPACSPositioning::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
            }
            
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
            }
            else {
                LOG(ERROR) << "Required element name is missing";
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
            }
            
            // read element length
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/length")) {
                m_length = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/length");
            }
            else {
                LOG(ERROR) << "Required element length is missing";
            }
            
            // read element sweepAngle
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sweepAngle")) {
                m_sweepAngle = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sweepAngle");
            }
            else {
                LOG(ERROR) << "Required element sweepAngle is missing";
            }
            
            // read element dihedralAngle
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/dihedralAngle")) {
                m_dihedralAngle = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/dihedralAngle");
            }
            else {
                LOG(ERROR) << "Required element dihedralAngle is missing";
            }
            
            // read element fromSectionUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fromSectionUID")) {
                m_fromSectionUID = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/fromSectionUID");
            }
            
            // read element toSectionUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/toSectionUID")) {
                m_toSectionUID = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/toSectionUID");
            }
            else {
                LOG(ERROR) << "Required element toSectionUID is missing";
            }
            
        }
        
        void CPACSPositioning::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            if (m_uID) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/uID");
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", *m_uID);
            }
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            }
            
            // write element length
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/length");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/length", m_length);
            
            // write element sweepAngle
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sweepAngle");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/sweepAngle", m_sweepAngle);
            
            // write element dihedralAngle
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/dihedralAngle");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/dihedralAngle", m_dihedralAngle);
            
            // write element fromSectionUID
            if (m_fromSectionUID) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/fromSectionUID");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/fromSectionUID", *m_fromSectionUID);
            }
            
            // write element toSectionUID
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/toSectionUID");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/toSectionUID", m_toSectionUID);
            
        }
        
        bool CPACSPositioning::HasUID() const
        {
            return static_cast<bool>(m_uID);
        }
        
        const std::string& CPACSPositioning::GetUID() const
        {
            return *m_uID;
        }
        
        void CPACSPositioning::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        const std::string& CPACSPositioning::GetName() const
        {
            return m_name;
        }
        
        void CPACSPositioning::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        bool CPACSPositioning::HasDescription() const
        {
            return static_cast<bool>(m_description);
        }
        
        const std::string& CPACSPositioning::GetDescription() const
        {
            return *m_description;
        }
        
        void CPACSPositioning::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        const double& CPACSPositioning::GetLength() const
        {
            return m_length;
        }
        
        void CPACSPositioning::SetLength(const double& value)
        {
            m_length = value;
        }
        
        const double& CPACSPositioning::GetSweepAngle() const
        {
            return m_sweepAngle;
        }
        
        void CPACSPositioning::SetSweepAngle(const double& value)
        {
            m_sweepAngle = value;
        }
        
        const double& CPACSPositioning::GetDihedralAngle() const
        {
            return m_dihedralAngle;
        }
        
        void CPACSPositioning::SetDihedralAngle(const double& value)
        {
            m_dihedralAngle = value;
        }
        
        bool CPACSPositioning::HasFromSectionUID() const
        {
            return static_cast<bool>(m_fromSectionUID);
        }
        
        const std::string& CPACSPositioning::GetFromSectionUID() const
        {
            return *m_fromSectionUID;
        }
        
        void CPACSPositioning::SetFromSectionUID(const std::string& value)
        {
            m_fromSectionUID = value;
        }
        
        const std::string& CPACSPositioning::GetToSectionUID() const
        {
            return m_toSectionUID;
        }
        
        void CPACSPositioning::SetToSectionUID(const std::string& value)
        {
            m_toSectionUID = value;
        }
        
    }
}
