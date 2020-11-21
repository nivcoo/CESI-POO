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
    AddressModel::archiveAllType(customerID, type);
    int addressID = AddressModel::insert(type, addressLine, postalCode, city);
    CustomerAddressModel::insert(customerID, addressID);
}

