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
#include "CCPACSFuselages.h"
#include "TixiHelper.h"
#include "CTiglLogging.h"
#include "CTiglError.h"
#include "CPACSFuselage.h"

namespace tigl
{
    namespace generated
    {
        CPACSFuselage::CPACSFuselage(CCPACSFuselages* parent) :
            m_segments(reinterpret_cast<CCPACSFuselage*>(this))
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSFuselage::~CPACSFuselage() {}
        
        CCPACSFuselages* CPACSFuselage::GetParent() const
        {
            return m_parent;
        }
        
        void CPACSFuselage::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
            }
            else {
                LOG(ERROR) << "Required attribute uID is missing";
            }
            
            // read attribute symmetry
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "symmetry")) {
                m_symmetry = stringToTiglSymmetryAxis(tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "symmetry"));
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
            
            // read element parentUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/parentUID")) {
                m_parentUID = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/parentUID");
            }
            
            // read element transformation
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/transformation")) {
                m_transformation.ReadCPACS(tixiHandle, xpath + "/transformation");
            }
            else {
                LOG(ERROR) << "Required element transformation is missing";
            }
            
            // read element sections
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sections")) {
                m_sections.ReadCPACS(tixiHandle, xpath + "/sections");
            }
            else {
                LOG(ERROR) << "Required element sections is missing";
            }
            
            // read element positionings
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/positionings")) {
                m_positionings.ReadCPACS(tixiHandle, xpath + "/positionings");
            }
            else {
                LOG(ERROR) << "Required element positionings is missing";
            }
            
            // read element segments
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/segments")) {
                m_segments.ReadCPACS(tixiHandle, xpath + "/segments");
            }
            else {
                LOG(ERROR) << "Required element segments is missing";
            }
            
            // read element cutOuts
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/cutOuts")) {
                m_cutOuts = boost::in_place();
                try {
                    m_cutOuts->ReadCPACS(tixiHandle, xpath + "/cutOuts");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read cutOuts at xpath << " << xpath << ": " << e.what();
                    m_cutOuts = boost::none;
                } catch(const CTiglError& e) {
                    LOG(ERROR) << "Failed to read cutOuts at xpath << " << xpath << ": " << e.getError();
                    m_cutOuts = boost::none;
                }
            }
            
        }
        
        void CPACSFuselage::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/uID");
            tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);
            
            // write attribute symmetry
            if (m_symmetry) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/symmetry");
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "symmetry", TiglSymmetryAxisToString(*m_symmetry));
            }
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            }
            
            // write element parentUID
            if (m_parentUID) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/parentUID");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/parentUID", *m_parentUID);
            }
            
            // write element transformation
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/transformation");
            m_transformation.WriteCPACS(tixiHandle, xpath + "/transformation");
            
            // write element sections
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sections");
            m_sections.WriteCPACS(tixiHandle, xpath + "/sections");
            
            // write element positionings
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/positionings");
            m_positionings.WriteCPACS(tixiHandle, xpath + "/positionings");
            
            // write element segments
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/segments");
            m_segments.WriteCPACS(tixiHandle, xpath + "/segments");
            
            // write element cutOuts
            if (m_cutOuts) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/cutOuts");
                m_cutOuts->WriteCPACS(tixiHandle, xpath + "/cutOuts");
            }
            
        }
        
        const std::string& CPACSFuselage::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSFuselage::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        bool CPACSFuselage::HasSymmetry() const
        {
            return static_cast<bool>(m_symmetry);
        }
        
        const TiglSymmetryAxis& CPACSFuselage::GetSymmetry() const
        {
            return *m_symmetry;
        }
        
        void CPACSFuselage::SetSymmetry(const TiglSymmetryAxis& value)
        {
            m_symmetry = value;
        }
        
        const std::string& CPACSFuselage::GetName() const
        {
            return m_name;
        }
        
        void CPACSFuselage::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        bool CPACSFuselage::HasDescription() const
        {
            return static_cast<bool>(m_description);
        }
        
        const std::string& CPACSFuselage::GetDescription() const
        {
            return *m_description;
        }
        
        void CPACSFuselage::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        bool CPACSFuselage::HasParentUID() const
        {
            return static_cast<bool>(m_parentUID);
        }
        
        const std::string& CPACSFuselage::GetParentUID() const
        {
            return *m_parentUID;
        }
        
        void CPACSFuselage::SetParentUID(const std::string& value)
        {
            m_parentUID = value;
        }
        
        const CCPACSTransformation& CPACSFuselage::GetTransformation() const
        {
            return m_transformation;
        }
        
        CCPACSTransformation& CPACSFuselage::GetTransformation()
        {
            return m_transformation;
        }
        
        const CCPACSFuselageSections& CPACSFuselage::GetSections() const
        {
            return m_sections;
        }
        
        CCPACSFuselageSections& CPACSFuselage::GetSections()
        {
            return m_sections;
        }
        
        const CCPACSPositionings& CPACSFuselage::GetPositionings() const
        {
            return m_positionings;
        }
        
        CCPACSPositionings& CPACSFuselage::GetPositionings()
        {
            return m_positionings;
        }
        
        const CCPACSFuselageSegments& CPACSFuselage::GetSegments() const
        {
            return m_segments;
        }
        
        CCPACSFuselageSegments& CPACSFuselage::GetSegments()
        {
            return m_segments;
        }
        
        bool CPACSFuselage::HasCutOuts() const
        {
            return static_cast<bool>(m_cutOuts);
        }
        
        const CPACSFuselageCutOuts& CPACSFuselage::GetCutOuts() const
        {
            return *m_cutOuts;
        }
        
        CPACSFuselageCutOuts& CPACSFuselage::GetCutOuts()
        {
            return *m_cutOuts;
        }
        
    }
}
