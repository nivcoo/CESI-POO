//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_CUSTOMERADDRESSMODEL_H
#define MAIN_CPP_CUSTOMERADDRESSMODEL_H

#include <vector>
#include "../utils/DataBase.h"
#include "AddressModel.h"

class CustomerAddressModel {
public:

    static int insert(int idCustomer, int idAddress);

    static void deleteByID(int idCustomer, int idAddress);

    static vector<AddressModel::Address> getAllAddressOfCustomerID(int customerID);
};


#endif //MAIN_CPP_CUSTOMERADDRESSMODEL_H
