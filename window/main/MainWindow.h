//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_MAINWINDOW_H
#define MAIN_CPP_MAINWINDOW_H


#include <QMainWindow>
#include "../../service/CustomerService.h"
#include "../../service/StaffService.h"
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

    void showPOPUpMessage(bool error, string title, string message);


private slots:

    void customerTabButtonClicked();

    void customerTabOrderButtonOnTableClicked(int customerID, int row);

    void customerTabEditButtonOnTableClicked(int customerID, int row);

    void customerTabArchiveButtonOnTableClicked(int customerID, int row);

    void initCustomerTab();

    void addCustomerToTable(CustomerModel::Customer customer);

    void customerTabCancelEdit();














    void staffTabButtonClicked();

    void staffTabOrderButtonOnTableClicked(int staffID, int row);

    void staffTabEditButtonOnTableClicked(int staffID, int row);

    void staffTabArchiveButtonOnTableClicked(int staffID, int row);

    void initStaffTab();

    void addStaffToTable(StaffModel::Staff staff);

    void staffTabCancelEdit();

    void clearCustomerInput();

    void clearStaffInput();
};

#endif //MAIN_CPP_MAINWINDOW_H
