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

#include "CPACSLinkToFile.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSLinkToFile::CPACSLinkToFile()
    {
    }

    CPACSLinkToFile::~CPACSLinkToFile()
    {
    }

    void CPACSLinkToFile::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read fundamental type base class 
        if (tixi::TixiCheckElement(tixiHandle, xpath)) {
            m_base = tixi::TixiGetElement<std::string>(tixiHandle, xpath);
            if (m_base.empty()) {
                LOG(WARNING) << "Required element  is empty at xpath " << xpath;
            }
        }
        else {
            LOG(ERROR) << "Required fundamental type base class  is missing at xpath " << xpath;
        }

        // read attribute format
        if (tixi::TixiCheckAttribute(tixiHandle, xpath, "format")) {
            m_format = stringToCPACSLinkToFileType_format(tixi::TixiGetAttribute<std::string>(tixiHandle, xpath, "format"));
        }

    }

    void CPACSLinkToFile::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write fundamental type base class 
        tixi::TixiSaveElement(tixiHandle, xpath, m_base);

        // write attribute format
        if (m_format) {
            tixi::TixiSaveAttribute(tixiHandle, xpath, "format", CPACSLinkToFileType_formatToString(*m_format));
        }
        else {
            if (tixi::TixiCheckAttribute(tixiHandle, xpath, "format")) {
                tixi::TixiRemoveAttribute(tixiHandle, xpath, "format");
            }
        }

    }

    const std::string& CPACSLinkToFile::GetBase() const
    {
        return m_base;
    }

    void CPACSLinkToFile::SetBase(const std::string& value)
    {
        m_base = value;
    }

    const boost::optional<CPACSLinkToFileType_format>& CPACSLinkToFile::GetFormat() const
    {
        return m_format;
    }

    void CPACSLinkToFile::SetFormat(const boost::optional<CPACSLinkToFileType_format>& value)
    {
        m_format = value;
    }

} // namespace generated
} // namespace tigl
