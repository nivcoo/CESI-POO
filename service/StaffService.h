//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_STAFFSERVICE_H
#define MAIN_CPP_STAFFSERVICE_H

#include "../model/StaffModel.h"

class StaffService {
public:
    static int addStaff(string firstname, string lastname, SADateTime hireDate, string addressLine, string postalCode, string city, int idSuperior);

    static void updateStaffByID(int idStaff, string firstname, string lastname, SADateTime hireDate, int idSuperior);

    static void deleteStaffByID(int idStaff);

    static StaffModel::Staff getStaffByID(int id);

    static vector<StaffModel::Staff> getAllStaffs();

    static vector<StaffModel::Staff> getAllStaffsByFirstAndLastName(string firstname, string lastname);

    static int updateStaffAddress(int idStaff, string addressLine, string postalCode, string city);

};


#endif //MAIN_CPP_STAFFSERVICE_H
