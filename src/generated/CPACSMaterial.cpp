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

#include "CPACSPostFailure.h"
#include "TixiHelper.h"
#include "CTiglLogging.h"
#include "CTiglError.h"
#include "CPACSMaterial.h"

namespace tigl
{
    namespace generated
    {
        CPACSMaterial::CPACSMaterial(){}
        CPACSMaterial::~CPACSMaterial() {}
        
        void CPACSMaterial::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
            }
            
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
            }
            else {
                LOG(ERROR) << "Required element name is missing at xpath " << xpath;
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
            }
            
            // read element rho
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/rho")) {
                m_rho = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/rho");
            }
            else {
                LOG(ERROR) << "Required element rho is missing at xpath " << xpath;
            }
            
            // read element k11
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k11")) {
                m_k11 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k11");
            }
            else {
                LOG(ERROR) << "Required element k11 is missing at xpath " << xpath;
            }
            
            // read element k12
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k12")) {
                m_k12 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k12");
            }
            else {
                LOG(ERROR) << "Required element k12 is missing at xpath " << xpath;
            }
            
            // read element maxStrain
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/maxStrain")) {
                m_maxStrain = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/maxStrain");
            }
            
            // read element fatigueFactor
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fatigueFactor")) {
                m_fatigueFactor = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/fatigueFactor");
            }
            
            // read element postFailure
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/postFailure")) {
                tixihelper::TixiReadElements(tixiHandle, xpath + "/postFailure", m_postFailure);
            }
            
            // read element sig11
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11")) {
                m_sig11_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11");
            }
            
            // read element tau12
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tau12")) {
                m_tau12_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/tau12");
            }
            
            // read element sig11yieldT
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11yieldT")) {
                m_sig11yieldT_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11yieldT");
            }
            
            // read element sig11yieldC
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11yieldC")) {
                m_sig11yieldC_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11yieldC");
            }
            
            // read element k22
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k22")) {
                m_k22_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k22");
            }
            
            // read element k23
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k23")) {
                m_k23_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k23");
            }
            
            // read element k66
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k66")) {
                m_k66_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k66");
            }
            
            // read element sig11t
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11t")) {
                m_sig11t_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11t");
            }
            
            // read element sig11c
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11c")) {
                m_sig11c_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11c");
            }
            
            // read element sig22t
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig22t")) {
                m_sig22t_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig22t");
            }
            
            // read element sig22c
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig22c")) {
                m_sig22c_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig22c");
            }
            
            // read element tau12
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tau12")) {
                m_tau12_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/tau12");
            }
            
            // read element tau23
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tau23")) {
                m_tau23_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/tau23");
            }
            
            // read element k13
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k13")) {
                m_k13_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k13");
            }
            
            // read element k22
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k22")) {
                m_k22_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k22");
            }
            
            // read element k23
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k23")) {
                m_k23_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k23");
            }
            
            // read element k33
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k33")) {
                m_k33_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k33");
            }
            
            // read element k44
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k44")) {
                m_k44_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k44");
            }
            
            // read element k55
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k55")) {
                m_k55_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k55");
            }
            
            // read element k66
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/k66")) {
                m_k66_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/k66");
            }
            
            // read element sig11t
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11t")) {
                m_sig11t_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11t");
            }
            
            // read element sig11c
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig11c")) {
                m_sig11c_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig11c");
            }
            
            // read element sig22t
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig22t")) {
                m_sig22t_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig22t");
            }
            
            // read element sig22c
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig22c")) {
                m_sig22c_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig22c");
            }
            
            // read element sig33t
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig33t")) {
                m_sig33t_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig33t");
            }
            
            // read element sig33c
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sig33c")) {
                m_sig33c_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/sig33c");
            }
            
            // read element tau12
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tau12")) {
                m_tau12_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/tau12");
            }
            
            // read element tau13
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tau13")) {
                m_tau13_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/tau13");
            }
            
            // read element tau23
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/tau23")) {
                m_tau23_choice3 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/tau23");
            }
            
        }
        
        void CPACSMaterial::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            if (m_uID) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/uID");
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", *m_uID);
            }
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            }
            
            // write element rho
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/rho");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/rho", m_rho);
            
            // write element k11
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k11");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/k11", m_k11);
            
            // write element k12
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k12");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/k12", m_k12);
            
            // write element maxStrain
            if (m_maxStrain) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/maxStrain");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/maxStrain", *m_maxStrain);
            }
            
            // write element fatigueFactor
            if (m_fatigueFactor) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/fatigueFactor");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/fatigueFactor", *m_fatigueFactor);
            }
            
            // write element postFailure
            tixihelper::TixiSaveElements(tixiHandle, xpath + "/postFailure", m_postFailure);
            
            // write element sig11
            if (m_sig11_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11", *m_sig11_choice1);
            }
            
            // write element tau12
            if (m_tau12_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tau12");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/tau12", *m_tau12_choice1);
            }
            
            // write element sig11yieldT
            if (m_sig11yieldT_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11yieldT");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11yieldT", *m_sig11yieldT_choice1);
            }
            
            // write element sig11yieldC
            if (m_sig11yieldC_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11yieldC");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11yieldC", *m_sig11yieldC_choice1);
            }
            
            // write element k22
            if (m_k22_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k22");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k22", *m_k22_choice2);
            }
            
            // write element k23
            if (m_k23_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k23");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k23", *m_k23_choice2);
            }
            
            // write element k66
            if (m_k66_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k66");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k66", *m_k66_choice2);
            }
            
            // write element sig11t
            if (m_sig11t_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11t");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11t", *m_sig11t_choice2);
            }
            
            // write element sig11c
            if (m_sig11c_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11c");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11c", *m_sig11c_choice2);
            }
            
            // write element sig22t
            if (m_sig22t_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig22t");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig22t", *m_sig22t_choice2);
            }
            
            // write element sig22c
            if (m_sig22c_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig22c");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig22c", *m_sig22c_choice2);
            }
            
            // write element tau12
            if (m_tau12_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tau12");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/tau12", *m_tau12_choice2);
            }
            
            // write element tau23
            if (m_tau23_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tau23");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/tau23", *m_tau23_choice2);
            }
            
            // write element k13
            if (m_k13_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k13");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k13", *m_k13_choice3);
            }
            
            // write element k22
            if (m_k22_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k22");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k22", *m_k22_choice3);
            }
            
            // write element k23
            if (m_k23_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k23");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k23", *m_k23_choice3);
            }
            
            // write element k33
            if (m_k33_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k33");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k33", *m_k33_choice3);
            }
            
            // write element k44
            if (m_k44_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k44");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k44", *m_k44_choice3);
            }
            
            // write element k55
            if (m_k55_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k55");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k55", *m_k55_choice3);
            }
            
            // write element k66
            if (m_k66_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/k66");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/k66", *m_k66_choice3);
            }
            
            // write element sig11t
            if (m_sig11t_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11t");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11t", *m_sig11t_choice3);
            }
            
            // write element sig11c
            if (m_sig11c_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig11c");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig11c", *m_sig11c_choice3);
            }
            
            // write element sig22t
            if (m_sig22t_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig22t");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig22t", *m_sig22t_choice3);
            }
            
            // write element sig22c
            if (m_sig22c_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig22c");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig22c", *m_sig22c_choice3);
            }
            
            // write element sig33t
            if (m_sig33t_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig33t");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig33t", *m_sig33t_choice3);
            }
            
            // write element sig33c
            if (m_sig33c_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sig33c");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/sig33c", *m_sig33c_choice3);
            }
            
            // write element tau12
            if (m_tau12_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tau12");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/tau12", *m_tau12_choice3);
            }
            
            // write element tau13
            if (m_tau13_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tau13");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/tau13", *m_tau13_choice3);
            }
            
            // write element tau23
            if (m_tau23_choice3) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/tau23");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/tau23", *m_tau23_choice3);
            }
            
        }
        
        bool CPACSMaterial::HasUID() const
        {
            return static_cast<bool>(m_uID);
        }
        
        const std::string& CPACSMaterial::GetUID() const
        {
            return *m_uID;
        }
        
        void CPACSMaterial::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        const std::string& CPACSMaterial::GetName() const
        {
            return m_name;
        }
        
        void CPACSMaterial::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        bool CPACSMaterial::HasDescription() const
        {
            return static_cast<bool>(m_description);
        }
        
        const std::string& CPACSMaterial::GetDescription() const
        {
            return *m_description;
        }
        
        void CPACSMaterial::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        const double& CPACSMaterial::GetRho() const
        {
            return m_rho;
        }
        
        void CPACSMaterial::SetRho(const double& value)
        {
            m_rho = value;
        }
        
        const double& CPACSMaterial::GetK11() const
        {
            return m_k11;
        }
        
        void CPACSMaterial::SetK11(const double& value)
        {
            m_k11 = value;
        }
        
        const double& CPACSMaterial::GetK12() const
        {
            return m_k12;
        }
        
        void CPACSMaterial::SetK12(const double& value)
        {
            m_k12 = value;
        }
        
        bool CPACSMaterial::HasMaxStrain() const
        {
            return static_cast<bool>(m_maxStrain);
        }
        
        const double& CPACSMaterial::GetMaxStrain() const
        {
            return *m_maxStrain;
        }
        
        void CPACSMaterial::SetMaxStrain(const double& value)
        {
            m_maxStrain = value;
        }
        
        bool CPACSMaterial::HasFatigueFactor() const
        {
            return static_cast<bool>(m_fatigueFactor);
        }
        
        const double& CPACSMaterial::GetFatigueFactor() const
        {
            return *m_fatigueFactor;
        }
        
        void CPACSMaterial::SetFatigueFactor(const double& value)
        {
            m_fatigueFactor = value;
        }
        
        const std::vector<unique_ptr<CPACSPostFailure> >& CPACSMaterial::GetPostFailure() const
        {
            return m_postFailure;
        }
        
        std::vector<unique_ptr<CPACSPostFailure> >& CPACSMaterial::GetPostFailure()
        {
            return m_postFailure;
        }
        
        bool CPACSMaterial::HasSig11_choice1() const
        {
            return static_cast<bool>(m_sig11_choice1);
        }
        
        const double& CPACSMaterial::GetSig11_choice1() const
        {
            return *m_sig11_choice1;
        }
        
        void CPACSMaterial::SetSig11_choice1(const double& value)
        {
            m_sig11_choice1 = value;
        }
        
        bool CPACSMaterial::HasTau12_choice1() const
        {
            return static_cast<bool>(m_tau12_choice1);
        }
        
        const double& CPACSMaterial::GetTau12_choice1() const
        {
            return *m_tau12_choice1;
        }
        
        void CPACSMaterial::SetTau12_choice1(const double& value)
        {
            m_tau12_choice1 = value;
        }
        
        bool CPACSMaterial::HasSig11yieldT_choice1() const
        {
            return static_cast<bool>(m_sig11yieldT_choice1);
        }
        
        const double& CPACSMaterial::GetSig11yieldT_choice1() const
        {
            return *m_sig11yieldT_choice1;
        }
        
        void CPACSMaterial::SetSig11yieldT_choice1(const double& value)
        {
            m_sig11yieldT_choice1 = value;
        }
        
        bool CPACSMaterial::HasSig11yieldC_choice1() const
        {
            return static_cast<bool>(m_sig11yieldC_choice1);
        }
        
        const double& CPACSMaterial::GetSig11yieldC_choice1() const
        {
            return *m_sig11yieldC_choice1;
        }
        
        void CPACSMaterial::SetSig11yieldC_choice1(const double& value)
        {
            m_sig11yieldC_choice1 = value;
        }
        
        bool CPACSMaterial::HasK22_choice2() const
        {
            return static_cast<bool>(m_k22_choice2);
        }
        
        const double& CPACSMaterial::GetK22_choice2() const
        {
            return *m_k22_choice2;
        }
        
        void CPACSMaterial::SetK22_choice2(const double& value)
        {
            m_k22_choice2 = value;
        }
        
        bool CPACSMaterial::HasK23_choice2() const
        {
            return static_cast<bool>(m_k23_choice2);
        }
        
        const double& CPACSMaterial::GetK23_choice2() const
        {
            return *m_k23_choice2;
        }
        
        void CPACSMaterial::SetK23_choice2(const double& value)
        {
            m_k23_choice2 = value;
        }
        
        bool CPACSMaterial::HasK66_choice2() const
        {
            return static_cast<bool>(m_k66_choice2);
        }
        
        const double& CPACSMaterial::GetK66_choice2() const
        {
            return *m_k66_choice2;
        }
        
        void CPACSMaterial::SetK66_choice2(const double& value)
        {
            m_k66_choice2 = value;
        }
        
        bool CPACSMaterial::HasSig11t_choice2() const
        {
            return static_cast<bool>(m_sig11t_choice2);
        }
        
        const double& CPACSMaterial::GetSig11t_choice2() const
        {
            return *m_sig11t_choice2;
        }
        
        void CPACSMaterial::SetSig11t_choice2(const double& value)
        {
            m_sig11t_choice2 = value;
        }
        
        bool CPACSMaterial::HasSig11c_choice2() const
        {
            return static_cast<bool>(m_sig11c_choice2);
        }
        
        const double& CPACSMaterial::GetSig11c_choice2() const
        {
            return *m_sig11c_choice2;
        }
        
        void CPACSMaterial::SetSig11c_choice2(const double& value)
        {
            m_sig11c_choice2 = value;
        }
        
        bool CPACSMaterial::HasSig22t_choice2() const
        {
            return static_cast<bool>(m_sig22t_choice2);
        }
        
        const double& CPACSMaterial::GetSig22t_choice2() const
        {
            return *m_sig22t_choice2;
        }
        
        void CPACSMaterial::SetSig22t_choice2(const double& value)
        {
            m_sig22t_choice2 = value;
        }
        
        bool CPACSMaterial::HasSig22c_choice2() const
        {
            return static_cast<bool>(m_sig22c_choice2);
        }
        
        const double& CPACSMaterial::GetSig22c_choice2() const
        {
            return *m_sig22c_choice2;
        }
        
        void CPACSMaterial::SetSig22c_choice2(const double& value)
        {
            m_sig22c_choice2 = value;
        }
        
        bool CPACSMaterial::HasTau12_choice2() const
        {
            return static_cast<bool>(m_tau12_choice2);
        }
        
        const double& CPACSMaterial::GetTau12_choice2() const
        {
            return *m_tau12_choice2;
        }
        
        void CPACSMaterial::SetTau12_choice2(const double& value)
        {
            m_tau12_choice2 = value;
        }
        
        bool CPACSMaterial::HasTau23_choice2() const
        {
            return static_cast<bool>(m_tau23_choice2);
        }
        
        const double& CPACSMaterial::GetTau23_choice2() const
        {
            return *m_tau23_choice2;
        }
        
        void CPACSMaterial::SetTau23_choice2(const double& value)
        {
            m_tau23_choice2 = value;
        }
        
        bool CPACSMaterial::HasK13_choice3() const
        {
            return static_cast<bool>(m_k13_choice3);
        }
        
        const double& CPACSMaterial::GetK13_choice3() const
        {
            return *m_k13_choice3;
        }
        
        void CPACSMaterial::SetK13_choice3(const double& value)
        {
            m_k13_choice3 = value;
        }
        
        bool CPACSMaterial::HasK22_choice3() const
        {
            return static_cast<bool>(m_k22_choice3);
        }
        
        const double& CPACSMaterial::GetK22_choice3() const
        {
            return *m_k22_choice3;
        }
        
        void CPACSMaterial::SetK22_choice3(const double& value)
        {
            m_k22_choice3 = value;
        }
        
        bool CPACSMaterial::HasK23_choice3() const
        {
            return static_cast<bool>(m_k23_choice3);
        }
        
        const double& CPACSMaterial::GetK23_choice3() const
        {
            return *m_k23_choice3;
        }
        
        void CPACSMaterial::SetK23_choice3(const double& value)
        {
            m_k23_choice3 = value;
        }
        
        bool CPACSMaterial::HasK33_choice3() const
        {
            return static_cast<bool>(m_k33_choice3);
        }
        
        const double& CPACSMaterial::GetK33_choice3() const
        {
            return *m_k33_choice3;
        }
        
        void CPACSMaterial::SetK33_choice3(const double& value)
        {
            m_k33_choice3 = value;
        }
        
        bool CPACSMaterial::HasK44_choice3() const
        {
            return static_cast<bool>(m_k44_choice3);
        }
        
        const double& CPACSMaterial::GetK44_choice3() const
        {
            return *m_k44_choice3;
        }
        
        void CPACSMaterial::SetK44_choice3(const double& value)
        {
            m_k44_choice3 = value;
        }
        
        bool CPACSMaterial::HasK55_choice3() const
        {
            return static_cast<bool>(m_k55_choice3);
        }
        
        const double& CPACSMaterial::GetK55_choice3() const
        {
            return *m_k55_choice3;
        }
        
        void CPACSMaterial::SetK55_choice3(const double& value)
        {
            m_k55_choice3 = value;
        }
        
        bool CPACSMaterial::HasK66_choice3() const
        {
            return static_cast<bool>(m_k66_choice3);
        }
        
        const double& CPACSMaterial::GetK66_choice3() const
        {
            return *m_k66_choice3;
        }
        
        void CPACSMaterial::SetK66_choice3(const double& value)
        {
            m_k66_choice3 = value;
        }
        
        bool CPACSMaterial::HasSig11t_choice3() const
        {
            return static_cast<bool>(m_sig11t_choice3);
        }
        
        const double& CPACSMaterial::GetSig11t_choice3() const
        {
            return *m_sig11t_choice3;
        }
        
        void CPACSMaterial::SetSig11t_choice3(const double& value)
        {
            m_sig11t_choice3 = value;
        }
        
        bool CPACSMaterial::HasSig11c_choice3() const
        {
            return static_cast<bool>(m_sig11c_choice3);
        }
        
        const double& CPACSMaterial::GetSig11c_choice3() const
        {
            return *m_sig11c_choice3;
        }
        
        void CPACSMaterial::SetSig11c_choice3(const double& value)
        {
            m_sig11c_choice3 = value;
        }
        
        bool CPACSMaterial::HasSig22t_choice3() const
        {
            return static_cast<bool>(m_sig22t_choice3);
        }
        
        const double& CPACSMaterial::GetSig22t_choice3() const
        {
            return *m_sig22t_choice3;
        }
        
        void CPACSMaterial::SetSig22t_choice3(const double& value)
        {
            m_sig22t_choice3 = value;
        }
        
        bool CPACSMaterial::HasSig22c_choice3() const
        {
            return static_cast<bool>(m_sig22c_choice3);
        }
        
        const double& CPACSMaterial::GetSig22c_choice3() const
        {
            return *m_sig22c_choice3;
        }
        
        void CPACSMaterial::SetSig22c_choice3(const double& value)
        {
            m_sig22c_choice3 = value;
        }
        
        bool CPACSMaterial::HasSig33t_choice3() const
        {
            return static_cast<bool>(m_sig33t_choice3);
        }
        
        const double& CPACSMaterial::GetSig33t_choice3() const
        {
            return *m_sig33t_choice3;
        }
        
        void CPACSMaterial::SetSig33t_choice3(const double& value)
        {
            m_sig33t_choice3 = value;
        }
        
        bool CPACSMaterial::HasSig33c_choice3() const
        {
            return static_cast<bool>(m_sig33c_choice3);
        }
        
        const double& CPACSMaterial::GetSig33c_choice3() const
        {
            return *m_sig33c_choice3;
        }
        
        void CPACSMaterial::SetSig33c_choice3(const double& value)
        {
            m_sig33c_choice3 = value;
        }
        
        bool CPACSMaterial::HasTau12_choice3() const
        {
            return static_cast<bool>(m_tau12_choice3);
        }
        
        const double& CPACSMaterial::GetTau12_choice3() const
        {
            return *m_tau12_choice3;
        }
        
        void CPACSMaterial::SetTau12_choice3(const double& value)
        {
            m_tau12_choice3 = value;
        }
        
        bool CPACSMaterial::HasTau13_choice3() const
        {
            return static_cast<bool>(m_tau13_choice3);
        }
        
        const double& CPACSMaterial::GetTau13_choice3() const
        {
            return *m_tau13_choice3;
        }
        
        void CPACSMaterial::SetTau13_choice3(const double& value)
        {
            m_tau13_choice3 = value;
        }
        
        bool CPACSMaterial::HasTau23_choice3() const
        {
            return static_cast<bool>(m_tau23_choice3);
        }
        
        const double& CPACSMaterial::GetTau23_choice3() const
        {
            return *m_tau23_choice3;
        }
        
        void CPACSMaterial::SetTau23_choice3(const double& value)
        {
            m_tau23_choice3 = value;
        }
        
    }
}
