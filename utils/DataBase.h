//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_DATABASE_H
#define MAIN_CPP_DATABASE_H

#include <iostream>
#include <SQLAPI.h>
#include <string>

using namespace std;

class DataBase {

public:

/**
 * Init database object
 * @param server Hostname
 * @param db Database name
 * @param user DB Username
 * @param pass DB Password
 */
    DataBase(SAString server, SAString db, SAString user, SAString pass);

    ~DataBase();

    void connectIfNot();

    void closeConnection();

/**
 * Send a command to the DB
 * @param saCommand
 */
    void connectAndExecuteCommand(SACommand *saCommand);

    SAConnection _con;
private:

    SAString _server;
    SAString _db;
    SAString _user;
    SAString _pass;
    void displayDBError(SAException &error);
};


#endif //MAIN_CPP_DATABASE_H
