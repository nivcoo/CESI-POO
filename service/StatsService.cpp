//
// Created by Nicolas on 18/11/2020.
//

#include "StatsService.h"


double StatsService::getAverageCartValue() {
    auto orderItems = OrderService::getAllOrderItem();
    int count = 0;
    double d = 0.0;
    for (auto orderItem : orderItems) {
        double delta = ((1 + orderItem.vat) * (orderItem.price * orderItem.quantity)) - d;
        d += delta / ++count;
    }
    return d;
}

double StatsService::getMonthlyEarning(SADateTime dateTime) {
    auto ordersItems = OrderService::getAllOrderItem();
    double total = 0.0;
    for (auto orderItem : ordersItems) {
        string ref = orderItem.reference;
        OrderHistoryModel::Order order = OrderService::getOrderByREF(ref);
        int orderYear = order.createdAt.GetYear();
        int orderMonth = order.createdAt.GetMonth();
        int currentYear = SADateTime::currentDateTime().GetYear();
        int currentMonth = SADateTime::currentDateTime().GetMonth();
        if (orderYear != currentYear && orderMonth != currentMonth)
            continue;
        total += (1 + orderItem.vat) * (orderItem.price * orderItem.quantity);
    }
    return total;
}

double StatsService::getCustomerTotalPurchases(int customerID) {
    vector<OrderHistoryModel::Order> Orders = OrderHistoryModel::getAllOrdersByCustomerID(customerID);
    double total = 0.0;
    for (auto order : Orders) {
        //  order.
    }
    return total;
}

double StatsService::getCommercialValueStock() {
    auto item = ItemService::getAllItems();
    double total;

    for (auto item : ItemService::getAllItems())
    {
        total += (item.priceHt * item.quantity) * (1 + item.vat);
    }

    return total;
}

double StatsService::getBuyValueStock() {
    auto item = ItemService::getAllItems();
    double total;

        for (auto item: ItemService::getAllItems())
        {
                total += item.priceHt * item.quantity;
        }


    return total;
}
