//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ODERPAYMENTMODEL_H
#define MAIN_CPP_ODERPAYMENTMODEL_H


#include "../../utils/DataBase.h"

#include <vector>

class OrderPaymentModel {
public:

    struct Payment {

        int id, paymentMethod;
        double amount;
        SADateTime soldAt;
        string reference;
    };

    static int insert(int paymentMethod, double amount, string orderReference);

    static void deleteByID(int id);

    static double getAmountForOrderByREF(string ref);

    static vector<Payment> getAllPaymentByOrderREF(string orderReference);

    static void updateAmountBuID(int id, double amount);

};


#endif //MAIN_CPP_ODERPAYMENTMODEL_H
