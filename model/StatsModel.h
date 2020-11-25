//
// Created by Nicolas on 25/11/2020.
//

#ifndef GLOBAL_QSS_STATMODEL_H
#define GLOBAL_QSS_STATMODEL_H

#include <iostream>
#include <vector>
#include <SQLAPI.h>

using namespace std;

class StatsModel {
public:
    struct Statistics {

    };
    struct OrderItem {
        string reference, referenceItem;
        int quantity;
        float price, vat;
        float orderValue(){
            return quantity * price;
        }
    };
    struct OrderHistory{
        string reference, estimatedDeliveryDate, createdAt;
        int customerID, staffID, deliveryAddressID, billingAddressID;
    };
    static vector<OrderItem> getAllOrderItem();
    static vector<OrderHistory> getAllOrderHistory();
};


#endif //GLOBAL_QSS_STATMODEL_H
