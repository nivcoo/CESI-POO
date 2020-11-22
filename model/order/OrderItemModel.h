//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ORDERITEMMODEL_H
#define MAIN_CPP_ORDERITEMMODEL_H


#include "../../utils/DataBase.h"

class OrderItemModel {
public:
    void insert(string orderReference, string itemReference, int quantity, double price, double vat);

    void deleteById(string orderReference, string itemReference);

};


#endif //MAIN_CPP_ORDERITEMMODEL_H
