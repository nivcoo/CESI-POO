//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerAddressModel.h"
#include "../ihm/IHM.h"

int CustomerAddressModel::insert(int idCustomer, int idAddress) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer_address` VALUES (:1, :2); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsInt64() = _TSA(idCustomer);
    cmd.Param(2).setAsInt64()  = _TSA(idAddress);
    IHM::get()->getModelManager()->sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    IHM::get()->getDataBase()->closeConnection();
    return id;
}

void CustomerAddressModel::deleteByID(int idCustomer, int idAddress) {

    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer_address` WHERE `id_customer` = :1 AND `id_address` = :2;");
    cmd.Param(1).setAsInt64() = _TSA(idCustomer);
    cmd.Param(2).setAsInt64() = _TSA(idAddress);
    IHM::get()->getModelManager()->sendCMD(&cmd);

}
