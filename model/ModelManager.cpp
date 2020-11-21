//
// Created by Nicolas on 19/11/2020.
//


#include "ModelManager.h"
#include "../ihm/IHM.h"


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
    //_customerAddressModel->insert(2,1);
    //_addressModel->insert(1, "41 rue de lassun", "64800", "Montaut", false);
    //_customerModel->deleteCustomerByID(1);

}

ModelManager::~ModelManager() {

    delete _customerModel;

}


