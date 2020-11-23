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

void StaffService::updateStaffByID(int idStaff, string firstname, string lastname, SADateTime hireDate, int idSuperior) {
    StaffModel::Staff staff = StaffModel::getStaffByID(idStaff);
    StaffModel::updateById(idStaff, firstname, lastname, hireDate, staff.idAddress, idSuperior);
}

void StaffService::deleteStaffByID(int idStaff) {
    StaffModel::deleteById(idStaff);
}

StaffModel::Staff StaffService::getStaffByID(int id) {
    return StaffModel::getStaffByID(id);
}

vector<StaffModel::Staff> StaffService::getAllStaffs() {
    return StaffModel::getAllStaffs();
}

vector<StaffModel::Staff> StaffService::getAllStaffsByFirstAndLastName(string firstname, string lastname) {
    return StaffModel::getAllStaffsByFirstAndLastName(firstname, lastname);
}

int StaffService::updateStaffAddress(int idStaff, string addressLine, string postalCode, string city) {
    int idNewAddress = AddressModel::insert(0, addressLine, postalCode, city);
    StaffModel::Staff staff = StaffModel::getStaffByID(idStaff);
    StaffModel::updateById(idStaff, staff.firstname, staff.lastname, staff.hireDate, idNewAddress, staff.idSuperior);
    AddressModel::archiveByID(staff.idAddress);
    return idNewAddress;
}
