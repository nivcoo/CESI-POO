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
    static double getAverageCartValue();

    static double getMonthlyEarning(SADateTime dateTime);

    static double getValueStock(bool commercial = false, double exValue = 1);

    static double getTotalPurchasesOfCustomerByID(int customerID);

    static vector<ItemModel::Item> getLowStockItems();

    static std::vector<OrderItemModel::OrderItem> getItemsBestSelled();

    static vector<OrderItemModel::OrderItem> getItemsLeastSelled();

};


#endif //MAIN_CPP_STATISTIQUES_H
