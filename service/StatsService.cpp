//
// Created by Nicolas on 18/11/2020.
//

#include "StatsService.h"
#include <vector>
#include "../model/StatsModel.h"
#include "OrderService.h"

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
        OrderHistoryModel::Order order = OrderService::getOrderByREF(ref);
        //SADateTime hasnt a parse function
        string orderYear = order.createdAt.substr(0, 4);
        string orderMonth = order.createdAt.substr(5, 7);
        string currentYear =  to_string(SADateTime::currentDateTime().GetYear());
        string currentMonth =  to_string(SADateTime::currentDateTime().GetMonth());
        if(orderYear != currentYear && orderMonth != currentMonth)
            continue;
        total += x.orderValue();
    }
    return total;
}

vector<ItemModel::Item> GetLowStocksItems(){
    vector<ItemModel::Item> itemsList = ItemModel::GetAllItems();
    //todo: voir si on peut pas faire un truc genre
    //return itemsList.Where(x => x.quantity >= x.resuplyThreshold);
    vector<ItemModel::Item> lowStocksList;
    for (auto x : itemsList) {
        if(x.quantity >= x.resuplyThreshold)
            lowStocksList.push_back(x);
    }
    return lowStocksList;
}

double StatsService::getCustomerTotalPurchases(int customerId) {
    vector<OrderHistoryModel::Order> Orders = OrderHistoryModel::getAllOrdersByCustomerID(customerId);
    double d = 0.0;
    for (auto x : Orders) {
      //  x.
    }
    return d;
}