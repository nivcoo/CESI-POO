//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERMODEL_H
#define MAIN_CPP_CUSTOMERMODEL_H


#include <vector>
#include "../utils/DataBase.h"

class CustomerModel {

public:

    struct Customer {
        int id;
        string lastname, firstname;
        SADateTime birthDate;
    };

/**
 * Insert row in the customer table
 * @param firstname
 * @param lastname
 * @param birthDate
 * @return id of the customer
 */
    static int insert(string firstname, string lastname, SADateTime birthDate);

/**
 * Update row in the customer table
 * @param id
 * @param firstname
 * @param lastname
 * @param birthDate
 */
    static void updateByID(int id, string firstname, string lastname, SADateTime birthDate);

/**
 * Get a customer by it's id
 * @param id
 * @return CustomerModel::Customer struct that contain all data about a customer
 */
    static Customer getCustomerByID(int id);

    static vector<Customer> getAllCustomers();

/**
 * Get all customers matching firstname & lastname
 * @param firstname
 * @param lastname
 * @return vector of CustomerModel::Customer struct that contain all data about a customer
 */
    static vector<Customer> getAllCustomersByFirstAndLastName(string firstname, string lastname);

/**
 * Instead of deleting customer, archive it to not lose it in previous orders
 * @param id
 */
    static void archivedByID(int id);
};


#endif //MAIN_CPP_CUSTOMERMODEL_H
