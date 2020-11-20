//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERMODEL_H
#define MAIN_CPP_CUSTOMERMODEL_H


#include "../utils/DataBase.h"
class CustomerModel {

public:
    void insert(string firstname, string lastname, SADateTime birthDate);
    void updateByID(int id, string firstname, string lastname, SADateTime birthDate);
    void deleteByID(int id);
private:
    void send(SACommand * cmd);
};


#endif //MAIN_CPP_CUSTOMERMODEL_H
