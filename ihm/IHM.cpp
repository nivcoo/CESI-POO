//
// Created by Nicolas on 19/11/2020.
//


#include "IHM.h"

IHM *IHM::INSTANCE = nullptr;


IHM::IHM() {
    INSTANCE = this;
    initDB();
}

void IHM::initDB() {
    _db = new DataBase("antoinelonne.dev", "poo", "cesi", "cesi-POO");
    _modelManager = new ModelManager();
    /**vector<CustomerModel::Customer> cu = CustomerModel::getAllCustomers();
    for (auto c : cu) {
        cout << c.firstName << c.lastName << c.birthDate << endl;
    }**/

    /**int customerID = _customerService->addCustomer("SALUT", "DUUUU", SADateTime(2000, 8, 02));
    _customerService->addAddressToCustomerID(customerID, 1, "41 rue", "64800", "okkk");
    _customerService->addAddressToCustomerID(customerID, 2, "78 rue", "64000", "uyk");**/
}


ModelManager *IHM::getModelManager() {
    return _modelManager;
}

DataBase *IHM::getDataBase() {
    return _db;
}

IHM *IHM::get() {
    return INSTANCE;
}

IHM::~IHM() {
    delete INSTANCE;
    delete _db;
    delete _modelManager;
}


