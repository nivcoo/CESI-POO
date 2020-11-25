//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_STAFFMODEL_H
#define MAIN_CPP_STAFFMODEL_H

#include <iostream>
#include <vector>
#include <SQLAPI.h>

using namespace std;

class StaffModel {
public:
    struct Staff {
        int id;
        string firstname, lastname, addressLine, city, postalCode;
        SADateTime hireDate;
        int idAddress, idSuperior;
    };

    static int insert(string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

    static void
    updateById(int idStaff, string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

    static void deleteById(int idStaff);

    static Staff getStaffByID(int id);

    static vector<Staff> getAllStaffs();

    static vector<Staff> getAllStaffsByFirstAndLastName(string firstname, string lastname);

};


#endif //MAIN_CPP_STAFFMODEL_H
