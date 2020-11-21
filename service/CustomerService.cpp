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
    int addressID = AddressModel::insert(type, addressLine, postalCode, city, false);
    CustomerAddressModel::insert(customerID, addressID);


}

