//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_IHM_H
#define MAIN_CPP_IHM_H

#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include "../utils/DataBase.h"
#include "../model/ModelManager.h"
class IHM {

public:
    IHM();
    ~IHM();
private:
    ModelManager * modelManager;
    DataBase * db;
    void initDB();
};


#endif //MAIN_CPP_IHM_H
