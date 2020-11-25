//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ORDERITEMMODEL_H
#define MAIN_CPP_ORDERITEMMODEL_H


#include <vector>
#include "../../utils/DataBase.h"

class OrderItemModel {
public:

    struct OrderItem {
        string reference, referenceItem;
        int quantity;
        float price, vat;
    };
    static void insert(string orderReference, string itemReference, int quantity, double price, double vat);

    static void deleteById(string orderReference, string itemReference);

    static std::vector<OrderItem> getAllOrderItem();
};


#endif //MAIN_CPP_ORDERITEMMODEL_H
