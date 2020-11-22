//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ORDERHISTORYMODEL_H
#define MAIN_CPP_ORDERHISTORYMODEL_H


#include "../../utils/DataBase.h"

class OrderHistoryModel {
public:
    void insert(string reference, SADateTime estimatedDeliveryDate, int idCustomer, int idStaff,
                int idDeliveryAddress, int idBillingAddress);

    void deleteById(string reference);

};


#endif //MAIN_CPP_ORDERHISTORYMODEL_H
