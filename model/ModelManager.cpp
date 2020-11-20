//
// Created by Nicolas on 19/11/2020.
//

#include "ModelManager.h"
#include "../ihm/IHM.h"
#include "Item.h"
ModelManager::ModelManager(DataBase * db) : _db(db)  {
    initDB();
    initItemModel();
    //IHM::get().getModelManager()->getDataBase();

}

void ModelManager::initDB() {

    new Item();

}

void ModelManager::initItemModel() {

}

DataBase * ModelManager::getDataBase() {
    return _db;
}

ModelManager::~ModelManager() {
    delete _db;
}


