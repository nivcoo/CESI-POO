//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_MODELMANAGER_H
#define MAIN_CPP_MODELMANAGER_H


#include "../utils/DataBase.h"
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

class ModelManager {

public:
    ModelManager();

    ~ModelManager();

    DataBase *getDataBase();

    static ModelManager *get();

/**
 * Send query to the database and the connection to the db
 * @param cmd contains the query
 */
    static void sendCMD(SACommand *cmd);

/**
 * Send query to the database
 * @param cmd contains the query
 * @param close optinal : close or not the connection to the db (default true)
 */
    static void sendCMD(SACommand *cmd, bool close);

private:
    static ModelManager *INSTANCE;
    DataBase *_db;
    void initDB();

};


#endif //MAIN_CPP_MODELMANAGER_H
