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

/**
 * Insert row in the item table
 * @param reference
 * @param name
 * @param resuplyThreshold
 * @param quantity
 * @param priceHt
 * @param vat
 * @param achived instead of deleting item, archive it to not lose it in previous orders
 * @return reference Insert row in the item table
 */
    static string insert(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat,
                      bool achived);

/**
 * Instead of deleting item, archive it to not lose it in previous orders
 * @param reference
 */
    static void archiveByREF(string reference);

    static vector<Item> getAllItems();

/**
 * Get a item by it's reference
 * @param id
 * @return ItemModel::Item struct that contain all data about an item
 */
    static Item getItemByREF(string reference);

    static vector<Item> getLowStockItems();

/**
 * Update quantity of an item
 * @param reference
 * @param newQuantity
 */
    static void updateQuantityOfItemREF(string reference, int newQuantity);

/**
 * Update row in the item table
 * @param reference
 * @param name
 * @param resuplyThreshold
 * @param quantity
 * @param priceHt
 * @param vat
 */
    static void updateByREF(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat);
};


#endif //MAIN_CPP_ITEMMODEL_H
