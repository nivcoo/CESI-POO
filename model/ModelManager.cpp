//
// Created by Nicolas on 19/11/2020.
//


#include "ModelManager.h"
#include "../ihm/IHM.h"
#include "../service/CustomerService.h"


ModelManager::ModelManager() {
    initDB();
    initModel();
}

void ModelManager::initDB() {
    QFile sql(":/database/database.sql");
    if (!sql.open(QFile::ReadOnly))
        return;

    QString allSQL = QLatin1String(sql.readAll());
    SAString allSQLStr = SAString(allSQL.toLatin1());
    DataBase *db = IHM::get()->getDataBase();
    SACommand cmd;
    cmd.setCommandText(allSQLStr);
    db->connectAndExecuteCommand(&cmd);
    db->closeConnection();
    sql.close();
}

void ModelManager::initModel() {

    _orderHistoryModel = new OrderHistoryModel;
    _orderItemModel = new OrderItemModel;
    _orderPaymentModel = new OrderPaymentModel;
    _addressModel = new AddressModel;
    _customerAddressModel = new CustomerAddressModel;
    _customerModel = new CustomerModel;
    _itemModel = new ItemModel;
    _staffModel = new StaffModel;
    /**test->addAddressToCustomerID(customerID, 1, "41 rue", "64800", "okkk");
    test->addAddressToCustomerID(customerID, 2, "78 rue", "64000", "uyk");**/
    //test->addCustomer();
    //_customerAddressModel->insert(2,1);
    //_addressModel->insert(1, "41 rue de lassun", "64800", "Montaut", false);
    //_customerModel->deleteCustomerByID(1);

}


OrderHistoryModel *ModelManager::getOrderHistoryModel() {
    return _orderHistoryModel;
}

OrderItemModel *ModelManager::getOrderItemModel() {
    return _orderItemModel;
}

OrderPaymentModel *ModelManager::getOrderPaymentModel() {
    return _orderPaymentModel;
}

AddressModel *ModelManager::getAddressModel() {
    return _addressModel;
}

CustomerAddressModel *ModelManager::getCustomerAddressModel() {
    return _customerAddressModel;
}

CustomerModel *ModelManager::getCustomerModel() {
    return _customerModel;
}

ItemModel *ModelManager::getItemModel() {
    return _itemModel;
}

StaffModel *ModelManager::getStaffModel() {
    return _staffModel;
}


ModelManager::~ModelManager() {

    delete _orderHistoryModel;
    delete _orderItemModel;
    delete _orderPaymentModel;
    delete _addressModel;
    delete _customerAddressModel;
    delete _customerModel;
    delete _itemModel;
    delete _staffModel;

}

void ModelManager::sendCMD(SACommand *cmd) {
    sendCMD(cmd, true);
}

void ModelManager::sendCMD(SACommand *cmd, bool close) {
    DataBase *db = IHM::get()->getDataBase();
    db->connectAndExecuteCommand(cmd);
    if (close)
        db->closeConnection();
}


