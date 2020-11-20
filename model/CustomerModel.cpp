//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerModel.h"
#include "../ihm/IHM.h"


void CustomerModel::insert(string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer` VALUES (:1, :2, :3, :4);");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsString() = _TSA(firstname).c_str();
    cmd.Param(3).setAsString() = _TSA(lastname).c_str();
    cmd.Param(4).setAsDateTime() = birthDate;
    this->send(&cmd);

}

void CustomerModel::updateByID(int id, string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `customer` SET firstname=:1, lastname=:2, birth_date=:3 WHERE `id`=:4;");

    cmd.Param(1).setAsString() = _TSA(firstname).c_str();
    cmd.Param(2).setAsString() = _TSA(lastname).c_str();
    cmd.Param(3).setAsDateTime() = birthDate;
    cmd.Param(4).setAsLong() = id;
    this->send(&cmd);

}

void CustomerModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsLong() = id;
    this->send(&cmd);

}

void CustomerModel::send(SACommand * cmd) {
    DataBase *db = IHM::get()->getDataBase();
    db->connectAndExecuteCommand(cmd);
}

