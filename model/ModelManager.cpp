//
// Created by Nicolas on 19/11/2020.
//


#include "ModelManager.h"

ModelManager *ModelManager::INSTANCE = nullptr;

ModelManager::ModelManager() {
    INSTANCE = this;
    initDB();
}

void ModelManager::initDB() {
    _db = new DataBase("antoinelonne.dev", "poo", "cesi", "cesi-POO");
    QFile sql(":/database/database.sql");
    if (!sql.open(QFile::ReadOnly))
        return;

    QString allSQL = QLatin1String(sql.readAll());
    SAString allSQLStr = SAString(allSQL.toLatin1());
    SACommand cmd;
    cmd.setCommandText(allSQLStr);
    _db->connectAndExecuteCommand(&cmd);
    _db->closeConnection();
    sql.close();
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


