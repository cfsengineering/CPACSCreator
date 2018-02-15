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

#pragma once

#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <CCPACSRotorHinges.h>
#include <CCPACSStringVector.h>
#include <string>
#include <tixi.h>
#include "CreateIfNotExists.h"
#include "tigl_internal.h"

namespace tigl
{
class CTiglUIDManager;
class CCPACSRotorBladeAttachments;

namespace generated
{
    // This class is used in:
    // CPACSRotorBladeAttachments

    // generated from /xsd:schema/xsd:complexType[765]
    class CPACSRotorBladeAttachment
    {
    public:
        TIGL_EXPORT CPACSRotorBladeAttachment(CCPACSRotorBladeAttachments* parent, CTiglUIDManager* uidMgr);

        TIGL_EXPORT virtual ~CPACSRotorBladeAttachment();

        TIGL_EXPORT CCPACSRotorBladeAttachments* GetParent() const;

        TIGL_EXPORT CTiglUIDManager& GetUIDManager();
        TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;

        TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
        TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;

        TIGL_EXPORT bool ValidateChoices() const;

        TIGL_EXPORT virtual const std::string& GetUID() const;
        TIGL_EXPORT virtual void SetUID(const std::string& value);

        TIGL_EXPORT virtual const boost::optional<std::string>& GetName() const;
        TIGL_EXPORT virtual void SetName(const boost::optional<std::string>& value);

        TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
        TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);

        TIGL_EXPORT virtual const boost::optional<CCPACSRotorHinges>& GetHinges() const;
        TIGL_EXPORT virtual boost::optional<CCPACSRotorHinges>& GetHinges();

        TIGL_EXPORT virtual const std::string& GetRotorBladeUID() const;
        TIGL_EXPORT virtual void SetRotorBladeUID(const std::string& value);

        TIGL_EXPORT virtual const boost::optional<CCPACSStringVector>& GetAzimuthAngles_choice1() const;
        TIGL_EXPORT virtual boost::optional<CCPACSStringVector>& GetAzimuthAngles_choice1();

        TIGL_EXPORT virtual const boost::optional<int>& GetNumberOfBlades_choice2() const;
        TIGL_EXPORT virtual void SetNumberOfBlades_choice2(const boost::optional<int>& value);

        TIGL_EXPORT virtual CCPACSRotorHinges& GetHinges(CreateIfNotExistsTag);
        TIGL_EXPORT virtual void RemoveHinges();

        TIGL_EXPORT virtual CCPACSStringVector& GetAzimuthAngles_choice1(CreateIfNotExistsTag);
        TIGL_EXPORT virtual void RemoveAzimuthAngles_choice1();

    protected:
        CCPACSRotorBladeAttachments* m_parent;

        CTiglUIDManager* m_uidMgr;

        std::string                         m_uID;
        boost::optional<std::string>        m_name;
        boost::optional<std::string>        m_description;
        boost::optional<CCPACSRotorHinges>  m_hinges;
        std::string                         m_rotorBladeUID;
        boost::optional<CCPACSStringVector> m_azimuthAngles_choice1;
        boost::optional<int>                m_numberOfBlades_choice2;

    private:
#ifdef HAVE_CPP11
        CPACSRotorBladeAttachment(const CPACSRotorBladeAttachment&) = delete;
        CPACSRotorBladeAttachment& operator=(const CPACSRotorBladeAttachment&) = delete;

        CPACSRotorBladeAttachment(CPACSRotorBladeAttachment&&) = delete;
        CPACSRotorBladeAttachment& operator=(CPACSRotorBladeAttachment&&) = delete;
#else
        CPACSRotorBladeAttachment(const CPACSRotorBladeAttachment&);
        CPACSRotorBladeAttachment& operator=(const CPACSRotorBladeAttachment&);
#endif
    };
} // namespace generated

// CPACSRotorBladeAttachment is customized, use type CCPACSRotorBladeAttachment directly
} // namespace tigl
