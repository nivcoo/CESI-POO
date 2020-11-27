//
// Created by Nicolas on 20/11/2020.
//

#include "OrderPaymentModel.h"
#include "../ModelManager.h"

int OrderPaymentModel::insert(int paymentMethod, double amount, string orderReference) {
    SACommand cmd;
    cmd.setCommandText("INSERT INTO `order__payment` VALUES (:1, :2, :3, :4, :5); SELECT LAST_INSERT_ID();");
    cmd.Param(1).setAsNull();
    cmd.Param(2).setAsInt64() = _TSA(paymentMethod);
    cmd.Param(3).setAsDouble() = _TSA(amount);
    cmd.Param(4).setAsDateTime() = SADateTime::currentDateTime();
    cmd.Param(5).setAsString() = _TSA(orderReference).c_str();
    ModelManager::sendCMD(&cmd, false);
    cmd.FetchNext();
    int id = cmd[1].asInt64();
    ModelManager::get()->getDataBase()->closeConnection();
    return id;
}

void OrderPaymentModel::deleteByID(int id) {
    SACommand cmd;
    cmd.setCommandText("DELETE FROM `order__payment` WHERE `id` = :1;");
    cmd.Param(1).setAsInt64() = _TSA(id);
    ModelManager::sendCMD(&cmd);

}
