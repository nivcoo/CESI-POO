//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_MAINWINDOW_H
#define MAIN_CPP_MAINWINDOW_H


#include <QMainWindow>
#include "../../service/CustomerService.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    void showPOPUpMessage(bool error, string title, string message);

    Ui::mainwindow *ui;

private slots:
    void customerTabButtonAddClicked();
    void customerTabOrderButtonOnTableClicked(int customerID, int row);
    void customerTabEditButtonOnTableClicked(int customerID, int row);
    void customerTabArchiveButtonOnTableClicked(int customerID, int row);

    void initCustomerTab();
};

#endif //MAIN_CPP_MAINWINDOW_H
