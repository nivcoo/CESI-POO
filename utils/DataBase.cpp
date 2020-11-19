//
// Created by Nicolas on 18/11/2020.
//

#include "DataBase.h"

DataBase::DataBase(SAString server, SAString db, SAString user, SAString pass) : _server(server), _db(db),
                                                                                 _user(user), _pass(pass) {


    /**connectIfNot();
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
            cout << "Database ERROR " << endl << x.ErrText().GetMultiByteChars() << endl;
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




SACommand * DataBase::connectAndExecuteCommand(SACommand * saCommand) {
    connectIfNot();
    saCommand->setConnection(&_con);
    saCommand->Execute();
    return saCommand;
}

DataBase::~DataBase() {
    closeConnection();
}



