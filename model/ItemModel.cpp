//
// Created by Nicolas on 20/11/2020.
//

#include "ItemModel.h"
#include "../ihm/IHM.h"

struct ItemModel::Item item;

int ItemModel::insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat, bool isAchived = false) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `item` VALUES (:1, :2, :3, :4, :5, :6, :7); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    cmd.Param(2).setAsString() = _TSA(name).c_str();
    cmd.Param(3).setAsInt64() = _TSA(resuplyThreshold);
    cmd.Param(4).setAsInt64() = _TSA(quantity);
    cmd.Param(5).setAsDouble() = _TSA(priceHt);
    cmd.Param(6).setAsDouble() = _TSA(vat);
    cmd.Param(7).setAsBool() = _TSA(isAchived);
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    IHM::get()->getDataBase()->closeConnection();
    return cmd[1].asInt64();
}

void ItemModel::archiveByID(string reference) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `item` SET `archived`=:1 WHERE `reference`=:2;");
    cmd.Param(1).setAsBool() = _TSA(true);
    cmd.Param(2).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}

void ItemModel::deleteByID(string reference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `item` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}

ItemModel::Item ItemModel::getItemByID(int id) {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `item` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = id;
    ModelManager::sendCMD(&cmd, false);

    while (cmd.FetchNext()) {
        item.id = cmd.Field("id").asInt64();
        item.reference = cmd.Field("reference").asString().GetMultiByteChars();
        item.name = cmd.Field("name").asString().GetMultiByteChars();
        item.resuplyThreshold = cmd.Field("resuplyThreshold").asInt64();
        item.quantity = cmd.Field("quantity").asInt64();
        item.priceHt = cmd.Field("priceHt").asDouble();
        item.vat = cmd.Field("vat").asDouble();
        item.isAchived = cmd.Field("isAchived").asBool();
    }
    IHM::get()->getDataBase()->closeConnection();
    return item;
}
