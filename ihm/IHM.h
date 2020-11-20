//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_IHM_H
#define MAIN_CPP_IHM_H

#include "../utils/DataBase.h"
#include "../model/ModelManager.h"

class IHM {

public:
    IHM();

    ~IHM();

    IHM(const IHM &other) = delete;

    static IHM *get();

    ModelManager *getModelManager();

    DataBase *getDataBase();


private:
    static IHM *INSTANCE;
    void initDB();
    ModelManager *_modelManager;
    DataBase *_db;

};


#endif //MAIN_CPP_IHM_H
