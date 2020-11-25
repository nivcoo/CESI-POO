//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_STATISTIQUES_H
#define MAIN_CPP_STATISTIQUES_H


#include <SQLAPI.h>
#include "../model/ItemModel.h"

class StatsService {
public:
    static double getAvarageCartValue();
    static double getMonthlyEarning(SADateTime);
    static vector<ItemModel::Item> GetLowStocksItems();
    static double getCustomerTotalPurchases(int);
};


#endif //MAIN_CPP_STATISTIQUES_H
