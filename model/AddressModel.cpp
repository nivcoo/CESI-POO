//
// Created by Nicolas on 20/11/2020.
//

#include "AddressModel.h"
#include "ModelManager.h"

struct AddressModel::Address address;

int AddressModel::insert(int type, string addressLine, string postalCode, string city) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `address` VALUES (:1, :2, :3, :4, :5, :6); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsInt64() = _TSA(type);
    cmd.Param(3).setAsString() = _TSA(addressLine).c_str();
    cmd.Param(4).setAsString() = _TSA(postalCode).c_str();
    cmd.Param(5).setAsString() = _TSA(city).c_str();
    cmd.Param(6).setAsBool() = false;
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    ModelManager::get()->getDataBase()->closeConnection();
    return id;
}

void AddressModel::archiveByID(int id) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `address` SET `archived` =:1 WHERE `id` = :2;");
    cmd.Param(1).setAsBool() = true;
    cmd.Param(2).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);

}
