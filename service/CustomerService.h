//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERSERVICE_H
#define MAIN_CPP_CUSTOMERSERVICE_H
#include <iostream>
#include <SQLAPI.h>
using namespace std;
class CustomerService {

public:
    int addCustomer(string firstname, string lastname, SADateTime birthDate);
    void addAddressToCustomerID(int customerID, int type, string addressLine, string postalCode, string city);

};


#endif //MAIN_CPP_CUSTOMERSERVICE_H
