//
// Created by Nicolas on 20/11/2020.
//

#include "ItemService.h"

int ItemService::addItem(string reference, string name, int resuply_threshold, int quantity, double price_ht, double vat, bool isAchived = false) {
    return ItemModel::insert(reference, name, resuplyThreshold, quantity, price_ht, vat, isAchived); //???
}

ItemModel::Item ItemService::getItemByID(int itemID) {
    return ItemModel::getItemByID(itemID);
}