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

#include <tixi.h>
#include <string>
#include "tigl_internal.h"
#include "CPACSRibCrossingBehaviour.h"

namespace tigl
{
    namespace generated
    {
        // This class is used in:
        // CPACSWingRibsPositioning
        
        // generated from /xsd:schema/xsd:complexType[916]/xsd:complexContent/xsd:extension/xsd:sequence/xsd:element[4]/xsd:complexType
        class CPACSWingRibsPositioning_ribCrossingBehaviour
        {
        public:
            TIGL_EXPORT CPACSWingRibsPositioning_ribCrossingBehaviour();
            TIGL_EXPORT virtual ~CPACSWingRibsPositioning_ribCrossingBehaviour();
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT const CPACSRibCrossingBehaviour& GetSimpleContent() const;
            TIGL_EXPORT void SetSimpleContent(const CPACSRibCrossingBehaviour& value);
            
        protected:
            CPACSRibCrossingBehaviour m_simpleContent;
            
        private:
            #ifdef HAVE_CPP11
            CPACSWingRibsPositioning_ribCrossingBehaviour(const CPACSWingRibsPositioning_ribCrossingBehaviour&) = delete;
            CPACSWingRibsPositioning_ribCrossingBehaviour& operator=(const CPACSWingRibsPositioning_ribCrossingBehaviour&) = delete;
            
            CPACSWingRibsPositioning_ribCrossingBehaviour(CPACSWingRibsPositioning_ribCrossingBehaviour&&) = delete;
            CPACSWingRibsPositioning_ribCrossingBehaviour& operator=(CPACSWingRibsPositioning_ribCrossingBehaviour&&) = delete;
            #else
            CPACSWingRibsPositioning_ribCrossingBehaviour(const CPACSWingRibsPositioning_ribCrossingBehaviour&);
            CPACSWingRibsPositioning_ribCrossingBehaviour& operator=(const CPACSWingRibsPositioning_ribCrossingBehaviour&);
            #endif
        };
    }
    
    // This type is not customized, create alias in tigl namespace
    #ifdef HAVE_CPP11
    using CCPACSWingRibsPositioning_ribCrossingBehaviour = generated::CPACSWingRibsPositioning_ribCrossingBehaviour;
    #else
    typedef generated::CPACSWingRibsPositioning_ribCrossingBehaviour CCPACSWingRibsPositioning_ribCrossingBehaviour;
    #endif
}
