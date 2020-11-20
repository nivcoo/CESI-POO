//
// Created by Nicolas on 19/11/2020.
//


#include "ModelManager.h"
#include "../ihm/IHM.h"


ModelManager::ModelManager() {
    initDB();
    initItemModel();
}

void ModelManager::initDB() {
    QFile sql(":/database/database.sql");
    if (!sql.open(QFile::ReadOnly))
        return;

    QString allSQL = QLatin1String(sql.readAll());
    SAString allSQLStr = SAString(allSQL.toLatin1());
    DataBase * db = IHM::get()->getDataBase();
    SACommand cmd;
    cmd.setCommandText(allSQLStr);
    db->connectAndExecuteCommand(&cmd);
    db->closeConnection();
    sql.close();
}

void ModelManager::initItemModel() {

}

ModelManager::~ModelManager() {

}


