//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMMODEL_H
#define MAIN_CPP_ITEMMODEL_H


#include "../utils/DataBase.h"

class ItemModel {
public:
    int insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat);

    void archiveByID(string reference);

    void deleteByID(string reference);
};


#endif //MAIN_CPP_ITEMMODEL_H
