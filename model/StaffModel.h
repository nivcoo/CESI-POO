//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_STAFFMODEL_H
#define MAIN_CPP_STAFFMODEL_H


#include "../utils/DataBase.h"

class StaffModel {
public:
    void insert(string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

    void updateById(int id, string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

    void deleteById(int id);
};


#endif //MAIN_CPP_STAFFMODEL_H
