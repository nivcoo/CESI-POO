//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERMODEL_H
#define MAIN_CPP_CUSTOMERMODEL_H


#include "../utils/DataBase.h"

class CustomerModel {

public:
    static int insert(string firstname, string lastname, SADateTime birthDate);

    static void updateByID(int id, string firstname, string lastname, SADateTime birthDate);

    static void deleteByID(int id);

};


#endif //MAIN_CPP_CUSTOMERMODEL_H
