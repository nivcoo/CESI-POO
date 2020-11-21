//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ADDRESSMODEL_H
#define MAIN_CPP_ADDRESSMODEL_H


#include "../utils/DataBase.h"

class AddressModel {


public:
    static int insert(int type, string addressLine, string postalCode, string city, bool archived);

    static void updateByID(int id, int type, string addressLine, string postalCode, string city, bool archived);

    static void deleteByID(int id);

    static void archiveAllType(int id, int type);
};


#endif //MAIN_CPP_ADDRESSMODEL_H
