//
// Created by Nicolas on 19/11/2020.
//


#include "IHM.h"



IHM::IHM() {

    initDB();


}

IHM::~IHM() {
    delete db;
    delete modelManager;
}

void IHM::initDB() {

    db = new DataBase();
    modelManager = new ModelManager(db);


}
