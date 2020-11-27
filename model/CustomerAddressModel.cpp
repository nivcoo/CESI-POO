//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerAddressModel.h"
#include "ModelManager.h"

int CustomerAddressModel::insert(int idCustomer, int idAddress) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer_address` VALUES (:1, :2); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsInt64() = _TSA(idCustomer);
    cmd.Param(2).setAsInt64() = _TSA(idAddress);
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    ModelManager::get()->getDataBase()->closeConnection();
    return id;
}

void CustomerAddressModel::deleteByID(int idCustomer, int idAddress) {

    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer_address` WHERE `id_customer` = :1 AND `id_address` = :2;");
    cmd.Param(1).setAsInt64() = _TSA(idCustomer);
    cmd.Param(2).setAsInt64() = _TSA(idAddress);
    ModelManager::sendCMD(&cmd);

}


vector<AddressModel::Address> CustomerAddressModel::getAllActiveAddressOfCustomerID(int customerID) {
    SACommand cmd;
    cmd.setCommandText(
            "SELECT ad.* FROM `customer_address` ca INNER join address ad on ad.id = ca.id_address WHERE ca.id = :1;");
    cmd.Param(1).setAsInt64() = customerID;
    ModelManager::sendCMD(&cmd, false);

    AddressModel::Address address;
    vector<AddressModel::Address> allAddress;
    while (cmd.FetchNext()) {
        address.id = cmd.Field("id").asInt64();
        address.type = cmd.Field("type").asInt64();
        address.addressLine = cmd.Field("address_line").asString().GetMultiByteChars();
        address.postalCode = cmd.Field("postal_code").asString().GetMultiByteChars();
        address.city = cmd.Field("city").asString().GetMultiByteChars();
        address.archived = cmd.Field("archived").asBool();
        if (!address.archived)
            allAddress.push_back(address);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return allAddress;
}


void CustomerAddressModel::archiveAddressOfCustomerIDByType(int customerID, int type) {
    SACommand cmd;
    cmd.setCommandText(
            "UPDATE address, customer_address SET address.archived = :1 WHERE customer_address.id_address = address.id AND customer_address.id = :2 AND address.type = :3");
    cmd.Param(1).setAsBool() = true;
    cmd.Param(2).setAsInt64() = customerID;
    cmd.Param(3).setAsInt64() = type;
    ModelManager::sendCMD(&cmd);
}
