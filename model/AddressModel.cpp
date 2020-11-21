//
// Created by Nicolas on 20/11/2020.
//

#include "AddressModel.h"
#include "../ihm/IHM.h"

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
    IHM::get()->getDataBase()->closeConnection();
    return id;
}

void AddressModel::updateByID(int id, int type, string addressLine, string postalCode, string city, bool archived) {
    SACommand cmd;
    cmd.setCommandText(
            "UPDATE `address` SET type=:1, address_line=:2, postal_code=:3, city=:4, archived=:5 WHERE `id`=:6;");

    cmd.Param(1).setAsInt64() = _TSA(type);
    cmd.Param(2).setAsString() = _TSA(addressLine).c_str();
    cmd.Param(3).setAsString() = _TSA(postalCode).c_str();
    cmd.Param(4).setAsString() = _TSA(city).c_str();
    cmd.Param(5).setAsBool() = _TSA(archived);
    cmd.Param(6).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);
}


void AddressModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `address` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);

}

void AddressModel::archiveAllType(int id, int type) {
    SACommand cmd;
    cmd.setCommandText("UPDATE table SET archived = :1 WHERE `id` = :2 AND `type` = :3;");
    cmd.Param(1).setAsBool() = true;
    cmd.Param(2).setAsInt64() = _TSA(id);
    cmd.Param(3).setAsInt64() = _TSA(type);
    ModelManager::sendCMD(&cmd);

}
