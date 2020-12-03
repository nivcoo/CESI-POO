//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_MAINWINDOW_H
#define MAIN_CPP_MAINWINDOW_H


#include <QMainWindow>
#include "../../model/ModelManager.h"
#include "../../service/CustomerService.h"
#include "../../service/StaffService.h"
#include "../../service/ItemService.h"
#include "../../service/OrderService.h"
#include "../../service/StatsService.h"
#include <QMessageBox>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
Q_OBJECT

public:

    struct OrderItemWidget {
        QLayout *layout;
        QComboBox *itemSelect;
        QSpinBox *quantity;
        QDoubleSpinBox *commercialDiscount;
        QDoubleSpinBox *priceIT;
    };

    struct OrderPaymentWidget {
        QSpinBox *id;
        QLayout *layout;
        QComboBox *paymentSelect;
        QDoubleSpinBox *amount;
    };

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    Ui::mainwindow *ui;

private:

    int orderFormCustomerID = 0;
    int orderFormStaffID = 0;
    int customerFormID = 0;
    int staffFormID = 0;
    string orderFormREF;
    string itemFormREFSave;
    ModelManager *_modelManager;
    QPushButton *_customerBtnBack;
    QPushButton *_staffBtnBack;
    QPushButton *_itemBtnBack;
    vector<OrderItemWidget> _orderItemWidgets;
    vector<OrderPaymentWidget> _orderPaymentWidgets;

    static void showPOPUpMessage(bool error, string title, string message);

    void initCustomerTab();

    void initStaffTab();

    void initStatTab();

    void initItemTab();

    void initOrderTab();

    void statInitSelectValue();

    void clearCustomerInput();

    void clearStaffInput();

    void clearItemInput();

    void clearOrderInput();

    void addCustomerToTable(CustomerModel::Customer customer);

    void addStaffToTable(StaffModel::Staff staff);

    void addItemToTable(ItemModel::Item item);

    void addOrderToTable(OrderHistoryModel::Order order);

    void statAddItemToTable(ItemModel::Item item, QTableWidget *tableWidget);

    void orderTabAddItemsToComboBox(QComboBox *itemSelect);

    void orderTabAddPaymentsToComboBox(QComboBox *itemSelect);

    bool orderCheckItemQuantityError();


private slots:


    void customerTabButtonClicked();

    void customerTabOrderButtonOnTableClicked(int customerID, int row);

    void customerTabEditButtonOnTableClicked(int customerID, int row);

    void customerTabArchiveButtonOnTableClicked(int customerID, int row);

    void customerTabCancelEditClicked();

    void staffTabButtonClicked();

    void staffTabOrderButtonOnTableClicked(int staffID, int row);

    void staffTabEditButtonOnTableClicked(int staffID, int row);

    void staffTabDeleteButtonOnTableClicked(int staffID, int row);

    void staffTabCancelEditClicked();

    void itemTabButtonClicked();

    void itemTabEditButtonOnTableClicked(string itemREF, int row);

    void itemTabArchiveButtonOnTableClicked(string itemREF, int row);

    void itemTabCancelEditClicked();

    void orderTabButtonClicked();

    void orderTabButtonResetOrderClicked();

    void orderTabButtonCalculOrderClicked();

    void orderTabButtonAddPaymentToOrderClicked(int idVal = 0, int type = 0, double amountVal = 0);

    void orderTabButtonAddItemToOrderClicked(string ref = "", int quantityVal = 0, double commercialDiscountVal = 0,
                                             double priceIT = 0);

    void orderTabEditButtonOnTableClicked(string orderREF, int row);

    void orderTabDeleteButtonOnTableClicked(string orderREF, int row);

    void statTabButtonAverageCartClicked();

    void statTabButtonMonthlyEarningClicked();

    void statTabButtonCustomerTotalPurschasesClicked();

    void statTabButtonCommercialValueClicked();

    void statTabButtonPurchaseValueClicked();

    void statTabButtonSimulateVariationClicked();

};

#endif //MAIN_CPP_MAINWINDOW_H
