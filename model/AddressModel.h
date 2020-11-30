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

/**
 * iInsert a row in the model table
 * @param type
 * @param addressLine
 * @param postalCode
 * @param city
 * @return id of the inserted address
 */
    static int insert(int type, string addressLine, string postalCode, string city);

/**
 * Instead of deleting address, archive it to not lose it in previous orders
 * @param id
 */
static void archiveByID(int id);

};


#endif //MAIN_CPP_ADDRESSMODEL_H
