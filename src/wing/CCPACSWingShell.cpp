/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-05-28 Martin Siggel <Martin.Siggel@dlr.de>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "CCPACSWingShell.h"

#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiSaveExt.h"

namespace tigl 
{

CCPACSWingShell::CCPACSWingShell()
    : isvalid(false) {
}

int CCPACSWingShell::GetCellCount() const
{
    return m_cells.get().GetCellCount();
}

CCPACSWingCell& CCPACSWingShell::GetCell(int index)
{
    return m_cells->GetCell(index);
}

CCPACSMaterial& CCPACSWingShell::GetMaterial()
{
    return m_skin.GetMaterial();
}

void CCPACSWingShell::ReadCPACS(TixiDocumentHandle tixiHandle, const std::string &shellXPath)
{
    Invalidate();
    generated::CPACSWingShell::ReadCPACS(tixiHandle, shellXPath);
}

void CCPACSWingShell::Invalidate()
{
    isvalid = false;
}

bool CCPACSWingShell::IsValid() const
{
    return isvalid;
}

void CCPACSWingShell::Update()
{
    if (isvalid) {
        return;
    }

    // TODO: build stringer geometry

    isvalid = true;
}

} // namespace tigl
