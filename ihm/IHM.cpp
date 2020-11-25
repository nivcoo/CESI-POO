//
// Created by Nicolas on 19/11/2020.
//


#include "IHM.h"
#include "../service/CustomerService.h"
#include "../service/ItemService.h"
#include "../service/OrderService.h"
#include "../service/StaffService.h"
#include "../service/StatsService.h"

IHM *IHM::INSTANCE = nullptr;


IHM::IHM() {
    INSTANCE = this;
    initDB();
}

void IHM::initDB() {
    _db = new DataBase("antoinelonne.dev", "poo", "cesi", "cesi-POO");
    _modelManager = new ModelManager();

    //double earn = StatsService::getMonthlyEarning(SADateTime::currentDateTime());
   // double value = StatsService::getAvarageCartValue();
   // cout << value << endl;

    //string ref = ItemService::addItem("HYHT858GG", "tyj", 50,100, 10, 0.2);

    //int id = StaffService::addStaff("salut", "salut2", SADateTime(2020,12,11), "84887 yuty", "85860", "albert", NULL);
    //string ref = OrderService::addOrder(SADateTime(2020,12,11), 4, 5);
    /**string ref = OrderService::addOrder(SADateTime(2020,12,11), 4, 5);
    OrderService::addItemToOrderREF(ref, "HYHT858GG", 10);**/

    //OrderService::addPaymentToOrderREF("UJOIIDFJHBYHGH89UHU5", 1, 10);


    /**int customerID = CustomerService::addCustomer("SALUT", "DUUUU", SADateTime(2000, 8, 02));
    CustomerService::addAddressToCustomerID(customerID, 1, "41 rue", "64800", "okkk");
    CustomerService::addAddressToCustomerID(customerID, 2, "78 rue", "64000", "uyk");

    CustomerService::addAddressToCustomerID(customerID, 2, "88 rue", "64000", "uyk");


    vector<AddressModel::Address> ad = CustomerService::getAllActiveAddressOfCustomerID(customerID);

    for (auto c : ad) {
        cout << c.id << c.addressLine << c.postalCode << endl;
    }**/

    /**vector<AddressModel::Address> ad = CustomerService::getAllActiveAddressOfCustomerID(31);

    for (auto c : ad) {
        cout << c.id << c.addressLine << c.postalCode << endl;
    }**/

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


