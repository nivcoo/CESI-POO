//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerModel.h"
#include "../ihm/IHM.h"

struct CustomerModel::Customer customer;


int CustomerModel::insert(string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer` VALUES (:1, :2, :3, :4); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsString() = firstname.c_str();
    cmd.Param(3).setAsString() = lastname.c_str();
    cmd.Param(4).setAsDateTime() = birthDate;
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    IHM::get()->getDataBase()->closeConnection();
    return id;
}

void CustomerModel::updateByID(int id, string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `customer` SET firstname=:1, lastname=:2, birth_date=:3 WHERE `id`=:4;");

    cmd.Param(1).setAsString() = firstname.c_str();
    cmd.Param(2).setAsString() = lastname.c_str();
    cmd.Param(3).setAsDateTime() = birthDate;
    cmd.Param(4).setAsInt64() = id;
    ModelManager::sendCMD(&cmd);

}

void CustomerModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = id;
    ModelManager::sendCMD(&cmd);
}


CustomerModel::Customer CustomerModel::getCustomerByID(int id) {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = id;
    ModelManager::sendCMD(&cmd, false);

    while (cmd.FetchNext()) {
        customer.id = cmd.Field("id").asInt64();
        customer.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        customer.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        customer.birthDate = cmd.Field("birth_date").asString().GetMultiByteChars();
    }
    IHM::get()->getDataBase()->closeConnection();
    return customer;
}


vector<CustomerModel::Customer> CustomerModel::getAllCustomers() {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `customer`");
    ModelManager::sendCMD(&cmd, false);

    vector<CustomerModel::Customer> customers;

    while (cmd.FetchNext()) {
        customer.id = cmd.Field("id").asInt64();
        customer.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        customer.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        customer.birthDate = cmd.Field("birth_date").asString().GetMultiByteChars();
        customers.push_back(customer);
    }
    IHM::get()->getDataBase()->closeConnection();
    return customers;
}


vector<CustomerModel::Customer> CustomerModel::getAllCustomersByFirstAndLastName(string firstname, string lastname) {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `customer` WHERE `firstname` = :1 AND `lastname` = :2;");
    cmd.Param(1).setAsString() = firstname.c_str();
    cmd.Param(2).setAsString() = lastname.c_str();
    ModelManager::sendCMD(&cmd, false);
    vector<CustomerModel::Customer> customers;
    while (cmd.FetchNext()) {
        customer.id = cmd.Field("id").asInt64();
        customer.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        customer.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        customer.birthDate = cmd.Field("birth_date").asString().GetMultiByteChars();
        customers.push_back(customer);
    }
    IHM::get()->getDataBase()->closeConnection();
    return customers;
}


