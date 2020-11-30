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

/**
 * Insert row in the staff table
 * @param firstname
 * @param lastname
 * @param hireDate
 * @param idAddress
 * @param idSuperior
 * @return id corresponding to the staff inserted
 */
    static int insert(string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

/**
 * Update row in the staff table
 * @param idStaff
 * @param firstname
 * @param lastname
 * @param hireDate
 * @param idAddress
 * @param idSuperior
 */
    static void
    updateById(int idStaff, string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior);

/**
 * Delete a row in the staff table using the id
 * @param idStaff
 */
    static void deleteById(int idStaff);

/**
 * Get a staff by it's id
 * @param id
 * @return StaffModel::Staff struct that contain all data about a staff
 */
    static Staff getStaffByID(int id);

    static vector<Staff> getAllStaffs();

/**
 * Get all staffs matching firstname & lastname
 * @param firstname
 * @param lastname
 * @return vector of StaffModel::Staff struct that contain all data about a staff
 */
    static vector<Staff> getAllStaffsByFirstAndLastName(string firstname, string lastname);

};


#endif //MAIN_CPP_STAFFMODEL_H
