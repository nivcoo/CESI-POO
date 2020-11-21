//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerService.h"

int CustomerService::addCustomer(string firstname, string lastname, SADateTime birthDate) {
    int customerID = CustomerModel::insert(firstname, lastname, birthDate);
    return customerID;
}

void
CustomerService::addAddressToCustomerID(int customerID, int type, string addressLine, string postalCode, string city) {
    AddressModel::archiveAllType(type);
    int addressID = AddressModel::insert(type, addressLine, postalCode, city);
    CustomerAddressModel::insert(customerID, addressID);
}

CustomerModel::Customer CustomerService::getCustomerByID(int id) {
    return CustomerModel::getCustomerByID(id);
}

std::vector<CustomerModel::Customer> CustomerService::getAllCustomers() {
    return CustomerModel::getAllCustomers();
}

vector<CustomerModel::Customer> CustomerService::getAllCustomersByFirstAndLastName(string firstname, string lastname) {
    return CustomerModel::getAllCustomersByFirstAndLastName(firstname, lastname);
}


