//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerService.h"
#include "../ihm/IHM.h"
int CustomerService::addCustomer(string firstname, string lastname, SADateTime birthDate) {

    ModelManager * mm = IHM::get()->getModelManager();

    int customerID = mm->getCustomerModel()->insert(firstname, lastname, birthDate);
    return customerID;
}

void CustomerService::addAddressToCustomerID(int id, int type, string addressLine, string postalCode, string city) {


}

