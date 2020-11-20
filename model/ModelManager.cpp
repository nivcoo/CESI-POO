//
// Created by Nicolas on 19/11/2020.
//

#include "ModelManager.h"
#include "../ihm/IHM.h"
#include "Item.h"

ModelManager::ModelManager() {
    initDB();
    initItemModel();
}

void ModelManager::initDB() {
    new Item();
}

void ModelManager::initItemModel() {

}

ModelManager::~ModelManager() {

}


