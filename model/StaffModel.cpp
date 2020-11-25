//
// Created by Nicolas on 20/11/2020.
//

#include "StaffModel.h"

#include "../ihm/IHM.h"

struct StaffModel::Staff staff;

int StaffModel::insert(string firstname, string lastname, SADateTime hireDate, int idAddress, int idSuperior) {

    SACommand cmd;
    cmd.setCommandText("INSERT INTO `staff` VALUES (:1, :2, :3, :4, :5, :6); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsString() = _TSA(firstname).c_str();
    cmd.Param(3).setAsString() = _TSA(lastname).c_str();
    cmd.Param(4).setAsDateTime() = _TSA(hireDate);
    cmd.Param(5).setAsInt64() = _TSA(idAddress);
    cmd.Param(6).setAsInt64() = _TSA(idSuperior);
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    IHM::get()->getDataBase()->closeConnection();
    return id;

}

void
StaffModel::updateById(int idStaff, string firstname, string lastname, SADateTime hireDate, int idAddress,
                       int idSuperior) {

    SACommand cmd;
    cmd.setCommandText(
            "UPDATE `staff` SET `firstname`=:1, `lastname`=:2, `hire_date`=:3, `id_address`=:4, `id_staff`=:5 WHERE `id`=:6;");
    cmd.Param(1).setAsString() = _TSA(firstname).c_str();
    cmd.Param(2).setAsString() = _TSA(lastname).c_str();
    cmd.Param(3).setAsDateTime() = _TSA(hireDate);
    cmd.Param(4).setAsInt64() = _TSA(idAddress);
    cmd.Param(5).setAsInt64() = _TSA(idSuperior);
    cmd.Param(6).setAsInt64() = _TSA(idStaff);
    ModelManager::sendCMD(&cmd);

}

void StaffModel::deleteById(int idStaff) {

    SACommand cmd;
    cmd.setCommandText("DELETE FROM `staff` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(idStaff);
    ModelManager::sendCMD(&cmd);

}

StaffModel::Staff StaffModel::getStaffByID(int id) {
    SACommand cmd;
    cmd.setCommandText("SELECT staff.*, a.address_line, a.city, a.postal_code FROM `staff` INNER JOIN address a on staff.id_address = a.id WHERE staff.id = :1;");
    cmd.Param(1).setAsInt64() = id;
    ModelManager::sendCMD(&cmd, false);

    while (cmd.FetchNext()) {
        staff.id = cmd.Field("id").asInt64();
        staff.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        staff.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        staff.hireDate = cmd.Field("hire_date").asDateTime();
        staff.addressLine = cmd.Field("address_line").asString().GetMultiByteChars();
        staff.city = cmd.Field("city").asString().GetMultiByteChars();
        staff.postalCode = cmd.Field("postal_code").asString().GetMultiByteChars();
        staff.idAddress = cmd.Field("id_address").asInt64();
        staff.idSuperior = cmd.Field("id_staff").asInt64();
    }
    IHM::get()->getDataBase()->closeConnection();
    return staff;
}

vector<StaffModel::Staff> StaffModel::getAllStaffs() {
    SACommand cmd;
    cmd.setCommandText("SELECT staff.*, a.address_line, a.city, a.postal_code FROM `staff` INNER JOIN address a on staff.id_address = a.id;");
    ModelManager::sendCMD(&cmd, false);

    vector<StaffModel::Staff> staffs;

    while (cmd.FetchNext()) {
        staff.id = cmd.Field("id").asInt64();

        staff.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        staff.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        staff.hireDate = cmd.Field("hire_date").asDateTime();
        staff.addressLine = cmd.Field("address_line").asString().GetMultiByteChars();
        staff.city = cmd.Field("city").asString().GetMultiByteChars();
        staff.postalCode = cmd.Field("postal_code").asString().GetMultiByteChars();
        staff.idAddress = cmd.Field("id_address").asInt64();
        staff.idSuperior = cmd.Field("id_staff").asInt64();
        staffs.push_back(staff);
    }
    IHM::get()->getDataBase()->closeConnection();
    return staffs;
}

vector<StaffModel::Staff> StaffModel::getAllStaffsByFirstAndLastName(string firstname, string lastname) {
    SACommand cmd;
    cmd.setCommandText("SELECT staff.*, a.address_line, a.city, a.postal_code FROM `staff` INNER JOIN address a on staff.id_address = a.id WHERE staff.firstname = :1 AND staff.lastname = :2;");
    cmd.Param(1).setAsString() = _TSA(firstname.c_str());
    cmd.Param(2).setAsString() = _TSA(lastname.c_str());
    ModelManager::sendCMD(&cmd, false);

    vector<StaffModel::Staff> staffs;

    while (cmd.FetchNext()) {
        staff.id = cmd.Field("id").asInt64();
        staff.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        staff.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        staff.hireDate = cmd.Field("hire_date").asDateTime();
        staff.addressLine = cmd.Field("address_line").asString().GetMultiByteChars();
        staff.city = cmd.Field("city").asString().GetMultiByteChars();
        staff.postalCode = cmd.Field("postal_code").asString().GetMultiByteChars();
        staff.idAddress = cmd.Field("id_address").asInt64();
        staff.idSuperior = cmd.Field("id_staff").asInt64();
        staffs.push_back(staff);
    }
    IHM::get()->getDataBase()->closeConnection();
    return staffs;
}

