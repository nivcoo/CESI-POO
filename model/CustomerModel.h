//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERMODEL_H
#define MAIN_CPP_CUSTOMERMODEL_H


#include <vector>
#include "../utils/DataBase.h"

class CustomerModel {

public:

    struct Customer {
        int id;
        string lastname, firstname;
        SADateTime birthDate;
    };

    static int insert(string firstname, string lastname, SADateTime birthDate);

    static void updateByID(int id, string firstname, string lastname, SADateTime birthDate);

    static void deleteByID(int id);

    static Customer getCustomerByID(int id);

    static std::vector<Customer> getAllCustomers();

    static vector<Customer> getAllCustomersByFirstAndLastName(string firstname, string lastname);

    static void archivedByID(int id);
};


#endif //MAIN_CPP_CUSTOMERMODEL_H
