//
// Created by Nicolas on 19/11/2020.
//


#include "ModelManager.h"
#include "../ihm/IHM.h"


ModelManager::ModelManager() {
    initDB();
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
    DataBase *db = IHM::get()->getDataBase();
    db->connectAndExecuteCommand(cmd);
    if (close)
        db->closeConnection();
}

ModelManager::~ModelManager() {

}


