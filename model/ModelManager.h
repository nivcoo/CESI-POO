//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_MODELMANAGER_H
#define MAIN_CPP_MODELMANAGER_H


#include "../utils/DataBase.h"
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

class ModelManager {

public:
    ModelManager();
    ~ModelManager();


private:

    void initItemModel();

    void initDB();
};


#endif //MAIN_CPP_MODELMANAGER_H
