//
// Created by Nicolas on 20/11/2020.
//

#include "ItemModel.h"
#include "../ihm/IHM.h"

void ItemModel::insert(string reference, string name, int resuply_threshold, int quantity, int price_ht, int vat) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `item` VALUES (:1, :2, :3, :4, :5, :6, :7);");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    cmd.Param(2).setAsString() = _TSA(name).c_str();
    cmd.Param(3).setAsInt64() = _TSA(resuply_threshold);
    cmd.Param(4).setAsInt64() = _TSA(quantity);
    cmd.Param(5).setAsInt64() = _TSA(price_ht);
    cmd.Param(6).setAsInt64() = _TSA(vat);
    cmd.Param(7).setAsBool() = _TSA(false);
    this->send(&cmd);

}

void ItemModel::archiveByID(string reference) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `item` SET `archived`=:1 WHERE `reference`=:2;");
    cmd.Param(1).setAsBool() = _TSA(true);
    cmd.Param(2).setAsString() = _TSA(reference).c_str();
    this->send(&cmd);

}

void ItemModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(id);
    this->send(&cmd);

}

void ItemModel::send(SACommand *cmd) {
    DataBase *db = IHM::get()->getDataBase();
    db->connectAndExecuteCommand(cmd);
}