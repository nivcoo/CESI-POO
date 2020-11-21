//
// Created by Nicolas on 20/11/2020.
//

#include "AddressModel.h"
#include "../ihm/IHM.h"

void AddressModel::insert(int type, string addressLine, string postalCode, string city, bool archived) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `address` VALUES (:1, :2, :3, :4, :5, :6);");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsInt64() = _TSA(type);
    cmd.Param(3).setAsString() = _TSA(addressLine).c_str();
    cmd.Param(4).setAsString() = _TSA(postalCode).c_str();
    cmd.Param(5).setAsString() = _TSA(city).c_str();
    cmd.Param(6).setAsBool() = _TSA(archived);
    this->send(&cmd);
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
    cmd.Param(6).setAsLong() = _TSA(id);
    this->send(&cmd);
}


void AddressModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `address` WHERE `id` = :1;");
    cmd.Param(1).setAsLong() = _TSA(id);
    this->send(&cmd);

}

void AddressModel::send(SACommand *cmd) {

    DataBase *db = IHM::get()->getDataBase();
    db->connectAndExecuteCommand(cmd);

}
