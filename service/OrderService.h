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
    static string addOrder(SADateTime estimatedDeliveryDate, int customerID, int staffID);

    static void editEstimatedDeliveryDateByOrderREF(string reference, SADateTime estimatedDeliveryDate);

    static void deleteOrderByREF(string orderREF);

    static void deleteItemFromOrderByREF(string orderReference, string itemReference);

    static void deletePaymentFromOrderByID(int paymentID);

    static double getPaymentAmountForOrderByREF(string orderREF);

    static void addItemToOrderREF(string orderREF, string referenceItems, int quantity, double commercialDiscount);

    static void addPaymentToOrderREF(string orderREF, int paymentMethod, double amount);

    static OrderHistoryModel::Order getOrderByREF(string orderREF);

    static vector<OrderHistoryModel::Order> getAllOrdersByCustomerID(int customerID);

    static vector<OrderHistoryModel::Order> getLastOrdersByNumber(int number);

    static std::vector<OrderItemModel::OrderItem> getAllOrderItem();

    static int getOrderCountByCustomerID(int customerID);

    static vector<OrderHistoryModel::Order> getAllOrders();

    static vector<OrderItemModel::OrderItem> getAllOrderItemByOrderREF(string orderReference);

    static vector<OrderPaymentModel::Payment> getAllPaymentByOrderREF(string orderReference);

    static void editPaymentAmountByID(int paymentID, double amount);

    static void editCommercialDiscountFromOrderByREF(string orderReference, string itemReference, double commercialDiscount);

};


#endif //MAIN_CPP_ODERSERVICE_H
