//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMMODEL_H
#define MAIN_CPP_ITEMMODEL_H


#include "../utils/DataBase.h"

class ItemModel {
public:

    struct Item {
        int id;
        string reference, name, birthDate;
        int resuply_threshold, quantity;
        float price_ht;
    };

    static int insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat);

    static void archiveByID(string reference);

    static Item getItemByID(int id);

    static void deleteByID(string reference);
};


#endif //MAIN_CPP_ITEMMODEL_H
