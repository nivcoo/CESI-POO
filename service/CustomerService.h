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
    static int addCustomer(string firstname, string lastname, SADateTime birthDate);
    static void addAddressToCustomerID(int customerID, int type, string addressLine, string postalCode, string city);
};


#endif //MAIN_CPP_CUSTOMERSERVICE_H
