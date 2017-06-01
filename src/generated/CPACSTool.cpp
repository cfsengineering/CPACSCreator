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

#include "CPACSTool.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSTool::CPACSTool() {}
        
        CPACSTool::~CPACSTool() {}
        
        void CPACSTool::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
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
            
            // read element version
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/version")) {
                m_version = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/version");
                if (m_version.empty()) {
                    LOG(ERROR) << "Required element version is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element version is missing at xpath " << xpath;
            }
            
        }
        
        void CPACSTool::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element version
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/version");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/version", m_version);
            
        }
        
        const std::string& CPACSTool::GetName() const
        {
            return m_name;
        }
        
        void CPACSTool::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const std::string& CPACSTool::GetVersion() const
        {
            return m_version;
        }
        
        void CPACSTool::SetVersion(const std::string& value)
        {
            m_version = value;
        }
        
    }
}
