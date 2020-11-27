//
// Created by Nicolas on 20/11/2020.
//

#include "ItemModel.h"
#include "ModelManager.h"

struct ItemModel::Item item;

string ItemModel::insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat, bool achived) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `item` VALUES (:1, :2, :3, :4, :5, :6, :7); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    cmd.Param(2).setAsString() = _TSA(name).c_str();
    cmd.Param(3).setAsInt64() = _TSA(resuplyThreshold);
    cmd.Param(4).setAsInt64() = _TSA(quantity);
    cmd.Param(5).setAsDouble() = _TSA(priceHt);
    cmd.Param(6).setAsDouble() = _TSA(vat);
    cmd.Param(7).setAsBool() = _TSA(achived);
    ModelManager::sendCMD(&cmd);
    return reference;
}

void ItemModel::updateByREF(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `item` SET `name`=:1,`resuply_threshold`=:2,`quantity`=:3,`price_ht`=:4,`vat`=:5 WHERE `reference`=:6;");
    cmd.Param(1).setAsString() = _TSA(name.c_str());
    cmd.Param(2).setAsInt64() = _TSA(resuplyThreshold);
    cmd.Param(3).setAsInt64() = _TSA(quantity);
    cmd.Param(4).setAsDouble() = _TSA(priceHt);
    cmd.Param(5).setAsDouble() = _TSA(vat);
    cmd.Param(6).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}

void ItemModel::archiveByREF(string reference) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `item` SET `archived`=:1 WHERE `reference`=:2;");
    cmd.Param(1).setAsBool() = _TSA(true);
    cmd.Param(2).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}

void ItemModel::deleteByREF(string reference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `item` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}

vector<ItemModel::Item> ItemModel::getAllItems(){
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `item` WHERE `archived` = :1;");
    cmd.Param(1).setAsBool() = _TSA(false);
    ModelManager::sendCMD(&cmd, false);
    vector<ItemModel::Item> items;
    while (cmd.FetchNext()) {
        item.reference = cmd.Field("reference").asString().GetMultiByteChars();
        item.name = cmd.Field("name").asString().GetMultiByteChars();
        item.resuplyThreshold = cmd.Field("resuply_threshold").asInt64();
        item.quantity = cmd.Field("quantity").asInt64();
        item.priceHt = cmd.Field("price_ht").asDouble();
        item.vat = cmd.Field("vat").asDouble();
        item.archived = cmd.Field("archived").asBool();
        items.push_back(item);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return items;
}

ItemModel::Item ItemModel::getItemByREF(string reference) {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `item` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd, false);

    while (cmd.FetchNext()) {
        item.reference = cmd.Field("reference").asString().GetMultiByteChars();
        item.name = cmd.Field("name").asString().GetMultiByteChars();
        item.resuplyThreshold = cmd.Field("resuply_threshold").asInt64();
        item.quantity = cmd.Field("quantity").asInt64();
        item.priceHt = cmd.Field("price_ht").asDouble();
        item.vat = cmd.Field("vat").asDouble();
        item.archived = cmd.Field("archived").asBool();
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return item;
}

void ItemModel::updateQuantityOfItemREF(string reference, int newQuantity) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `item` SET `quantity`=:1 WHERE `reference`=:2;");
    cmd.Param(1).setAsInt64() = _TSA(newQuantity);
    cmd.Param(2).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);
}

vector<ItemModel::Item> ItemModel::getLowStockItems() {


    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `item` WHERE quantity <= resuply_threshold AND archived = :1;");
    cmd.Param(1).setAsBool() = _TSA(false);
    ModelManager::sendCMD(&cmd, false);
    vector<ItemModel::Item> items;
    while (cmd.FetchNext()) {
        item.reference = cmd.Field("reference").asString().GetMultiByteChars();
        item.name = cmd.Field("name").asString().GetMultiByteChars();
        item.resuplyThreshold = cmd.Field("resuply_threshold").asInt64();
        item.quantity = cmd.Field("quantity").asInt64();
        item.priceHt = cmd.Field("price_ht").asDouble();
        item.vat = cmd.Field("vat").asDouble();
        item.archived = cmd.Field("archived").asBool();
        items.push_back(item);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return items;
}
