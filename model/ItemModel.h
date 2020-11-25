//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMMODEL_H
#define MAIN_CPP_ITEMMODEL_H

#include <vector>
#include "../utils/DataBase.h"

class ItemModel {
public:

    struct Item {
        string reference, name;
        int resuplyThreshold, quantity;
        double priceHt, vat;
        bool archived;
    };

    static string insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat,
                      bool achived);

    static void archiveByREF(string reference);

    static vector<Item> getAllItems();

    static Item getItemByREF(string reference);

    static vector<Item> getLowStockItems();

    static void deleteByREF(string reference);

    static void updateQuantityOfItemREF(string reference, int newQuantity);
};


#endif //MAIN_CPP_ITEMMODEL_H
