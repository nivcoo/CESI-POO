//
// Created by Nicolas on 19/11/2020.
//


#include "IHM.h"

IHM IHM::INSTANCE = IHM();


IHM::IHM() {
    //INSTANCE = this;
    initDB();
}

void IHM::initDB() {
    DataBase * db = new DataBase("antoinelonne.dev", "poo", "cesi", "cesi-POO");
    _modelManager = new ModelManager(db);
}


ModelManager * IHM::getModelManager() {
    return _modelManager;
}

IHM &IHM::get() {
    return INSTANCE;
}

IHM::~IHM() {
    delete _modelManager;
}
