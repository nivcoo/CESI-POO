//
// Created by Nicolas on 18/11/2020.
//

#include "DataBase.h"
#include "../ihm/IHM.h"

DataBase::DataBase(SAString server, SAString db, SAString user, SAString pass) : _server(server), _db(db),
                                                                                 _user(user), _pass(pass) {

    /**
     *
     * This is an example
    SACommand cmd;

    cmd.setCommandText("SELECT cuntest FROM test WHERE cuntest = :1");
    cmd << 10L;
    connectAndExecuteCommand(&cmd);

    while(cmd.FetchNext())
        cout << cmd.Field(_TSA("cuntest")).asString().GetMultiByteChars() << endl;
    closeConnection();**/
}

void DataBase::connectIfNot() {

    if (!_con.isConnected()) {
        try {
            _con.Connect(_server + "@" + _db, _user, _pass, SA_MySQL_Client);
            cout << "We are connected!" << endl;
        }
        catch (SAException &x) {
            displayDBError(x);
            _con.Rollback();
        }
    }

}

void DataBase::closeConnection() {
    if (_con.isConnected()) {
        _con.Disconnect();
        cout << "We are disconnected!" << endl;
    }
}


void DataBase::connectAndExecuteCommand(SACommand *saCommand) {
    connectIfNot();
    try {
        saCommand->setConnection(&_con);
        saCommand->Execute();
    }
    catch (SAException &x) {
        displayDBError(x);
        _con.Rollback();
    }
}

DataBase::~DataBase() {
    closeConnection();
}


void DataBase::displayDBError(SAException &error) {
    cerr << "Database ERROR :" << endl << error.ErrText().GetMultiByteChars() << endl;
}



