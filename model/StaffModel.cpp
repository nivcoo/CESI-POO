//
// Created by Nicolas on 20/11/2020.
//

#include "StaffModel.h"

#include "../ihm/IHM.h"

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
