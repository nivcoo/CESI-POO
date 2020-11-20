//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_MODELMANAGER_H
#define MAIN_CPP_MODELMANAGER_H


#include "../utils/DataBase.h"
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include "CustomerModel.h"

class ModelManager {

public:
    ModelManager();
    ~ModelManager();


private:

    void initItemModel();

    CustomerModel * _customerModel;

    void initDB();
};


#endif //MAIN_CPP_MODELMANAGER_H
