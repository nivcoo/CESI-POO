//
// Created by Nicolas on 20/11/2020.
//

#include "OrderItemModel.h"
#include "../ModelManager.h"

struct OrderItemModel::OrderItem orderItem;
void OrderItemModel::insert(string orderReference, string itemReference, int quantity, double price, double vat) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `order__item` VALUES (:1, :2, :3, :4, :5);");
    cmd.Param(1).setAsString() = _TSA(orderReference).c_str();
    cmd.Param(2).setAsString() = _TSA(itemReference).c_str();
    cmd.Param(3).setAsInt64() = _TSA(quantity);
    cmd.Param(4).setAsDouble() = _TSA(price);
    cmd.Param(5).setAsDouble() = _TSA(vat);
    ModelManager::sendCMD(&cmd);
}

vector<OrderItemModel::OrderItem> OrderItemModel::getAllOrderItem() {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__item`");
    ModelManager::sendCMD(&cmd, false);
    vector<OrderItemModel::OrderItem> orders;
    while (cmd.FetchNext()) {
        orderItem.reference = cmd.Field("reference").asString().GetMultiByteChars();
        orderItem.referenceItem = cmd.Field("reference_item").asString().GetMultiByteChars();
        orderItem.quantity = cmd.Field("quantity").asInt64();
        orderItem.price = cmd.Field("price").asDouble();
        orderItem.vat = cmd.Field("vat").asDouble();
        orders.push_back(orderItem);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return orders;
}

void OrderItemModel::deleteById(string orderReference, string itemReference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `order__item` WHERE `reference` = :1 AND `reference_item` = :2;");
    cmd.Param(1).setAsString() = _TSA(orderReference).c_str();
    cmd.Param(2).setAsString() = _TSA(itemReference).c_str();
    ModelManager::sendCMD(&cmd);

}

vector<OrderItemModel::OrderItem> OrderItemModel::getMostSellItem() {
    SACommand cmd;
    cmd.setCommandText("SELECT i.reference, i.name, SUM(order__item.quantity) as sum\n"
                       "    FROM order__item INNER JOIN item i on order__item.reference_item = i.reference\n"
                       "    GROUP BY reference_item\n"
                       "    ORDER BY sum DESC\n"
                       "    LIMIT 10;");
    ModelManager::sendCMD(&cmd, false);
    vector<OrderItemModel::OrderItem> orders;
    while (cmd.FetchNext()){
        orderItem.referenceItem = cmd.Field("reference").asString().GetMultiByteChars();
        orderItem.quantity = cmd.Field("sum").asString().GetMultiByteCharsLength();
        orders.push_back(orderItem);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return orders;
}

vector<OrderItemModel::OrderItem> OrderItemModel::getLeastSellItem() {
    SACommand cmd;
    cmd.setCommandText("SELECT i.reference, i.name, SUM(order__item.quantity) as sum\n"
                       "    FROM order__item INNER JOIN item i on order__item.reference_item = i.reference\n"
                       "    GROUP BY reference_item\n"
                       "    ORDER BY sum ASC\n"
                       "    LIMIT 10;");
    ModelManager::sendCMD(&cmd, false);
    vector<OrderItemModel::OrderItem> orders;
    while (cmd.FetchNext()){
        orderItem.referenceItem = cmd.Field("reference").asString().GetMultiByteChars();
        orderItem.quantity = cmd.Field("sum").asString().GetMultiByteCharsLength();
        orders.push_back(orderItem);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return orders;
}
