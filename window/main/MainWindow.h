//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_MAINWINDOW_H
#define MAIN_CPP_MAINWINDOW_H


#include <QMainWindow>
#include "../../service/CustomerService.h"
#include "../../service/StaffService.h"
#include "../../service/ItemService.h"
#include "../../service/OrderService.h"
#include <QMessageBox>
#include <sstream>
#include <algorithm>
#include <iterator>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    Ui::mainwindow *ui;

private:
    QPushButton *_customerBtnBack;
    QPushButton *_staffBtnBack;
    QPushButton *_itemBtnBack;

    void showPOPUpMessage(bool error, string title, string message);


private slots:

    void customerTabButtonClicked();

    void customerTabOrderButtonOnTableClicked(int customerID, int row);

    void customerTabEditButtonOnTableClicked(int customerID, int row);

    void customerTabArchiveButtonOnTableClicked(int customerID, int row);

    void initCustomerTab();

    void addCustomerToTable(CustomerModel::Customer customer);

    void customerTabCancelEdit();

    void clearCustomerInput();


    void staffTabButtonClicked();

    void staffTabOrderButtonOnTableClicked(int staffID, int row);

    void staffTabEditButtonOnTableClicked(int staffID, int row);

    void staffTabDeleteButtonOnTableClicked(int staffID, int row);

    void initStaffTab();

    void addStaffToTable(StaffModel::Staff staff);

    void staffTabCancelEdit();

    void clearStaffInput();




    void itemTabButtonClicked();

    void itemTabEditButtonOnTableClicked(string itemREF, int row);

    void itemTabArchiveButtonOnTableClicked(string itemREF, int row);

    void initItemTab();

    void addItemToTable(ItemModel::Item item);

    void itemTabCancelEdit();

    void clearItemInput();




    void orderTabButtonClicked();

    void orderTabEditButtonOnTableClicked(string orderREF, int row);

    void orderTabDeleteButtonOnTableClicked(string orderREF, int row);

    void initOrderTab();

    void addOrderToTable(OrderHistoryModel::Order order);

    void orderTabCancelEdit();

    void clearOrderInput();
};

#endif //MAIN_CPP_MAINWINDOW_H
