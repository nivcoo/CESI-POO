//
// Created by Nicolas on 20/11/2020.
//

#include "OrderHistoryModel.h"
#include "../ModelManager.h"

struct OrderHistoryModel::Order order;

string OrderHistoryModel::insert(string reference, SADateTime estimatedDeliveryDate, int customerID, int staffID,
                                 int deliveryAddressID, int billingAddressID) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `order__history` VALUES (:1, :2, :3, :4, :5, :6, :7);");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    cmd.Param(2).setAsDateTime() = _TSA(estimatedDeliveryDate);
    cmd.Param(3).setAsDateTime() = SADateTime::currentDateTime();
    cmd.Param(4).setAsInt64() = _TSA(customerID);
    cmd.Param(5).setAsInt64() = _TSA(staffID);
    cmd.Param(6).setAsInt64() = _TSA(deliveryAddressID);
    cmd.Param(7).setAsInt64() = _TSA(billingAddressID);
    ModelManager::sendCMD(&cmd);
    return reference;

}

void OrderHistoryModel::updateEstimatedDeliveryDateByREF(string reference, SADateTime estimatedDeliveryDate) {
    SACommand cmd;
    cmd.setCommandText(
            "UPDATE `order__history` SET estimated_delivery_date=:1 WHERE `reference`=:2;");
    //here we use "<<" because the other method not work correctly with date
    cmd << _TSA(estimatedDeliveryDate) << _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);
}

void OrderHistoryModel::deleteByREF(string reference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `order__history` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}

OrderHistoryModel::Order OrderHistoryModel::getOrderByREF(string reference) {

    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__history` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd, false);

    while (cmd.FetchNext()) {
        order.reference = cmd.Field("reference").asString().GetMultiByteChars();
        order.estimatedDeliveryDate = cmd.Field("estimated_delivery_date").asDateTime();
        order.createdAt = cmd.Field("created_at").asDateTime();
        order.customerID = cmd.Field("id").asInt64();
        order.staffID = cmd.Field("id_staff").asInt64();
        order.deliveryAddressID = cmd.Field("id_address").asInt64();
        order.billingAddressID = cmd.Field("id_address_bill").asInt64();
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return order;
}

vector<OrderHistoryModel::Order> OrderHistoryModel::getAllOrdersByCustomerID(int customerID) {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__history` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(customerID);
    ModelManager::sendCMD(&cmd, false);
    vector<OrderHistoryModel::Order> orders;
    while (cmd.FetchNext()) {
        order.reference = cmd.Field("reference").asString().GetMultiByteChars();
        order.estimatedDeliveryDate = cmd.Field("estimated_delivery_date").asDateTime();
        order.createdAt = cmd.Field("created_at").asDateTime();
        order.customerID = cmd.Field("id").asInt64();
        order.staffID = cmd.Field("id_staff").asInt64();
        order.deliveryAddressID = cmd.Field("id_address").asInt64();
        order.billingAddressID = cmd.Field("id_address_bill").asInt64();
        orders.push_back(order);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return orders;
}

vector<OrderHistoryModel::Order> OrderHistoryModel::getLastOrdersByNumber(int number) {

    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__history` ORDER by created_at DESC LIMIT :1;");
    cmd.Param(1).setAsInt64() = _TSA(number);
    cmd.setOption(SACMD_PREFETCH_ROWS) = number;
    ModelManager::sendCMD(&cmd, false);
    vector<OrderHistoryModel::Order> orders;
    while (cmd.FetchNext()) {
        order.reference = cmd.Field("reference").asString().GetMultiByteChars();
        order.estimatedDeliveryDate = cmd.Field("estimated_delivery_date").asDateTime();
        order.createdAt = cmd.Field("created_at").asDateTime();
        order.customerID = cmd.Field("id").asInt64();
        order.staffID = cmd.Field("id_staff").asInt64();
        order.deliveryAddressID = cmd.Field("id_address").asInt64();
        order.billingAddressID = cmd.Field("id_address_bill").asInt64();
        orders.push_back(order);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return orders;
}


vector<OrderHistoryModel::Order> OrderHistoryModel::getAllOrders() {

    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `order__history`;");
    ModelManager::sendCMD(&cmd, false);
    vector<OrderHistoryModel::Order> orders;
    while (cmd.FetchNext()) {
        order.reference = cmd.Field("reference").asString().GetMultiByteChars();
        order.estimatedDeliveryDate = cmd.Field("estimated_delivery_date").asDateTime();
        order.createdAt = cmd.Field("created_at").asDateTime();
        order.customerID = cmd.Field("id").asInt64();
        order.staffID = cmd.Field("id_staff").asInt64();
        order.deliveryAddressID = cmd.Field("id_address").asInt64();
        order.billingAddressID = cmd.Field("id_address_bill").asInt64();
        orders.push_back(order);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return orders;
}

int OrderHistoryModel::getOrderCountByCustomerID(int customerID) {
    SACommand cmd;
    cmd.setCommandText("SELECT COUNT(id) FROM `order__history` WHERE id = :1;");
    cmd.Param(1).setAsInt64() = _TSA(customerID);
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int count = cmd[1].asInt64();
    ModelManager::get()->getDataBase()->closeConnection();
    return count;
}

double OrderHistoryModel::getTotalPurchasesOfCustomerByID(int customerID) {
    SACommand cmd;
    cmd.setCommandText("SELECT SUM((oi.quantity * oi.price * (1 - oi.commercial_discount)) * (1 + i.vat))\n"
                       "FROM `order__history`\n"
                       "         INNER JOIN order__item oi on order__history.reference = oi.reference\n"
                       "         INNER JOIN item i on oi.reference_item = i.reference\n"
                       "WHERE id = :1;");
    cmd.Param(1).setAsInt64() = _TSA(customerID);
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    double amount = cmd[1].asInt64();
    ModelManager::get()->getDataBase()->closeConnection();
    return amount;
}
