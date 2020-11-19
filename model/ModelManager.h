//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_MODELMANAGER_H
#define MAIN_CPP_MODELMANAGER_H


#include "../utils/DataBase.h"

class ModelManager {

public:
    explicit ModelManager(DataBase *db);


private:

    DataBase *_db;

    void initItemModel();

    void initDB();
};


#endif //MAIN_CPP_MODELMANAGER_H
