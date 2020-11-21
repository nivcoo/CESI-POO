//
// Created by Nicolas on 20/11/2020.
//

#include "ItemModel.h"
#include "../ihm/IHM.h"

void ItemModel::insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `item` VALUES (:1, :2, :3, :4, :5, :6, :7);");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    cmd.Param(2).setAsString() = _TSA(name).c_str();
    cmd.Param(3).setAsInt64() = _TSA(resuplyThreshold);
    cmd.Param(4).setAsDouble() = _TSA(quantity);
    cmd.Param(5).setAsDouble() = _TSA(priceHt);
    cmd.Param(6).setAsInt64() = _TSA(vat);
    cmd.Param(7).setAsBool() = _TSA(false);
    IHM::get()->getModelManager()->sendCMD(&cmd);
}

void ItemModel::archiveByID(string reference) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `item` SET `archived`=:1 WHERE `reference`=:2;");
    cmd.Param(1).setAsBool() = _TSA(true);
    cmd.Param(2).setAsString() = _TSA(reference).c_str();
    IHM::get()->getModelManager()->sendCMD(&cmd);

}

void ItemModel::deleteByID(string reference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    //this->send(&cmd);
    IHM::get()->getModelManager()->sendCMD(&cmd);

}
