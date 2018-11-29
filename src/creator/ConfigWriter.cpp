//
// Created by cfse on 11/14/18.
//

#include "ConfigWriter.h"
#include "CreatorException.h"
#include "CCPACSFuselageSection.h"
#include "CCPACSWingSection.h"


cpcr::ConfigWriter::ConfigWriter() {
    tiglHandle = -1;

}

void cpcr::ConfigWriter::open(std::string filename, UID modelUID) {


    TixiDocumentHandle  tixiHandle = tixi::TixiOpenDocument(filename);
    TiglReturnCode tiglRet = tiglOpenCPACSConfiguration(tixiHandle, modelUID.c_str(),  &tiglHandle);
    if(tiglRet != TIGL_SUCCESS){
        tiglHandle = -1;
        throw CreatorException("ConfigWriter::open:: Error open tigl");
    }

    return ;
}


tigl::CCPACSConfiguration &cpcr::ConfigWriter::getConfiguration() {
    tigl::CCPACSConfigurationManager& manager = tigl::CCPACSConfigurationManager::GetInstance();
    return manager.GetConfiguration(tiglHandle);
}



tigl::CTiglTransformation cpcr::ConfigWriter::getTransformation(cpcr::UniqueXPath xpath) {

    tigl::CTiglTransformation r;

    if( ! isValidWithWarning() ){
        LOG(WARNING) << "ConfigWriter::getTransformation:: Impossible to get the transformation, the configWriter is not in a valid state!" << std::endl;
        return r;
    }

    try {
        r = this->getTransformationReference(xpath).getTransformationMatrix();
    }
    catch( const CreatorException& e){
        LOG(ERROR)  << "ConfigWriter::getTransformation throw error with message: "
                    << e.what()
                    << " Default CTiglTransformation will be returned!"
                    << std::endl;

    }
    return r;
}




void cpcr::ConfigWriter::setTransformation(cpcr::UniqueXPath xpath, tigl::CTiglTransformation newTransformation) {

    if( ! isValidWithWarning() ){
        LOG(WARNING) << "ConfigWriter::getTransformation:: Impossible to set the transformation, the configWriter is not in a valid state!" << std::endl;
        return;
    }


    try {

        tigl::CCPACSTransformation& refTransformation = this->getTransformationReference(xpath);
        refTransformation.setTransformationMatrix(newTransformation);
        tigl::CCPACSConfiguration & config = getConfiguration();
        std::string modelUID = config.GetUID();
        getConfiguration().WriteCPACS(modelUID);
    }
    catch( const CreatorException& e){
        LOG(ERROR)  << "ConfigWriter::getTransformation throw error with message: "
                    << e.what()
                    << " Nothing has changed!"
                    << std::endl;
    }

}



tigl::CCPACSTransformation &cpcr::ConfigWriter::getTransformationReference(cpcr::UniqueXPath xpath) {

    // go down until fuselages or wings
    while( (! xpath.isEmpty() )  && xpath.getFirstElementType() != "fuselages"  && xpath.getFirstElementType() != "wings" )  {
        xpath.popFirst();
    }

    if (xpath.isEmpty()){
        throw CreatorException("ConfigWriter::GetTransformationReference: Invalid xpath");
    }


    tigl::CCPACSConfiguration & config = getConfiguration();

    // fuselages cases
    if( xpath.getFirstElementType() == "fuselages"){

        xpath.walkSafely("fuselages");
        int fuselageIdx = xpath.walkSafely("fuselage");

        // fuselage[idx] transformation
        if(xpath.isEmpty()){
            return config.GetFuselage(fuselageIdx).GetTransformation();
        }

        xpath.walkSafely("sections");
        int sectionIdx = xpath.walkSafely("section");

        // fuselage[idx]/sections/section[idx] transformation
        if (xpath.isEmpty()){
            return config.GetFuselage(fuselageIdx).GetSections().GetSection(sectionIdx).GetTransformation();
        }

        xpath.walkSafely("elements");
        int elementIdx = xpath.walkSafely("element");


        // fuselage[idx]/sections/section[idx]/elements/element[idx] transformation
        if(xpath.isEmpty()){
            return config.GetFuselage(fuselageIdx).GetSections().GetSection(sectionIdx).GetElements().GetSectionElement(elementIdx).GetTransformation();
        }

        throw CreatorException("ConfigWriter::GetTransformationReference: Invalid xpath");
    }


    if( xpath.getFirstElementType() == "wings"){
        xpath.walkSafely("wings");
        int wingIdx = xpath.walkSafely("wing");

        // wing[idx] transformation
        if(xpath.isEmpty()){
            return config.GetWing(wingIdx).GetTransformation();
        }

        xpath.walkSafely("sections");
        int sectionIdx = xpath.walkSafely("section");

        // wing[idx]/sections/section[idx] transformation
        if (xpath.isEmpty()){
            return config.GetWing(wingIdx).GetSections().GetSection(sectionIdx).GetTransformation();
        }

        xpath.walkSafely("elements");
        int elementIdx = xpath.walkSafely("element");

        // wing[idx]/sections/section[idx]/elements/element[idx] transformation
        if(xpath.isEmpty()){
            return config.GetWing(wingIdx).GetSections().GetSection(sectionIdx).GetElements().GetSectionElement(elementIdx).GetTransformation();
        }

        throw CreatorException("ConfigWriter::GetTransformationReference: Invalid xpath");
    }

    throw CreatorException("ConfigWriter::GetTransformationReference: Invalid xpath");

}


void cpcr::ConfigWriter::save(std::string newFilname) {
/*
    if (!isValidWithWarning()) return;

    tiglSaveCPACSConfiguration(modelUID.c_str(), tiglHandle );
    TixiDocumentHandle tixiHandle = getConfiguration().GetTixiDocumentHandle();

    int ret = tixiSaveDocument(tixiHandle, newFilname.c_str());
    if( ret > 0){
        throw CreatorException("ConfigWriter::save:: Impossible to save file with the name: " + newFilname );
    }
    tixiCloseDocument(tixiHandle);
    filename = newFilname;
    // Is it ok for the cpacsconfigurationmanager
    tixiOpenDocument(filename.c_str(), &tixiHandle);
    */
}

void cpcr::ConfigWriter::save() {
    if(! isValidWithWarning() ){
        return;
    }
   // this->save(filename);
}


bool cpcr::ConfigWriter::isValidWithWarning() {

    if (isValid() ) {
        return true;
    } else {
        std::string msg = "ConfigWriter::isValidWithWarning:: The file is not valid or not open!";
        LOG(WARNING) << msg;
        return false;
    };
}



void cpcr::ConfigWriter::close() {
    tiglHandle = -1;

}


void cpcr::ConfigWriter::open(TiglCPACSConfigurationHandle newTiglHandle) {
    tiglHandle = newTiglHandle;
    if( ! isValid()){
        tiglHandle = -1;
        LOG(ERROR) << "ConfigWriter::open:: invalid new tiglHandle given" << std::endl;
    }
}

bool cpcr::ConfigWriter::isValid() {
    TiglBoolean isValid;
    tiglIsCPACSConfigurationHandleValid(tiglHandle, &isValid);
    if( isValid){
        return  true;
    }else{
        return false;
    }
}