//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ORDERHISTORYMODEL_H
#define MAIN_CPP_ORDERHISTORYMODEL_H


#include "../../utils/DataBase.h"
#include <vector>

class OrderHistoryModel {
public:
    struct Order {
        string reference;
        SADateTime estimatedDeliveryDate, createdAt;
        int customerID, staffID, deliveryAddressID, billingAddressID;
    };


    static string insert(string reference, SADateTime estimatedDeliveryDate, int customerID, int staffID,
                         int deliveryAddressID, int billingAddressID);

    static void deleteById(string reference);

    static Order getOrderByREF(string reference);

    static vector<OrderHistoryModel::Order> getAllOrdersByCustomerID(int customerID);

    static vector<OrderHistoryModel::Order> getLastOrdersByNumber(int number);

    static int getOrderCountByCustomerID(int customerID);

    static vector<Order> getAllOrders();
};


#endif //MAIN_CPP_ORDERHISTORYMODEL_H
