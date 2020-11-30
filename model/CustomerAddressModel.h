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

/**
 * Insert a row in customer_address table to make correspond a customer and it's addresses
 * @param idCustomer
 * @param idAddress
 * @return id of the row inserted
 */
    static int insert(int idCustomer, int idAddress);

/**
 * Get the addresses of a customer
 * @param customerID
 * @return vector of addresses
 */
    static vector<AddressModel::Address> getAllActiveAddressOfCustomerID(int customerID);

/**
 * Instead of deleting address, archive it to not lose it in previous orders
 * @param customerID
 * @param type
 */
    static void archiveAddressOfCustomerIDByType(int customerID, int type);
};


#endif //MAIN_CPP_CUSTOMERADDRESSMODEL_H
