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
#include <CCPACSWingRibRotation.h>
#include <string>
#include <tixi.h>
#include "CPACSRibCrossingBehaviour.h"
#include "tigl_internal.h"

namespace tigl
{
    class CCPACSWingRibsDefinition;
    
    namespace generated
    {
        // This class is used in:
        // CPACSWingRibsDefinition
        
        // generated from /xsd:schema/xsd:complexType[928]
        class CPACSWingRibsPositioning
        {
        public:
            TIGL_EXPORT CPACSWingRibsPositioning(CCPACSWingRibsDefinition* parent);
            
            TIGL_EXPORT virtual ~CPACSWingRibsPositioning();
            
            TIGL_EXPORT CCPACSWingRibsDefinition* GetParent() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT bool ValidateChoices() const;
            
            TIGL_EXPORT virtual const std::string& GetRibReference() const;
            TIGL_EXPORT virtual void SetRibReference(const std::string& value);
            
            TIGL_EXPORT virtual const std::string& GetRibStart() const;
            TIGL_EXPORT virtual void SetRibStart(const std::string& value);
            
            TIGL_EXPORT virtual const std::string& GetRibEnd() const;
            TIGL_EXPORT virtual void SetRibEnd(const std::string& value);
            
            TIGL_EXPORT virtual const CPACSRibCrossingBehaviour& GetRibCrossingBehaviour() const;
            TIGL_EXPORT virtual void SetRibCrossingBehaviour(const CPACSRibCrossingBehaviour& value);
            
            TIGL_EXPORT virtual const CCPACSWingRibRotation& GetRibRotation() const;
            TIGL_EXPORT virtual CCPACSWingRibRotation& GetRibRotation();
            
            TIGL_EXPORT virtual const boost::optional<double>& GetEtaStart_choice1() const;
            TIGL_EXPORT virtual void SetEtaStart_choice1(const double& value);
            TIGL_EXPORT virtual void SetEtaStart_choice1(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetElementStartUID_choice2() const;
            TIGL_EXPORT virtual void SetElementStartUID_choice2(const std::string& value);
            TIGL_EXPORT virtual void SetElementStartUID_choice2(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetSparPositionStartUID_choice3() const;
            TIGL_EXPORT virtual void SetSparPositionStartUID_choice3(const std::string& value);
            TIGL_EXPORT virtual void SetSparPositionStartUID_choice3(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetEtaEnd_choice1() const;
            TIGL_EXPORT virtual void SetEtaEnd_choice1(const double& value);
            TIGL_EXPORT virtual void SetEtaEnd_choice1(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetElementEndUID_choice2() const;
            TIGL_EXPORT virtual void SetElementEndUID_choice2(const std::string& value);
            TIGL_EXPORT virtual void SetElementEndUID_choice2(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetSparPositionEndUID_choice3() const;
            TIGL_EXPORT virtual void SetSparPositionEndUID_choice3(const std::string& value);
            TIGL_EXPORT virtual void SetSparPositionEndUID_choice3(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetSpacing_choice1() const;
            TIGL_EXPORT virtual void SetSpacing_choice1(const double& value);
            TIGL_EXPORT virtual void SetSpacing_choice1(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const boost::optional<int>& GetNumberOfRibs_choice2() const;
            TIGL_EXPORT virtual void SetNumberOfRibs_choice2(const int& value);
            TIGL_EXPORT virtual void SetNumberOfRibs_choice2(const boost::optional<int>& value);
            
        protected:
            CCPACSWingRibsDefinition* m_parent;
            
            std::string                  m_ribReference;
            std::string                  m_ribStart;
            std::string                  m_ribEnd;
            CPACSRibCrossingBehaviour    m_ribCrossingBehaviour;
            CCPACSWingRibRotation        m_ribRotation;
            boost::optional<double>      m_etaStart_choice1;
            boost::optional<std::string> m_elementStartUID_choice2;
            boost::optional<std::string> m_sparPositionStartUID_choice3;
            boost::optional<double>      m_etaEnd_choice1;
            boost::optional<std::string> m_elementEndUID_choice2;
            boost::optional<std::string> m_sparPositionEndUID_choice3;
            boost::optional<double>      m_spacing_choice1;
            boost::optional<int>         m_numberOfRibs_choice2;
            
        private:
            #ifdef HAVE_CPP11
            CPACSWingRibsPositioning(const CPACSWingRibsPositioning&) = delete;
            CPACSWingRibsPositioning& operator=(const CPACSWingRibsPositioning&) = delete;
            
            CPACSWingRibsPositioning(CPACSWingRibsPositioning&&) = delete;
            CPACSWingRibsPositioning& operator=(CPACSWingRibsPositioning&&) = delete;
            #else
            CPACSWingRibsPositioning(const CPACSWingRibsPositioning&);
            CPACSWingRibsPositioning& operator=(const CPACSWingRibsPositioning&);
            #endif
        };
    }
    
    // CPACSWingRibsPositioning is customized, use type CCPACSWingRibsPositioning directly
}
