//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ODERPAYMENTMODEL_H
#define MAIN_CPP_ODERPAYMENTMODEL_H


#include "../../utils/DataBase.h"

class OrderPaymentModel {
public:
    int insert(int payementMethod, double amount, string orderReference);

    void deleteByID(int id);

};


#endif //MAIN_CPP_ODERPAYMENTMODEL_H
