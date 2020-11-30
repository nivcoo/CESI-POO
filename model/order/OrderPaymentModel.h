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

/**
 * Insert a payment row in the order__payment table
 * @param paymentMethod
 * @param amount
 * @param orderReference
 * @return id of the payment
 */
    static int insert(int paymentMethod, double amount, string orderReference);

/**
 * Delete a payment row in the order__payment table
 * @param id
 */
    static void deleteByID(int id);

/**
 * Get the paid amount for a given order
 * @param ref order reference
 * @return amount paid
 */
    static double getAmountForOrderByREF(string ref);

/**
 * Get all payments of a given order
 * @param orderReference
 * @return vector of OrderPaymentModel::Payment
 */
    static vector<Payment> getAllPaymentByOrderREF(string orderReference);

/**
 * Update a payment row in the order__payment table
 * @param id
 * @param amount
 */
    static void updateAmountByID(int id, double amount);

};


#endif //MAIN_CPP_ODERPAYMENTMODEL_H
