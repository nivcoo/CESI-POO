//
// Created by Nicolas on 25/11/2020.
//

#include "StatsModel.h"
#include "../ihm/IHM.h"
#include <vector>

struct StatsModel::Statistics Stats;
struct StatsModel::OrderItem orderItem;
struct StatsModel::OrderHistory orderHistory;

vector<StatsModel::OrderItem> StatsModel::getAllOrderItem() { //move to OrderModel ??
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__item`");
    ModelManager::sendCMD(&cmd, false);
    vector<StatsModel::OrderItem> Orders;
    while (cmd.FetchNext()) {
        orderItem.reference = cmd.Field("reference").asString().GetMultiByteChars();
        orderItem.referenceItem = cmd.Field("reference_item").asString().GetMultiByteChars();
        orderItem.quantity = cmd.Field("quantity").asInt64();
        orderItem.price = cmd.Field("price").asDouble();
        orderItem.vat = cmd.Field("vat").asDouble();
        Orders.push_back(orderItem);
    }
    IHM::get()->getDataBase()->closeConnection();
    return Orders;
}

vector<StatsModel::OrderHistory> StatsModel::getAllOrderHistory() { //move to OrderModel ??
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__history`");
    ModelManager::sendCMD(&cmd, false);
    vector<StatsModel::OrderHistory> Orders;
    while (cmd.FetchNext()) {
        orderHistory.reference = cmd.Field("reference").asString().GetMultiByteChars();
        orderHistory.estimatedDeliveryDate = cmd.Field("estimated_delivery_date").asString().GetMultiByteChars();
        orderHistory.createdAt = cmd.Field("created_at").asString().GetMultiByteChars();
        orderHistory.customerID = cmd.Field("id").asInt64();
        orderHistory.staffID = cmd.Field("id_staff").asInt64();
        orderHistory.deliveryAddressID = cmd.Field("id_address").asInt64();
        orderHistory.billingAddressID = cmd.Field("id_address_bill").asInt64();
        Orders.push_back(orderHistory);
    }
    IHM::get()->getDataBase()->closeConnection();
    return Orders;
}