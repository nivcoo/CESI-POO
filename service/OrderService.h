//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ODERSERVICE_H
#define MAIN_CPP_ODERSERVICE_H

#include <algorithm>
#include "CustomerService.h"
#include "ItemService.h"
#include "../model/order/OrderHistoryModel.h"
#include "../model/order/OrderItemModel.h"
#include "../model/order/OrderPaymentModel.h"


class OrderService {
public:

/**
 * Create a new order
 * @param estimatedDeliveryDate
 * @param customerID
 * @param staffID
 * @return order reference
 */
    static string addOrder(SADateTime estimatedDeliveryDate, int customerID, int staffID);

/**
 * Edit estimated delivery date
 * @param reference
 * @param estimatedDeliveryDate
 */
    static void editEstimatedDeliveryDateByOrderREF(string reference, SADateTime estimatedDeliveryDate);

/**
 * Delete an order with a given reference
 * @param orderREF
 */
    static void deleteOrderByREF(string orderREF);

/**
 * Delete an item from an order
 * @param orderReference
 * @param itemReference
 */
    static void deleteItemFromOrderByREF(string orderReference, string itemReference);
/**
 * Delete a payment by it's id
 * @param paymentId
 */
    static void deletePaymentFromOrderByID(int paymentId);

/**
 * Get amount already paid on a given order
 * @param orderREF
 * @return amount already paid
 */
    static double getPaymentAmountForOrderByREF(string orderREF);

/**
 * Add an item to an order
 * @param orderREF
 * @param referenceItems
 * @param quantity
 * @param commercialDiscount
 */
    static void addItemToOrderREF(string orderREF, string referenceItems, int quantity, double commercialDiscount);

/**
 * Add a payment to an order
 * @param orderREF
 * @param paymentMethod
 * @param amount
 */
    static void addPaymentToOrderREF(string orderREF, int paymentMethod, double amount);

/**
 * Get an order by it's reference
 * @param orderREF Order reference
 * @return OrderHistoryModel::Order struct
 */
    static OrderHistoryModel::Order getOrderByREF(string orderREF);

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
 * Get all items row of a given order
 * @param orderReference
 * @return vector of OrderItemModel::OrderItem
 */
    static vector<OrderItemModel::OrderItem> getAllOrderItem();

/**
 * Get the number of orders of a customer
 * @param customerID
 * @return number of orders
 */
    static int getOrderCountByCustomerID(int customerID);

/**
 * Get all orders
 * @return vector of OrderHistoryModel::Order struct
 */
    static vector<OrderHistoryModel::Order> getAllOrders();

/**
 * Get all items row of a given order
 * @param orderReference
 * @return vector of OrderItemModel::OrderItem
 */
    static vector<OrderItemModel::OrderItem> getAllOrderItemByOrderREF(string orderReference);

/**
 * Get all payments of a given order
 * @param orderReference
 * @return vector of OrderPaymentModel::Payment
 */
    static vector<OrderPaymentModel::Payment> getAllPaymentByOrderREF(string orderReference);

/**
 * Update a payment
 * @param paymentID
 * @param amount
 */
    static void editPaymentAmountByID(int paymentID, double amount);

/**
 * Get the amount purchased by a customer
 * @param customerID
 * @return total
 */
    static double getTotalPurchasesOfCustomerByID(int customerID);

/**
 * Update commercial discount for an item in an order
 * @param orderReference
 * @param itemReference
 * @param commercialDiscount value between 0 and 1
 */
    static void editCommercialDiscountFromOrderByREF(string orderReference, string itemReference, double commercialDiscount);

};


#endif //MAIN_CPP_ODERSERVICE_H
