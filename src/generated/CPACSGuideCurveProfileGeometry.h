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
#include <CCPACSPointListRelXYZ.h>
#include <string>
#include <TiglSymmetryAxis.h>
#include <tixi.h>
#include "tigl_internal.h"

namespace tigl
{
class CTiglUIDManager;

namespace generated
{
    // This class is used in:
    // CPACSGuideCurveProfiles

    // generated from /xsd:schema/xsd:complexType[433]
    /// @brief guideCurveProfileGeometryType
    /// 
    /// A guide curve profile is defined by a profile name, an
    /// optional description and a 3-dimensional relative pointlist with
    /// all three coordinates mandatory. For typical profiles, one of
    /// the coordinate vectors contains only "0" entries. All point
    /// coordinates are transferred to the global coordinate system.
    /// First and last point may, but need not to, be identical.
    /// The points have to be ordered in a mathematical
    /// positive sense.
    /// A profile can be symmetric. In that case the profile
    /// is interpreted as being not closed and will be closed by
    /// mirroring it on the symmetry plane.
    /// Curves have to go continuously over the whole wing or
    /// fuselage
    /// Connection of guide curves from segment to segment
    /// @see guideProfileWing
    /// @see guideProfileFuselage
    /// Please note, currently it is not possible to apply any
    /// means of class based transformation in the description. However,
    /// this may be an addition for the future.
    /// 
    class CPACSGuideCurveProfileGeometry
    {
    public:
        TIGL_EXPORT CPACSGuideCurveProfileGeometry(CTiglUIDManager* uidMgr);
        TIGL_EXPORT virtual ~CPACSGuideCurveProfileGeometry();

        TIGL_EXPORT CTiglUIDManager& GetUIDManager();
        TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;

        TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
        TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;

        TIGL_EXPORT virtual const boost::optional<TiglSymmetryAxis>& GetSymmetry() const;
        TIGL_EXPORT virtual void SetSymmetry(const boost::optional<TiglSymmetryAxis>& value);

        TIGL_EXPORT virtual const std::string& GetUID() const;
        TIGL_EXPORT virtual void SetUID(const std::string& value);

        TIGL_EXPORT virtual const std::string& GetName() const;
        TIGL_EXPORT virtual void SetName(const std::string& value);

        TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
        TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);

        TIGL_EXPORT virtual const CCPACSPointListRelXYZ& GetPointList() const;
        TIGL_EXPORT virtual CCPACSPointListRelXYZ& GetPointList();

    protected:
        CTiglUIDManager* m_uidMgr;

        boost::optional<TiglSymmetryAxis> m_symmetry;

        std::string                       m_uID;

        /// Name of profile
        std::string                       m_name;

        /// Description of profile
        boost::optional<std::string>      m_description;

        CCPACSPointListRelXYZ             m_pointList;

    private:
#ifdef HAVE_CPP11
        CPACSGuideCurveProfileGeometry(const CPACSGuideCurveProfileGeometry&) = delete;
        CPACSGuideCurveProfileGeometry& operator=(const CPACSGuideCurveProfileGeometry&) = delete;

        CPACSGuideCurveProfileGeometry(CPACSGuideCurveProfileGeometry&&) = delete;
        CPACSGuideCurveProfileGeometry& operator=(CPACSGuideCurveProfileGeometry&&) = delete;
#else
        CPACSGuideCurveProfileGeometry(const CPACSGuideCurveProfileGeometry&);
        CPACSGuideCurveProfileGeometry& operator=(const CPACSGuideCurveProfileGeometry&);
#endif
    };
} // namespace generated

// CPACSGuideCurveProfileGeometry is customized, use type CCPACSGuideCurveProfile directly
} // namespace tigl
