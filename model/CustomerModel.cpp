//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerModel.h"
#include "../ihm/IHM.h"


void CustomerModel::insert(string firstname, string lastname, SADateTime birthDate) {
    DataBase *db = IHM::get()->getDataBase();
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer` VALUES (:1, :2, :3, :4);");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsString() = _TSA(firstname).c_str();
    cmd.Param(3).setAsString() = _TSA(lastname).c_str();
    cmd.Param(4).setAsDateTime() = birthDate;
    db->connectAndExecuteCommand(&cmd);
    db->closeConnection();

}

void CustomerModel::updateByID(int id, string firstname, string lastname, SADateTime birthDate) {

    DataBase *db = IHM::get()->getDataBase();
    SACommand cmd;
    cmd.setCommandText("UPDATE `customer` SET firstname=:1, lastname=:2, birth_date=:3 WHERE `id`=:4;");

    cmd.Param(1).setAsString() = _TSA(firstname).c_str();
    cmd.Param(2).setAsString() = _TSA(lastname).c_str();
    cmd.Param(3).setAsDateTime() = birthDate;
    cmd.Param(4).setAsLong() = id;
    db->connectAndExecuteCommand(&cmd);
    db->closeConnection();

}

void CustomerModel::deleteByID(int id) {

    DataBase *db = IHM::get()->getDataBase();
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsLong() = id;
    db->connectAndExecuteCommand(&cmd);
    db->closeConnection();

}

