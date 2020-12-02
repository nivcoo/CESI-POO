//
// Created by Nicolas on 18/11/2020.
//

#include "DataBase.h"

DataBase::DataBase(string server, string db, string user, string pass) : _server(server), _db(db),
                                                                                 _user(user), _pass(pass) {

}

void DataBase::connectIfNot() {
    if (!_con.isConnected()) {
        try {
            string host = _server + "@" + _db;
            _con.Connect(host.c_str(), _user.c_str(), _pass.c_str(), SA_MySQL_Client);
            //cout << "We are connected!" << endl;
        }
        catch (SAException &x) {
            displayDBError(x);
            _con.Rollback();
        }
    }

}

void DataBase::closeConnection() {
    if (_con.isConnected() || _con.isAlive()) {
        _con.Disconnect();
        //cout << "We are disconnected!" << endl;
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



