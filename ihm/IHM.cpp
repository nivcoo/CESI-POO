//
// Created by Nicolas on 19/11/2020.
//


#include "IHM.h"
#include "../window/main/MainWindow.h"
#include "../service/CustomerService.h"

IHM *IHM::INSTANCE = nullptr;


IHM::IHM() {
    INSTANCE = this;
    initDB();
    initServices();
    _customerService = new CustomerService();
}

void IHM::initDB() {
    _db = new DataBase("antoinelonne.dev", "poo", "cesi", "cesi-POO");
    _modelManager = new ModelManager();
}


void IHM::initServices() {
    _customerService = new CustomerService();

    /**int customerID = _customerService->addCustomer("SALUT", "DUUUU", SADateTime(2000, 8, 02));

    cout << customerID << endl;**/
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
    delete _customerService;
}


