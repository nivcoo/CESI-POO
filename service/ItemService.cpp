//
// Created by Nicolas on 20/11/2020.
//

#include "ItemService.h"

int ItemService::addItem(string reference, string name, int resuply_threshold, int quantity, float price_ht) {
    int itemID = ItemModel::insert(reference, name, resuply_threshold, quantity, quantity, price_ht);
    return itemID;
}

ItemModel::Item ItemService::getItemByID(int itemID) {
    return ItemModel::getItemByID(itemID);
}