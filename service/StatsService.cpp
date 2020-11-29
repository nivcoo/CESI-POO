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
        int selectedYear = dateTime.GetYear();
        int selectedMonth = dateTime.GetMonth();
        if (orderYear != selectedYear || orderMonth != selectedMonth)
            continue;
        total += (1 + orderItem.vat) * (orderItem.price * orderItem.quantity);
    }
    return total;
}

double StatsService::getValueStock(bool commercial, double exValue) {
    auto items = ItemService::getAllItems();
    double total = 0;
    for (auto item : items) {
        if (commercial)
            total += (item.priceHt * item.quantity) * (1 + item.vat);
        else
            total += (item.priceHt * item.quantity) * exValue;
    }
    return total;
}

std::vector<OrderItemModel::OrderItem> StatsService::getItemsBestSelled() {
    auto item = OrderItemModel::getMostSellItem();
    return item;
}

std::vector<OrderItemModel::OrderItem> StatsService::getItemsLeastSelled() {
    auto item = OrderItemModel::getLeastSellItem();
    return item;
}

double StatsService::getTotalPurchasesOfCustomerByID(int customerID) {
    return OrderService::getTotalPurchasesOfCustomerByID(customerID);
}

vector<ItemModel::Item> StatsService::getLowStockItems() {
    return ItemService::getLowStockItems();
}
