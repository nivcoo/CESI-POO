//
// Created by Nicolas on 19/11/2020.
//

#ifndef MAIN_CPP_IHM_H
#define MAIN_CPP_IHM_H

#include "../utils/DataBase.h"
#include "../model/ModelManager.h"
#include "../service/CustomerService.h"
#include "../service/ItemService.h"
#include "../service/OrderService.h"
#include "../service/StaffService.h"

class IHM {

public:
    IHM();

    ~IHM();

    IHM(const IHM &other) = delete;

    static IHM *get();

    ModelManager *getModelManager();

    ItemService *getItemService();

    OrderService *getOrderService();

    StaffService *getStaffService();

    DataBase *getDataBase();


private:
    static IHM *INSTANCE;

    void initDB();

    void initServices();

    ModelManager *_modelManager;
    DataBase *_db;
    CustomerService *_customerService;
    ItemService *_itemService;
    OrderService *_orderService;
    StaffService *_staffService;
};


#endif //MAIN_CPP_IHM_H
