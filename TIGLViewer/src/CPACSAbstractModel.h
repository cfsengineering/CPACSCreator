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
// Created by cfse on 3/13/18.
//

#ifndef TIGL_CPACSABSTRACTMODEL_H
#define TIGL_CPACSABSTRACTMODEL_H

#include <QAbstractItemModel>
#include <QtCore/QItemSelection>
#include <Quantity_Color.hxx>
#include <QMutex>

#include "CPACSCreatorAdapter.h"


#include "CPACSCreatorLib/AircraftTree.h"
#include "CPACSCreatorLib/CPACSTreeItem.h"


class CPACSAbstractModel: public QAbstractItemModel {

Q_OBJECT



signals:
    void selectionAsTreeItem(cpcr::CPACSTreeItem * treeItem);

public slots:

public:
    explicit CPACSAbstractModel( CPACSCreatorAdapter* adapter ,QObject *parent = 0);
    ~CPACSAbstractModel();

    // void initTree( TIGLViewerDocument& doc);

    // get the data
    QVariant data(const QModelIndex& index, int role) const override;

    // Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override ;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &index) const override;
    // count the number of child of a index
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // count the number of data a index hold
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;


    // Return true if there is a valid root
    bool isValid() const;

    void disconnectAdapter();

    void resetAdapter(CPACSCreatorAdapter* adapter );

    QModelIndex getIdxForUID(std::string uid );

    std::string getUidForIdx(QModelIndex idx);

    cpcr::CPACSTreeItem * getItemFromSelection(const QItemSelection & newSelection);

protected:


    // return the item for the given index
    // empty index is considered as the root index!
    cpcr::CPACSTreeItem * getItem( QModelIndex index) const;

    // return a index for the item
    QModelIndex getIndex( cpcr::CPACSTreeItem * item, int column ) const ;


private:

    // alternative to CPACS reader, take info form tigl instead from the xml directly
//    void initWingsFrom(tigl::CCPACSConfiguration &config);


    CPACSCreatorAdapter* creatorAdapter;
    QString currentFileName;    // filename of the displayed tree
    QString currentConfigUid;   // Uid of the display tree model

};


#endif //TIGL_CPACSABSTRACTMODEL_H
