//
// Created by Nicolas on 20/11/2020.
//

#include "CustomerAddressModel.h"
#include "../ihm/IHM.h"

void CustomerAddressModel::insert(int idCustomer, int idAddress) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `customer_address` VALUES (:1, :2);");
    cmd.Param(1).setAsInt64() = _TSA(idCustomer);
    cmd.Param(2).setAsInt64()  = _TSA(idAddress);
    IHM::get()->getModelManager()->sendCMD(&cmd);
}

void CustomerAddressModel::deleteByID(int idCustomer, int idAddress) {

    SACommand cmd;
    cmd.setCommandText("DELETE FROM `customer_address` WHERE `id_customer` = :1 AND `id_address` = :2;");
    cmd.Param(1).setAsInt64() = _TSA(idCustomer);
    cmd.Param(2).setAsInt64() = _TSA(idAddress);
    IHM::get()->getModelManager()->sendCMD(&cmd);

}
