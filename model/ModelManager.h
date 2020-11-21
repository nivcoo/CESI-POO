//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_MODELMANAGER_H
#define MAIN_CPP_MODELMANAGER_H


#include "../utils/DataBase.h"
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include "CustomerModel.h"
#include "AddressModel.h"
#include "order/OrderItemModel.h"
#include "order/OrderHistoryModel.h"
#include "order/OrderPaymentModel.h"
#include "ItemModel.h"
#include "CustomerAddressModel.h"
#include "StaffModel.h"

class ModelManager {

public:
    ModelManager();
    ~ModelManager();


private:

    void initModel();

    OrderHistoryModel * _orderHistoryModel;
    OrderItemModel * _orderItemModel;
    OrderPaymentModel * _orderPaymentModel;
    AddressModel * _addressModel;
    CustomerAddressModel * _customerAddressModel;
    CustomerModel * _customerModel;
    ItemModel * _itemModel;
    StaffModel * _staffModel;

    void initDB();
};


#endif //MAIN_CPP_MODELMANAGER_H