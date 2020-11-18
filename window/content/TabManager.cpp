//
// Created by Nicolas on 18/11/2020.
//

#include "TabManager.h"

TabManager::TabManager(QWidget *parent) :
        QTabWidget(parent), staffTab(new StaffTab(this)), orderTab(new OrderTab(this)) {
    //parent->setWindowTitle("test");
    setupTabs();



}


void TabManager::setupTabs() {
    addTab(staffTab, tr("STAFF"));
    addTab(orderTab, tr("ORDER"));

}



