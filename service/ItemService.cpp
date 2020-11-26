//
// Created by Nicolas on 20/11/2020.
//

#include "ItemService.h"
#include <regex>

string
ItemService::addItem(string itemREF, string name, int resuplyThreshold, int quantity, double price_ht, double vat) {
    return ItemModel::insert(itemREF, name, resuplyThreshold, quantity, price_ht, vat, false);
}

ItemModel::Item ItemService::getItemByREF(string itemREF) {
    return ItemModel::getItemByREF(itemREF);
}

void ItemService::archiveItemByREF(string itemREF) {
    ItemModel::archiveByREF(itemREF);

}

void ItemService::updateItemQuantityByREF(string reference, int newQuantity) {
    ItemModel::updateQuantityOfItemREF(reference, newQuantity);
}

vector<ItemModel::Item> ItemService::getLowStockItems() {
    return ItemModel::getLowStockItems();
}

vector<ItemModel::Item> ItemService::getAllItems() {
    return ItemModel::getAllItems();
}

void ItemService::updateItemByREF(string reference, string name, int resuplyThreshold, int quantity, double priceHt,
                                  double vat) {
    ItemModel::updateByREF(reference, name, resuplyThreshold, quantity, priceHt, vat);
}
