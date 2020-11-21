//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ADDRESSMODEL_H
#define MAIN_CPP_ADDRESSMODEL_H


#include "../utils/DataBase.h"

class AddressModel {


public:
    void insert(int type, string addressLine, string postalCode, string city, bool archived);

    void updateByID(int id, int type, string addressLine, string postalCode, string city, bool archived);

    void deleteByID(int id);

private:
    void send(SACommand *cmd);

};


#endif //MAIN_CPP_ADDRESSMODEL_H