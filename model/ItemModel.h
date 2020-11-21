//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMMODEL_H
#define MAIN_CPP_ITEMMODEL_H


#include "../utils/DataBase.h"

class ItemModel {
public:
    void insert(string reference, string name, int resuply_threshold, int quantity, int price_ht, int vat);

    void archiveByID(string reference);

    void deleteByID(int id);

private:
    void send(SACommand *cmd);
};


#endif //MAIN_CPP_ITEMMODEL_H
