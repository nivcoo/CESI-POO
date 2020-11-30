//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERSERVICE_H
#define MAIN_CPP_CUSTOMERSERVICE_H

#include "../model/CustomerModel.h"
#include "../model/AddressModel.h"
#include "../model/CustomerAddressModel.h"

class CustomerService {

public:

/**
 * Create a customer
 * @param firstname
 * @param lastname
 * @param birthDate
 * @return id of the customer
 */
    static int addCustomer(string firstname, string lastname, SADateTime birthDate);

/**
 * Archive a customer instead of deleting it
 * @param customerID
 */
    static void archiveCustomerByID(int customerID);

/**
 * Create an address for a customer
 * @param customerID
 * @param type 1 for payment, 2 for delivery
 * @param addressLine
 * @param postalCode
 * @param city
 */
    static void addAddressToCustomerID(int customerID, int type, string addressLine, string postalCode, string city);

/**
 * Get a customer by it's id
 * @param customerID
 * @return CustomerModel::Customer struct that contain all data about a customer
 */
    static CustomerModel::Customer getCustomerByID(int customerID);

/**
 * Get all the customers
 * @return vector of CustomerModel::Customer struct that contain all data about a customer
 */
    static vector<CustomerModel::Customer> getAllCustomers();

/**
 * Get customers by firstname and lastname
 * @param firstname
 * @param lastname
 * @return vector of CustomerModel::Customer struct that contain all data about a customer
 */
    static vector<CustomerModel::Customer> getAllCustomersByFirstAndLastName(string firstname, string lastname);

/**
 * Get the addresses of a customer
 * @param customerID
 * @return vector of AddressModel::Address struct that contain all data about an address
 */
    static vector<AddressModel::Address> getAllActiveAddressOfCustomerID(int customerID);

/**
 * Update a customer
 * @param customerID
 * @param firstname
 * @param lastname
 * @param birthDate
 */
    static void editCustomerByID(int customerID, string firstname, string lastname, SADateTime birthDate);
};


#endif //MAIN_CPP_CUSTOMERSERVICE_H
