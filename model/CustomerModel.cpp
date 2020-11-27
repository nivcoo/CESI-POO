//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerModel.h"
#include "ModelManager.h"

struct CustomerModel::Customer customer;


int CustomerModel::insert(string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer` VALUES (:1, :2, :3, :4, :5); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsString() = _TSA(firstname.c_str());
    cmd.Param(3).setAsString() = _TSA(lastname.c_str());
    cmd.Param(4).setAsDateTime() = _TSA(birthDate);
    cmd.Param(5).setAsBool() = false;
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    ModelManager::get()->getDataBase()->closeConnection();
    return id;
}

void CustomerModel::updateByID(int id, string firstname, string lastname, SADateTime birthDate) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `customer` SET firstname=:1, lastname=:2, birth_date=:3 WHERE `id`=:4;");

    cmd.Param(1).setAsString() = _TSA(firstname.c_str());
    cmd.Param(2).setAsString() = _TSA(lastname.c_str());
    cmd.Param(3).setAsDateTime() = _TSA(birthDate);
    cmd.Param(4).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);

}

void CustomerModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);
}

void CustomerModel::archivedByID(int id) {
    SACommand cmd;
    cmd.setCommandText("UPDATE `customer` SET `archived`=:1 WHERE `id`=:2;");
    cmd.Param(1).setAsBool() = _TSA(true);
    cmd.Param(2).setAsInt64() = _TSA(id);
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
        customer.birthDate = cmd.Field("birth_date").asDateTime();
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return customer;
}


vector<CustomerModel::Customer> CustomerModel::getAllCustomers() {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `customer` WHERE `archived` = :1;");
    cmd.Param(1).setAsBool() = _TSA(false);
    ModelManager::sendCMD(&cmd, false);

    vector<CustomerModel::Customer> customers;

    while (cmd.FetchNext()) {
        customer.id = cmd.Field("id").asInt64();
        customer.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        customer.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        customer.birthDate = cmd.Field("birth_date").asDateTime();
        customers.push_back(customer);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return customers;
}


vector<CustomerModel::Customer> CustomerModel::getAllCustomersByFirstAndLastName(string firstname, string lastname) {
    SACommand cmd;
    cmd.setCommandText("SELECT * FROM `customer` WHERE `firstname` = :1 AND `lastname` = :2 AND `archived` = :3;");
    cmd.Param(1).setAsString() = _TSA(firstname.c_str());
    cmd.Param(2).setAsString() = _TSA(lastname.c_str());
    cmd.Param(3).setAsBool() = _TSA(false);
    ModelManager::sendCMD(&cmd, false);
    vector<CustomerModel::Customer> customers;
    while (cmd.FetchNext()) {
        customer.id = cmd.Field("id").asInt64();
        customer.firstname = cmd.Field("firstname").asString().GetMultiByteChars();
        customer.lastname = cmd.Field("lastname").asString().GetMultiByteChars();
        customer.birthDate = cmd.Field("birth_date").asDateTime();
        customers.push_back(customer);
    }
    ModelManager::get()->getDataBase()->closeConnection();
    return customers;
}


