//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_STAFFMODEL_H
#define MAIN_CPP_STAFFMODEL_H

#include <iostream>
#include <SQLAPI.h>
using namespace std;

class StaffModel {
public:
    static int insert(string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

    static void updateById(int idStaff, string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

    static void deleteById(int idStaff);
};


#endif //MAIN_CPP_STAFFMODEL_H
