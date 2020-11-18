//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_TABMANAGER_H
#define MAIN_CPP_TABMANAGER_H


#include <QItemSelection>
#include <QTabWidget>
#include <QtWidgets>
#include "StaffTab.h"
#include "OrderTab.h"

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;

class QItemSelectionModel;

QT_END_NAMESPACE

class TabManager : public QTabWidget {
Q_OBJECT

private:
    StaffTab *staffTab;
    OrderTab *orderTab;
public:
    explicit TabManager(QWidget *parent = nullptr);

    void setupTabs();
};


#endif //MAIN_CPP_TABMANAGER_H
