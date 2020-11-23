//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMSERVICE_H
#define MAIN_CPP_ITEMSERVICE_H

#include "../model/ItemModel.h"

using namespace std;

class ItemService {
public:
    static string addItem(string itemREF, string name, int resuplyThreshold, int quantity, double priceHt, double vat);

    static ItemModel::Item getItemByREF(string itemREF);

    static void archiveItemByREF(string idStaff);

};


#endif //MAIN_CPP_ITEMSERVICE_H
