//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerModel.h"
#include "../ihm/IHM.h"


int CustomerModel::insert(string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer` VALUES (:1, :2, :3, :4); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsString() = _TSA(firstname).c_str();
    cmd.Param(3).setAsString() = _TSA(lastname).c_str();
    cmd.Param(4).setAsDateTime() = _TSA(birthDate);
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    IHM::get()->getDataBase()->closeConnection();
    return id;

    //cout <<  cmd[1].asString().GetMultiByteChars() << endl;


}

void CustomerModel::updateByID(int id, string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `customer` SET firstname=:1, lastname=:2, birth_date=:3 WHERE `id`=:4;");

    cmd.Param(1).setAsString() = _TSA(firstname).c_str();
    cmd.Param(2).setAsString() = _TSA(lastname).c_str();
    cmd.Param(3).setAsDateTime() = _TSA(birthDate);
    cmd.Param(4).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);

}

void CustomerModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);

}


