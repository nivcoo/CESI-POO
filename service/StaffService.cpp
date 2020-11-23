//
// Created by Nicolas on 20/11/2020.
//

#include "StaffService.h"
#include "../model/AddressModel.h"

int StaffService::addStaff(string firstname, string lastname, SADateTime hireDate, string addressLine,
                           string postalCode, string city, int idSuperior) {
    int idAddress = AddressModel::insert(0, addressLine, postalCode, city);
    int id = StaffModel::insert(firstname, lastname, hireDate, idAddress, idSuperior);
    return id;
}

void StaffService::updateStaff(int idStaff, string firstname, string lastname, SADateTime hireDate, int idSuperior) {
    StaffModel::Staff staff = StaffModel::getStaffByID(idStaff);
    StaffModel::updateById(idStaff, firstname, lastname, hireDate, staff.idAddress, idSuperior);
}

void StaffService::deleteStaff(int idStaff) {
    StaffModel::deleteById(idStaff);
}

StaffModel::Staff StaffService::getStaffById(int id) {
    StaffModel::Staff staff = StaffModel::getStaffByID(id);
    return staff;
}

vector<StaffModel::Staff> StaffService::getAllStaffs() {
    vector<StaffModel::Staff> staffs = StaffModel::getAllStaffs();
    return staffs;
}

vector<StaffModel::Staff> StaffService::getAllStaffsByFirstAndLastName(string firstname, string lastname) {
    vector<StaffModel::Staff> staffs = StaffModel::getAllStaffsByFirstAndLastName(firstname, lastname);
    return staffs;
}

int StaffService::updateStaffAddress(int idStaff, string addressLine, string postalCode, string city) {
    int idNewAddress = AddressModel::insert(0, addressLine, postalCode, city);
    StaffModel::Staff staff = StaffModel::getStaffByID(idStaff);
    StaffModel::updateById(idStaff, staff.firstname, staff.lastname, staff.hireDate, idNewAddress, staff.idSuperior);
    AddressModel::archiveByID(staff.idAddress);
    return idNewAddress;
}
