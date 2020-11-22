//
// Created by Nicolas on 20/11/2020.
//

#include "OrderItemModel.h"
#include "../../ihm/IHM.h"

void OrderItemModel::insert(string orderReference, string itemReference, int quantity, double price, double vat) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `order__item` VALUES (:1, :2, :3, :4, :5);");
    cmd.Param(1).setAsString() = _TSA(orderReference).c_str();
    cmd.Param(1).setAsString() = _TSA(itemReference).c_str();
    cmd.Param(4).setAsInt64() = _TSA(quantity);
    cmd.Param(7).setAsDouble() = _TSA(price);
    cmd.Param(7).setAsDouble() = _TSA(vat);
    ModelManager::sendCMD(&cmd);

}

void OrderItemModel::deleteById(string orderReference, string itemReference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `order__item` WHERE `reference` = :1 AND `reference_item` = :2;");
    cmd.Param(1).setAsString() = _TSA(orderReference).c_str();
    cmd.Param(1).setAsString() = _TSA(itemReference).c_str();
    ModelManager::sendCMD(&cmd);

}
