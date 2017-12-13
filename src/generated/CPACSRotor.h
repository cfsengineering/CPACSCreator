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

#pragma once

#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <CCPACSRotorHub.h>
#include <CCPACSTransformation.h>
#include <string>
#include <TiglSymmetryAxis.h>
#include <tixi.h>
#include "CPACSRotor_type.h"
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    class CCPACSRotors;
    
    namespace generated
    {
        // This class is used in:
        // CPACSRotors
        
        // generated from /xsd:schema/xsd:complexType[771]
        class CPACSRotor
        {
        public:
            TIGL_EXPORT CPACSRotor(CCPACSRotors* parent, CTiglUIDManager* uidMgr);
            
            TIGL_EXPORT virtual ~CPACSRotor();
            
            TIGL_EXPORT CCPACSRotors* GetParent() const;
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const std::string& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            
            TIGL_EXPORT virtual const boost::optional<TiglSymmetryAxis>& GetSymmetry() const;
            TIGL_EXPORT virtual void SetSymmetry(const TiglSymmetryAxis& value);
            TIGL_EXPORT virtual void SetSymmetry(const boost::optional<TiglSymmetryAxis>& value);
            
            TIGL_EXPORT virtual const std::string& GetName() const;
            TIGL_EXPORT virtual void SetName(const std::string& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
            TIGL_EXPORT virtual void SetDescription(const std::string& value);
            TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetParentUID() const;
            TIGL_EXPORT virtual void SetParentUID(const std::string& value);
            TIGL_EXPORT virtual void SetParentUID(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<CPACSRotor_type>& GetType() const;
            TIGL_EXPORT virtual void SetType(const CPACSRotor_type& value);
            TIGL_EXPORT virtual void SetType(const boost::optional<CPACSRotor_type>& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetNominalRotationsPerMinute() const;
            TIGL_EXPORT virtual void SetNominalRotationsPerMinute(const double& value);
            TIGL_EXPORT virtual void SetNominalRotationsPerMinute(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const CCPACSTransformation& GetTransformation() const;
            TIGL_EXPORT virtual CCPACSTransformation& GetTransformation();
            
            TIGL_EXPORT virtual const CCPACSRotorHub& GetRotorHub() const;
            TIGL_EXPORT virtual CCPACSRotorHub& GetRotorHub();
            
        protected:
            CCPACSRotors* m_parent;
            
            CTiglUIDManager* m_uidMgr;
            
            std::string                       m_uID;
            boost::optional<TiglSymmetryAxis> m_symmetry;
            std::string                       m_name;
            boost::optional<std::string>      m_description;
            boost::optional<std::string>      m_parentUID;
            boost::optional<CPACSRotor_type>  m_type;
            boost::optional<double>           m_nominalRotationsPerMinute;
            CCPACSTransformation              m_transformation;
            CCPACSRotorHub                    m_rotorHub;
            
        private:
            #ifdef HAVE_CPP11
            CPACSRotor(const CPACSRotor&) = delete;
            CPACSRotor& operator=(const CPACSRotor&) = delete;
            
            CPACSRotor(CPACSRotor&&) = delete;
            CPACSRotor& operator=(CPACSRotor&&) = delete;
            #else
            CPACSRotor(const CPACSRotor&);
            CPACSRotor& operator=(const CPACSRotor&);
            #endif
        };
    }
    
    // CPACSRotor is customized, use type CCPACSRotor directly
}
