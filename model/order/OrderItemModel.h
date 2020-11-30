//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ORDERITEMMODEL_H
#define MAIN_CPP_ORDERITEMMODEL_H


#include <vector>
#include "../../utils/DataBase.h"

class OrderItemModel {
public:

    struct OrderItem {
        string reference, referenceItem;
        int quantity;
        float price, vat, commercialDiscount;
    };

/**
 * Insert a item row in the order__item table
 * @param orderReference
 * @param itemReference
 * @param quantity
 * @param price
 * @param vat
 * @param commercialDiscount value between 0 and 1
 */
    static void insert(string orderReference, string itemReference, int quantity, double price, double vat, double commercialDiscount);

/**
 * Delete a item row in the order__item table
 * @param orderReference
 * @param itemReference
 */
    static void deleteByREF(string orderReference, string itemReference);

/**
 * Get all "order items"
 * @return vector of OrderItemModel::OrderItem
 */
    static std::vector<OrderItem> getAllOrderItem();

/**
 * Get 10 most sold items
 * @return vector of OrderItemModel::OrderItem
 */
    static std::vector<OrderItem> getMostSoldItem();

/**
 * Get 10 least sold items
 * @return vector of OrderItemModel::OrderItem
 */
    static std::vector<OrderItem> getLeastSoldItem();

/**
 * Get all items row of a given order
 * @param orderReference
 * @return vector of OrderItemModel::OrderItem
 */
    static vector<OrderItem> getAllOrderItemByOrderREF(string orderReference);

/**
 * Update commercial discount for an item in an order
 * @param orderReference
 * @param itemReference
 * @param commercialDiscount value between 0 and 1
 */
    static void updateCommercialDiscountFromOrderByREF(string orderReference, string itemReference, double commercialDiscount);
};


#endif //MAIN_CPP_ORDERITEMMODEL_H
