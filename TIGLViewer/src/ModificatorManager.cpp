/*
* Copyright (C) 2018 CFS Engineering
*
* Created: 2018 Malo Drougard <malo.drougard@protonmail.com>
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
//
// Created by makem on 29/05/18.
//

#include "ModificatorManager.h"



ModificatorManager::ModificatorManager(CPACSCreatorAdapter *adapter,
                                       QWidget* widgetApply,
                                       TIGLViewerTransformationWidget* transformationModificator,
                                       TIGLViewerWingWidget* wingModificator,
                                       ProfilesDBManager* profilesDB,
                                       TIGLViewerPositioningsWidget* positioningsModificator) {
    this->adapter = adapter;
    this->profilesDB = profilesDB;
    this->widgetApply = widgetApply;
    this->commitButton = widgetApply->findChild<QPushButton*>("commitButton");
    this->cancelButton = widgetApply->findChild<QPushButton*>("cancelButton");
    this->transformationModificator = transformationModificator;
    this->transformationModificator->init(this);
    this->wingModificator = wingModificator;
    this->wingModificator->init(this);
    this->positioningsModificator = positioningsModificator;
    this->positioningsModificator->init(this);
    currentModificator = nullptr;

    this->hideAll();

}


void ModificatorManager::reset() {
    currentModificator = nullptr;
    this->hideAll();
}


void ModificatorManager::applyCurrentModifications(){
    if(currentModificator != nullptr) {
        currentModificator->apply();
    }
}



void ModificatorManager::applyCurrentCancellation() {
    if(currentModificator != nullptr){
        currentModificator->reset();
    }
}


void ModificatorManager::dispatch(cpcr::CPACSTreeItem *item) {

    if(item == nullptr) {
        LOG(ERROR) << "MODIFICATOR MANAGER GET A NULL ITEM";
    }
    else if(item->getType() == "transformation"){
        currentModificator = transformationModificator;
        this->setTransformationModificator(item);
    }
    else if(item->getType() == "wing"){
        currentModificator = wingModificator;
        this->setWingModificator(item);
    }
    else if (item->getType() == "positionings"){
        currentModificator = positioningsModificator;
        this->setPositioningsModificator(item);
    }
    else {
        currentModificator = nullptr;
        hideAll();
        LOG(INFO) <<  "MODIFICATOR MANAGER: item not suported";
    }
}


void ModificatorManager::setTransformationModificator(cpcr::CPACSTreeItem * item ) {

    hideAll();
    transformationModificator->setTransformation(item);
    transformationModificator->setVisible(true);
    widgetApply->setVisible(true);

}


void ModificatorManager::setWingModificator(cpcr::CPACSTreeItem *item) {
    hideAll();
    wingModificator->setWing(item);
    wingModificator->setVisible(true);
    widgetApply->setVisible(true);
}


void ModificatorManager::setPositioningsModificator(cpcr::CPACSTreeItem *item) {
    hideAll();
    positioningsModificator->setPositionings(item);
    positioningsModificator->setVisible(true);
    widgetApply->setVisible(true);
}

void ModificatorManager::hideAll() {
    bool visible = false;
    transformationModificator->setVisible(visible);
    wingModificator->setVisible(visible);
    positioningsModificator->setVisible(visible);
    widgetApply->setVisible(visible);

}
