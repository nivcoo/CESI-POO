//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_MAINWINDOW_H
#define MAIN_CPP_MAINWINDOW_H


#include <QMainWindow>
#include "../../service/CustomerService.h"
#include <QMessageBox>
#include <sstream>

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

    void showPOPUpMessage(bool error, string title, string message);


private slots:

    void customerTabButtonClicked();

    void customerTabOrderButtonOnTableClicked(int customerID, int row);

    void customerTabEditButtonOnTableClicked(int customerID, int row);

    void customerTabArchiveButtonOnTableClicked(int customerID, int row);

    void initCustomerTab();

    void addCustomerToTable(CustomerModel::Customer customer);

    void customerTabCancelEdit();
};

#endif //MAIN_CPP_MAINWINDOW_H
