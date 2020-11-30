//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_STATISTIQUES_H
#define MAIN_CPP_STATISTIQUES_H


#include <SQLAPI.h>
#include "../model/ItemModel.h"
#include <vector>
#include <list>
#include "OrderService.h"
#include "../model/order/OrderItemModel.h"

class StatsService {
public:

/**
 * Get average price of the order
 * @return
 */
    static double getAverageCartValue();

/**
 * Get earning for a month
 * @param dateTime
 * @return earnings
 */
    static double getMonthlyEarning(SADateTime dateTime);

/**
 * Get the value of the stock
 * @param commercial set it true to count VAT (default : false -> so exValue is used)
 * @param exValue modifying coefficient (default : 1)
 * @return stock value
 */
    static double getValueStock(bool commercial = false, double exValue = 1);

/**
 * Get the amount spent by a customer
 * @param customerID
 * @return spent amount
 */
    static double getTotalPurchasesOfCustomerByID(int customerID);

/**
 * Get items that are bellow their resupply threshold
 * @return vector of ItemModel::Item containing all infos about item
 */
    static vector<ItemModel::Item> getLowStockItems();

/**
 * Get 10 most sold items
 * @return vector of OrderItemModel::OrderItem
 */
    static vector<OrderItemModel::OrderItem> getItemsBestSold();

/**
 * Get 10 least sold items
 * @return vector of OrderItemModel::OrderItem
 */
    static vector<OrderItemModel::OrderItem> getItemsLeastSold();

};


#endif //MAIN_CPP_STATISTIQUES_H
