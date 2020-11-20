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

    _customerModel = new CustomerModel();
    _customerModel->updateByID(2, "gtyrthrt", "rth", SADateTime(2000,10,1));
    //_customerModel->deleteCustomerByID(1);

}

ModelManager::~ModelManager() {

    delete _customerModel;

}


