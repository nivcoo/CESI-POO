//
// Created by Nicolas on 20/11/2020.
//

#include "OrderService.h"


string OrderService::addOrder(SADateTime estimatedDeliveryDate, int customerID, int staffID) {

    CustomerModel::Customer customer = CustomerService::getCustomerByID(customerID);
    vector<AddressModel::Address> address = CustomerService::getAllActiveAddressOfCustomerID(customerID);
    time_t now = time(NULL);
    struct tm *timeNow = localtime(&now);
    string reference = customer.firstname.substr(0, 2) + customer.lastname.substr(0, 2) +
                       to_string(timeNow->tm_year + 1900);
    int deliveryAddressID = 0;
    int billingAddressID = 0;

    for (const auto &ad :address) {
        if (ad.type == 1) {
            deliveryAddressID = ad.id;
            reference += ad.city.substr(0, 3);
        } else if (ad.type == 2)
            billingAddressID = ad.id;
    }

    reference += to_string((OrderHistoryModel::getOrderCountByCustomerID(customerID) + 1));
    transform(reference.begin(), reference.end(), reference.begin(), ::toupper);
    string orderHistoryREF = OrderHistoryModel::insert(reference, estimatedDeliveryDate, customerID, staffID,
                                                       deliveryAddressID, billingAddressID);

    return orderHistoryREF;
}


void OrderService::addItemToOrderREF(string orderREF, string itemREF, int quantity, double commercialDiscount) {
    ItemModel::Item item = ItemService::getItemByREF(itemREF);
    int newQuantity = item.quantity - quantity;
    newQuantity = (newQuantity >= 0 ? newQuantity : 0);
    OrderItemModel::insert(orderREF, itemREF, quantity, item.priceHt, item.vat, commercialDiscount);
    ItemService::updateItemQuantityByREF(itemREF, newQuantity);
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

vector<OrderHistoryModel::Order> OrderService::getLastOrdersByNumber(int number) {
    return OrderHistoryModel::getLastOrdersByNumber(number);
}

int OrderService::getOrderCountByCustomerID(int customerID) {
    return OrderHistoryModel::getOrderCountByCustomerID(customerID);
}

std::vector<OrderItemModel::OrderItem> OrderService::getAllOrderItem() {
    return OrderItemModel::getAllOrderItem();
}

vector<OrderHistoryModel::Order> OrderService::getAllOrders() {
    return OrderHistoryModel::getAllOrders();
}

vector<OrderItemModel::OrderItem> OrderService::getAllOrderItemByOrderREF(string orderReference) {
    return OrderItemModel::getAllOrderItemByOrderREF(orderReference);
}

void OrderService::deleteOrderByREF(string orderREF) {
    OrderHistoryModel::deleteByREF(orderREF);

}

double OrderService::getPaymentAmountForOrderByREF(string orderREF) {
    return OrderPaymentModel::getAmountForOrderByREF(orderREF);
}

vector<OrderPaymentModel::Payment> OrderService::getAllPaymentByOrderREF(string orderReference) {
    return OrderPaymentModel::getAllPaymentByOrderREF(orderReference);
}

void OrderService::editEstimatedDeliveryDateByOrderREF(string reference, SADateTime estimatedDeliveryDate) {
    OrderHistoryModel::updateEstimatedDeliveryDateByREF(reference, estimatedDeliveryDate);
}

void OrderService::deleteItemFromOrderByREF(string orderReference, string itemReference) {
    OrderItemModel::deleteByREF(orderReference, itemReference);
}

void OrderService::deletePaymentFromOrderByID(int itemReference) {
    OrderPaymentModel::deleteByID(itemReference);
}

void OrderService::editPaymentAmountByID(int paymentID, double amount) {
    OrderPaymentModel::updateAmountBuID(paymentID, amount);
}

void OrderService::editCommercialDiscountFromOrderByREF(string orderReference, string itemReference, double commercialDiscount) {
    OrderItemModel::updateCommercialDiscountFromOrderByREF(orderReference, itemReference, commercialDiscount);
}

double OrderService::getTotalPurchasesOfCustomerByID(int customerID) {
    return OrderHistoryModel::getAmountOfAllOrdersOfCustomerByID(customerID);
}
