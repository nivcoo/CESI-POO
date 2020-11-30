//
// Created by Nicolas on 20/11/2020.
//

#ifndef MAIN_CPP_ITEMSERVICE_H
#define MAIN_CPP_ITEMSERVICE_H

#include "../model/ItemModel.h"

using namespace std;

class ItemService {
public:

/**
 * Create an item
 * @param itemREF
 * @param name
 * @param resuplyThreshold
 * @param quantity
 * @param priceHt
 * @param vat
 * @return item reference
 */
    static string addItem(string itemREF, string name, int resuplyThreshold, int quantity, double priceHt, double vat);

/**
 * Update an item
 * @param reference
 * @param name
 * @param resuplyThreshold
 * @param quantity
 * @param priceHt
 * @param vat
 */
    static void updateItemByREF(string reference, string name, int resuplyThreshold, int quantity, double priceHt, double vat);

/**
 * Get an item by it's reference
 * @param itemREF
 * @return ItemModel::Item containing all infos about item
 */
    static ItemModel::Item getItemByREF(string itemREF);

/**
 * Archive an item (not available anymore but but still accessible in previous orders)
 * @param idStaff
 */
    static void archiveItemByREF(string idStaff);

/**
 * Get all items
 * @return vector of ItemModel::Item containing all infos about item
 */
    static vector<ItemModel::Item> getAllItems();

/**
 * Get items that are bellow their resupply threshold
 * @return vector of ItemModel::Item containing all infos about item
 */
    static vector<ItemModel::Item> getLowStockItems();

/**
 * Update quantity of a given item
 * @param reference
 * @param newQuantity
 */
    static void updateItemQuantityByREF(string reference, int newQuantity);

};


#endif //MAIN_CPP_ITEMSERVICE_H
