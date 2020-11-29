//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ADDRESSMODEL_H
#define MAIN_CPP_ADDRESSMODEL_H

#include "../utils/DataBase.h"

class AddressModel {

public:

    struct Address {
        int id, type;
        string addressLine, postalCode, city;
        bool archived;
    };

    static int insert(int type, string addressLine, string postalCode, string city);

    static void archiveByID(int id);

};


#endif //MAIN_CPP_ADDRESSMODEL_H
