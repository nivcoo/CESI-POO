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

    static double getCustomerTotalPurchases(int customerID);

    static double getCommercialValueStock();

    static double getBuyValueStock();

    static std::vector<OrderItemModel::OrderItem> getBestSeller();

    static vector<OrderItemModel::OrderItem> getLeastSeller();

};


#endif //MAIN_CPP_STATISTIQUES_H
