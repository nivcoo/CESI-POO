//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerService.h"

int CustomerService::addCustomer(string firstname, string lastname, SADateTime birthDate) {
    return CustomerModel::insert(firstname, lastname, birthDate);
}

void CustomerService::addAddressToCustomerID(int customerID, int type, string addressLine,
                                             string postalCode, string city) {
    CustomerAddressModel::archiveAddressOfCustomerIDByType(customerID, type);
    int addressID = AddressModel::insert(type, addressLine, postalCode, city);
    CustomerAddressModel::insert(customerID, addressID);
}

CustomerModel::Customer CustomerService::getCustomerByID(int customerID) {
    return CustomerModel::getCustomerByID(customerID);
}

vector<CustomerModel::Customer> CustomerService::getAllCustomers() {
    return CustomerModel::getAllCustomers();
}

vector<CustomerModel::Customer> CustomerService::getAllCustomersByFirstAndLastName(string firstname, string lastname) {
    return CustomerModel::getAllCustomersByFirstAndLastName(firstname, lastname);
}


vector<AddressModel::Address> CustomerService::getAllActiveAddressOfCustomerID(int customerID) {
    return CustomerAddressModel::getAllActiveAddressOfCustomerID(customerID);
}


