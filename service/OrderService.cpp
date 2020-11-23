//
// Created by Nicolas on 20/11/2020.
//

#include "OrderService.h"


string OrderService::addOrder(SADateTime estimatedDeliveryDate, int customerID, int staffID) {

    string reference = "UJOIIDFJHBYHGH89UHU5";
    vector<AddressModel::Address> address = CustomerService::getAllActiveAddressOfCustomerID(customerID);
    int deliveryAddressID = 0;
    int billingAddressID = 0;

    for (const auto &ad :address) {
        if (ad.type == 1)
            deliveryAddressID = ad.id;
        else if (ad.type == 2)
            billingAddressID = ad.id;
    }
    string orderHistoryREF = OrderHistoryModel::insert(reference, estimatedDeliveryDate, customerID, staffID,
                                                       deliveryAddressID, billingAddressID);

    return orderHistoryREF;
}


void OrderService::addItemToOrderREF(string orderREF, string itemREF, int quantity) {
    ItemModel::Item item = ItemModel::getItemByREF(itemREF);
    int newQuantity = item.quantity - quantity;
    OrderItemModel::insert(orderREF, itemREF, quantity, item.priceHt, item.vat);
    ItemModel::updateQuantityOfItemREF(itemREF, newQuantity);
}


void OrderService::addPaymentToOrderREF(string orderREF, int paymentMethod, double amount) {
    OrderPaymentModel::insert(paymentMethod, amount, orderREF);
}

OrderHistoryModel::Order OrderService::getOrderByREF(string orderREF) {
    return OrderHistoryModel::getOrderByREF(orderREF);
}

vector<OrderHistoryModel::Order> OrderService::getAllOrdersByCustomerID(int customerID) {
    return OrderHistoryModel::getAllOrdersByCustomerID(customerID);
}
