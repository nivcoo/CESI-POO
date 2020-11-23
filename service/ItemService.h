//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMSERVICE_H
#define MAIN_CPP_ITEMSERVICE_H

#include "../model/ItemModel.h"

using namespace std;

class ItemService {
public:
    static int addItem(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat, bool isAchived = false);
    static ItemModel::Item getItemByID(int itemID);

};


#endif //MAIN_CPP_ITEMSERVICE_H
