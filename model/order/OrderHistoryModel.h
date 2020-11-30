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

/**
 * Insert an order in the DB (in table order__history)
 * @param reference
 * @param estimatedDeliveryDate
 * @param customerID
 * @param staffID
 * @param deliveryAddressID
 * @param billingAddressID
 * @return Order reference
 */
    static string insert(string reference, SADateTime estimatedDeliveryDate, int customerID, int staffID,
                         int deliveryAddressID, int billingAddressID);

/**
 * Update the estimated delivery date of an order
 * @param reference Order reference
 * @param estimatedDeliveryDate
 */
    static void updateEstimatedDeliveryDateByREF(string reference, SADateTime estimatedDeliveryDate);

/**
 * Delete an order in the DB (in table order__history)
 * @param reference Order reference
 */
    static void deleteByREF(string reference);

/**
 * Get an order by it's reference
 * @param reference Order reference
 * @return OrderHistoryModel::Order struct
 */
    static Order getOrderByREF(string reference);

/**
 * Get all orders of customer
 * @param customerID
 * @return vector of OrderHistoryModel::Order struct
 */
    static vector<OrderHistoryModel::Order> getAllOrdersByCustomerID(int customerID);

/**
 * Get the n last orders
 * @param number Number of orders you'd like to get
 * @return vector of OrderHistoryModel::Order struct
 */
    static vector<OrderHistoryModel::Order> getLastOrdersByNumber(int number);

/**
 * Get the number of orders of a customer
 * @param customerID
 * @return number of orders
 */
    static int getOrderCountByCustomerID(int customerID);

/**
 * Get the amount purchased by a customer
 * @param customerID
 * @return total
 */
    static double getTotalPurchasesOfCustomerByID(int customerID);

/**
 * Get all orders in the DB (in table order__history)
 * @return vector of OrderHistoryModel::Order struct
 */
    static vector<Order> getAllOrders();
};


#endif //MAIN_CPP_ORDERHISTORYMODEL_H
