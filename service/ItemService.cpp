//
// Created by Nicolas on 20/11/2020.
//

#include "ItemService.h"
#include <regex>

string ItemService::addItem(string itemREF, string name, int resuplyThreshold, int quantity, double price_ht, double vat) {
    return ItemModel::insert(itemREF, name, resuplyThreshold, quantity, price_ht, vat, false);
}

ItemModel::Item ItemService::getItemByREF(string itemREF) {
    return ItemModel::getItemByREF(itemREF);
}

void ItemService::archiveItemByREF(string itemREF) {
    ItemModel::archiveByREF(itemREF);

}
