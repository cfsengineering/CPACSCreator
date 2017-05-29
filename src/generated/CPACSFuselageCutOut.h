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
#include <string>
#include <tixi.h>
#include "CPACSFuselageCutOut_cutout.h"
#include "CPACSPointXYZ.h"
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    
    namespace generated
    {
        // This class is used in:
        // CPACSFuselageCutOuts
        
        // generated from /xsd:schema/xsd:complexType[359]
        class CPACSFuselageCutOut
        {
        public:
            TIGL_EXPORT CPACSFuselageCutOut(CTiglUIDManager* uidMgr);
            TIGL_EXPORT virtual ~CPACSFuselageCutOut();
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const std::string& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetName() const;
            TIGL_EXPORT virtual void SetName(const std::string& value);
            TIGL_EXPORT virtual void SetName(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
            TIGL_EXPORT virtual void SetDescription(const std::string& value);
            TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const double& GetPositionX() const;
            TIGL_EXPORT virtual void SetPositionX(const double& value);
            
            TIGL_EXPORT virtual const double& GetReferenceY() const;
            TIGL_EXPORT virtual void SetReferenceY(const double& value);
            
            TIGL_EXPORT virtual const double& GetReferenceZ() const;
            TIGL_EXPORT virtual void SetReferenceZ(const double& value);
            
            TIGL_EXPORT virtual const double& GetReferenceAngle() const;
            TIGL_EXPORT virtual void SetReferenceAngle(const double& value);
            
            TIGL_EXPORT virtual const CPACSPointXYZ& GetOrientationVector() const;
            TIGL_EXPORT virtual CPACSPointXYZ& GetOrientationVector();
            
            TIGL_EXPORT virtual const boost::optional<CPACSPointXYZ>& GetAlignmentVector() const;
            TIGL_EXPORT virtual boost::optional<CPACSPointXYZ>& GetAlignmentVector();
            
            TIGL_EXPORT virtual const double& GetDeltaY() const;
            TIGL_EXPORT virtual void SetDeltaY(const double& value);
            
            TIGL_EXPORT virtual const double& GetDeltaZ() const;
            TIGL_EXPORT virtual void SetDeltaZ(const double& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetDeltaY1() const;
            TIGL_EXPORT virtual void SetDeltaY1(const double& value);
            TIGL_EXPORT virtual void SetDeltaY1(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetDeltaZ1() const;
            TIGL_EXPORT virtual void SetDeltaZ1(const double& value);
            TIGL_EXPORT virtual void SetDeltaZ1(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const double& GetFilletRadius() const;
            TIGL_EXPORT virtual void SetFilletRadius(const double& value);
            
            TIGL_EXPORT virtual const CPACSFuselageCutOut_cutout& GetCutoutType() const;
            TIGL_EXPORT virtual void SetCutoutType(const CPACSFuselageCutOut_cutout& value);
            
        protected:
            CTiglUIDManager* m_uidMgr;
            
            std::string                    m_uID;
            boost::optional<std::string>   m_name;
            boost::optional<std::string>   m_description;
            double                         m_positionX;
            double                         m_referenceY;
            double                         m_referenceZ;
            double                         m_referenceAngle;
            CPACSPointXYZ                  m_orientationVector;
            boost::optional<CPACSPointXYZ> m_alignmentVector;
            double                         m_deltaY;
            double                         m_deltaZ;
            boost::optional<double>        m_deltaY1;
            boost::optional<double>        m_deltaZ1;
            double                         m_filletRadius;
            CPACSFuselageCutOut_cutout     m_cutoutType;
            
        private:
            #ifdef HAVE_CPP11
            CPACSFuselageCutOut(const CPACSFuselageCutOut&) = delete;
            CPACSFuselageCutOut& operator=(const CPACSFuselageCutOut&) = delete;
            
            CPACSFuselageCutOut(CPACSFuselageCutOut&&) = delete;
            CPACSFuselageCutOut& operator=(CPACSFuselageCutOut&&) = delete;
            #else
            CPACSFuselageCutOut(const CPACSFuselageCutOut&);
            CPACSFuselageCutOut& operator=(const CPACSFuselageCutOut&);
            #endif
        };
    }
    
    // Aliases in tigl namespace
    #ifdef HAVE_CPP11
    using CCPACSFuselageCutOut = generated::CPACSFuselageCutOut;
    #else
    typedef generated::CPACSFuselageCutOut CCPACSFuselageCutOut;
    #endif
}
