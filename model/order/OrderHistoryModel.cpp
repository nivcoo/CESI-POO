//
// Created by Nicolas on 20/11/2020.
//

#include "OrderHistoryModel.h"
#include "../../ihm/IHM.h"

void OrderHistoryModel::insert(string reference, SADateTime estimatedDeliveryDate, int idCustomer, int idStaff,
                               int idDeliveryAddress, int idBillingAddress) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `order__history` VALUES (:1, :2, :3, :4, :5, :6, :7);");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    cmd.Param(2).setAsDateTime() = _TSA(estimatedDeliveryDate);
    cmd.Param(3).setAsDateTime() = SADateTime::currentDateTime();
    cmd.Param(4).setAsInt64() = _TSA(idCustomer);
    cmd.Param(5).setAsInt64() = _TSA(idStaff);
    cmd.Param(6).setAsInt64() = _TSA(idDeliveryAddress);
    cmd.Param(7).setAsInt64() = _TSA(idBillingAddress);
    ModelManager::sendCMD(&cmd);

}

void OrderHistoryModel::deleteById(string reference) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `order__history` WHERE `reference` = :1;");
    cmd.Param(1).setAsString() = _TSA(reference).c_str();
    ModelManager::sendCMD(&cmd);

}
