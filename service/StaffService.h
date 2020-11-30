//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_STAFFSERVICE_H
#define MAIN_CPP_STAFFSERVICE_H

#include "../model/StaffModel.h"

class StaffService {
public:

/**
 * Add staff
 * @param firstname
 * @param lastname
 * @param hireDate
 * @param idAddress
 * @param idSuperior
 * @return id corresponding to the staff inserted
 */
    static int addStaff(string firstname, string lastname, SADateTime hireDate, string addressLine, string postalCode,
                        string city, int idSuperior);

/**
 * Update staff
 * @param idStaff
 * @param firstname
 * @param lastname
 * @param hireDate
 * @param idAddress
 * @param idSuperior
 */
    static void updateStaffByID(int idStaff, string firstname, string lastname, SADateTime hireDate, int idSuperior);

/**
 * Delete a staff using the id
 * @param idStaff
 */
    static void deleteStaffByID(int idStaff);

/**
 * Get a staff by it's id
 * @param id
 * @return StaffModel::Staff struct that contain all data about a staff
 */
    static StaffModel::Staff getStaffByID(int id);

/**
 * Get all staffs
 * @return vector of StaffModel::Staff struct that contain all data about a staff
 */
    static vector<StaffModel::Staff> getAllStaffs();

/**
 * Get all staffs matching firstname & lastname
 * @param firstname
 * @param lastname
 * @return vector of StaffModel::Staff struct that contain all data about a staff
 */
    static vector<StaffModel::Staff> getAllStaffsByFirstAndLastName(string firstname, string lastname);

/**
 * Update staff address
 * @param idStaff
 * @param addressLine
 * @param postalCode
 * @param city
 * @return new address' id
 */
    static int updateStaffAddress(int idStaff, string addressLine, string postalCode, string city);

};


#endif //MAIN_CPP_STAFFSERVICE_H
