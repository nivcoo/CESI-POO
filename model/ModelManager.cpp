//
// Created by Nicolas on 19/11/2020.
//


#include "ModelManager.h"

ModelManager *ModelManager::INSTANCE = nullptr;

ModelManager::ModelManager() {

    INSTANCE = this;
    initDB();

    // double earn = StatsService::getMonthlyEarning(SADateTime::currentDateTime());
    // double value = StatsService::getAvarageCartValue();
    //  cout << earn << endl;

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

void ModelManager::initDB() {
    _db = new DataBase("antoinelonne.dev", "poo", "cesi", "cesi-POO");
    QFile sql(":/database/database.sql");
    if (!sql.open(QFile::ReadOnly))
        return;

    QString allSQL = QLatin1String(sql.readAll());
    SAString allSQLStr = SAString(allSQL.toLatin1());
    DataBase *db = getDataBase();
    SACommand cmd;
    cmd.setCommandText(allSQLStr);
    db->connectAndExecuteCommand(&cmd);
    db->closeConnection();
    sql.close();
    /**test->addAddressToCustomerID(customerID, 1, "41 rue", "64800", "okkk");
    test->addAddressToCustomerID(customerID, 2, "78 rue", "64000", "uyk");**/
    //test->addCustomer();
    //_customerAddressModel->insert(2,1);
    //_addressModel->insert(1, "41 rue de lassun", "64800", "Montaut", false);
    //_customerModel->deleteCustomerByID(1);
}

void ModelManager::sendCMD(SACommand *cmd) {
    sendCMD(cmd, true);
}

void ModelManager::sendCMD(SACommand *cmd, bool close) {
    DataBase *db = get()->getDataBase();
    db->connectAndExecuteCommand(cmd);
    if (close)
        db->closeConnection();
}

ModelManager::~ModelManager() {
    delete _db;
}

DataBase *ModelManager::getDataBase() {
    return _db;
}

ModelManager *ModelManager::get() {
    return INSTANCE;
}


