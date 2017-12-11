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

#include <CCPACSStringVector.h>
#include <string>
#include <tixi.h>
#include "tigl_internal.h"

namespace tigl
{
    namespace generated
    {
        // This class is used in:
        // CPACSProfileGeometry
        
        // generated from /xsd:schema/xsd:complexType[711]
        class CPACSPointListXYZVector
        {
        public:
            TIGL_EXPORT CPACSPointListXYZVector();
            TIGL_EXPORT virtual ~CPACSPointListXYZVector();
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const CCPACSStringVector& GetX() const;
            TIGL_EXPORT virtual CCPACSStringVector& GetX();
            
            TIGL_EXPORT virtual const CCPACSStringVector& GetY() const;
            TIGL_EXPORT virtual CCPACSStringVector& GetY();
            
            TIGL_EXPORT virtual const CCPACSStringVector& GetZ() const;
            TIGL_EXPORT virtual CCPACSStringVector& GetZ();
            
        protected:
            CCPACSStringVector m_x;
            CCPACSStringVector m_y;
            CCPACSStringVector m_z;
            
        private:
            #ifdef HAVE_CPP11
            CPACSPointListXYZVector(const CPACSPointListXYZVector&) = delete;
            CPACSPointListXYZVector& operator=(const CPACSPointListXYZVector&) = delete;
            
            CPACSPointListXYZVector(CPACSPointListXYZVector&&) = delete;
            CPACSPointListXYZVector& operator=(CPACSPointListXYZVector&&) = delete;
            #else
            CPACSPointListXYZVector(const CPACSPointListXYZVector&);
            CPACSPointListXYZVector& operator=(const CPACSPointListXYZVector&);
            #endif
        };
    }
    
    // CPACSPointListXYZVector is customized, use type CCPACSPointListXYZ directly
}
