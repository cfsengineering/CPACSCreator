//
// Created by cfse on 3/20/18.
//

#include "CPACSCreatorAdapter.h"


void CPACSCreatorAdapter::prepareTransformationValues(CPACSOverTreeItem *item) {

    if(item == nullptr)
        return;

    if(item->getCpacsType() != "transformation"){
        return;
    }
    std::vector<double> scaling = creator.getPoint(item->getXPath() + "/scaling");
    std::vector<double> rotation = creator.getPoint(item->getXPath() + "/rotation" );
    std::vector<double> translation  = creator.getPoint(item->getXPath() + "/translation");

    QString xpath = QString(item->getXPath().c_str());

    std::cout << "Prepare transformation Values  recived: "<< scaling[0] << " " <<scaling[1]<< " " << scaling[2]  << std::endl;

    emit newTransformationValues(xpath,
                                 scaling[0], scaling[1], scaling[2],
                                 rotation[0], rotation[1], rotation[2],
                                 translation[0], translation[1], translation[2] );

}

void CPACSCreatorAdapter::setTransformation(QString xpath,
                                            double sx, double sy, double sz,
                                            double rx, double ry, double rz,
                                            double tx, double ty, double tz) {


    std::string xpathStd = xpath.toStdString();

    creator.setPoint(xpathStd + "/scaling", { sx, sy, sz});
    creator.setPoint(xpathStd + "/rotation", { rx, ry, rz});
    creator.setPoint(xpathStd + "/translation", { tx, ty, tz});


    std::cout << "Set transformation Values for xPath: "<< xpathStd << std::endl;

    creator.save();

}




void CPACSCreatorAdapter::resetCpacsConfig(const TIGLViewerDocument& doc) {
    QMutexLocker locker(&mutex); // ensure that the tree is not accessed during the creation

    creator = CPACSCreator();

    // Check if the new document is valid
    if(!doc.isConfigurationValid()){
        return;
    }

    // check rotorcraft
    tigl::CCPACSConfiguration& config = doc.GetConfiguration();
    if( config.IsRotorcraft() ){
        std::cout << "Rotorcraft is not supported by the tree viewer" << std::endl;
        return;
    }

    creator.open(doc.getLoadedDocumentFileName().toStdString(), config.GetUID() );
    creator.createRoot();

    return;

}

CSharedPtr<CPACSOverTreeItem> CPACSCreatorAdapter::getRoot()const {

    QMutexLocker locker(&mutex); // ensure that the tree is not accessed during the creation

    CSharedPtr<CPACSOverTreeItem> root = CSharedPtr<CPACSOverTreeItem>();
    root = creator.getRoot();
    return root;
}