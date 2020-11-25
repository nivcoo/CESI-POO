//
// Created by Nicolas on 18/11/2020.
//

#include "StatsService.h"
#include <vector>
#include "../model/StatsModel.h"

double StatsService::getAvarageCartValue() {
    vector<StatsModel::OrderItem> ordersList = StatsModel::getAllOrderItem();
    int count = 0;
    double d = 0.0;
    for (auto x : ordersList) {
        double delta = x.orderValue() - d;
        d += delta / ++count;
    }
    return d;
}

double StatsService::getMonthlyEarning(SADateTime DateTime) {
    vector<StatsModel::OrderItem> ordersListItems = StatsModel::getAllOrderItem();
    vector<StatsModel::OrderHistory> ordersListHistory = StatsModel::getAllOrderHistory();

    double total = 0.0;
    for (auto x : ordersListItems) {
        string ref = x.reference;
      //  auto it = find_if(ordersListHistory.begin(), ordersListHistory.end(), [&ref](const StatsModel::OrderHistory& obj) {return obj.reference == ref;});
        //  if (it != ordersListHistory.end())
        //  {
        //      auto index = std::distance(ordersListHistory.begin(), it); // element index
        //  }
    }
    return total;
}