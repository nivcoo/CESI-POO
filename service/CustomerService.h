//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERSERVICE_H
#define MAIN_CPP_CUSTOMERSERVICE_H
#include "../ihm/IHM.h"
class CustomerService {

public:
    int addCustomer(string firstname, string lastname, SADateTime birthDate);
    void addAddressToCustomerID(int id, int type, string addressLine, string postalCode, string city);

};


#endif //MAIN_CPP_CUSTOMERSERVICE_H
