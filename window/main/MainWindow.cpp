#include "MainWindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::mainwindow) {
    ui->setupUi(this);

    initCustomerTab();

}


MainWindow::~MainWindow() {

    delete ui;
}


void MainWindow::initCustomerTab() {

    QTableWidget *tableWidget = ui->customerListTable;

    vector<CustomerModel::Customer> customers = CustomerService::getAllCustomers();
    for (auto customer : customers) {
        tableWidget->insertRow(tableWidget->rowCount());


        QPushButton *btnOrder = new QPushButton("Do Order");
        QPushButton *btnEdit = new QPushButton("Edit");
        QPushButton *btnArchive = new QPushButton("Archive");
        int id = customer.id;

        int row = tableWidget->rowCount() - 1;
        connect(btnOrder, &QPushButton::clicked, [this, id, row] { customerTabOrderButtonOnTableClicked(id, row); });
        connect(btnEdit, &QPushButton::clicked, [this, id, row] { customerTabEditButtonOnTableClicked(id, row); });
        connect(btnArchive, &QPushButton::clicked,
                [this, id, row] { customerTabArchiveButtonOnTableClicked(id, row); });

        tableWidget->setCellWidget(row, 0, btnOrder);
        tableWidget->setCellWidget(row, 1, btnEdit);
        tableWidget->setCellWidget(row, 2, btnArchive);
        tableWidget->setItem(row,
                             3,
                             new QTableWidgetItem(customer.firstname.c_str()));
        tableWidget->setItem(row,
                             4,
                             new QTableWidgetItem(customer.lastname.c_str()));
        tableWidget->setItem(row,
                             5,
                             new QTableWidgetItem(customer.birthDate.c_str()));

        vector<AddressModel::Address> address = CustomerService::getAllActiveAddressOfCustomerID(customer.id);


        for (auto ad : address) {
            if (ad.type == 2)
                continue;
            tableWidget->setItem(row,
                                 6,
                                 new QTableWidgetItem(ad.addressLine.c_str()));
            tableWidget->setItem(row,
                                 7,
                                 new QTableWidgetItem(ad.postalCode.c_str()));
            tableWidget->setItem(row,
                                 8,
                                 new QTableWidgetItem(ad.city.c_str()));
            break;
        }

    }


    connect(ui->pushButtonAddCustomer, SIGNAL(clicked()), this, SLOT(customerTabButtonAddClicked()));

}






void MainWindow::customerTabOrderButtonOnTableClicked(int customerID, const int i) {

    cout << customerID << " " << endl;

}


void MainWindow::customerTabEditButtonOnTableClicked(int customerID, int row) {

    cout << customerID << " " << endl;

}

void MainWindow::customerTabArchiveButtonOnTableClicked(int customerID, int row) {

    if (!customerID) {
        showPOPUpMessage(true, "Error line !", "The application can't access to the ID");
        return;
    }

    CustomerService::archiveCustomerByID(customerID);
    ui->customerListTable->removeRow(row);
    showPOPUpMessage(false, "Success !", "The customer was archived");

}

void MainWindow::customerTabButtonAddClicked() {

    cout << "clicked" << endl;
    string customerFormFirstName = ui->customerFormFirstName->text().toStdString();
    string customerFormLastName = ui->customerFormLastName->text().toStdString();
    QDateEdit *customerFormBirthDate = ui->customerFormBirthDate;
    string customerFormAddressLine1 = ui->customerFormAddressLine1->text().toStdString();
    string customerFormCity1 = ui->customerFormCity1->text().toStdString();
    string customerFormPostalCode1 = ui->customerFormPostalCode1->text().toStdString();
    string customerFormAddressLine2 = ui->customerFormAddressLine2->text().toStdString();
    string customerFormCity2 = ui->customerFormCity2->text().toStdString();
    string customerFormPostalCode2 = ui->customerFormPostalCode2->text().toStdString();

    if (empty(customerFormFirstName) || empty(customerFormLastName) ||
        empty(customerFormBirthDate->text().toStdString()) ||
        empty(customerFormAddressLine1) || empty(customerFormCity1) || empty(customerFormPostalCode1) ||
        empty(customerFormAddressLine2) || empty(customerFormCity2) || empty(customerFormPostalCode2)) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }

    int customerID = CustomerService::addCustomer(customerFormFirstName, customerFormLastName,
                                                  SADateTime(customerFormBirthDate->date().year(),
                                                             customerFormBirthDate->date().month(),
                                                             customerFormBirthDate->date().day()));
    CustomerService::addAddressToCustomerID(customerID, 1, customerFormAddressLine1, customerFormPostalCode1,
                                            customerFormCity1);
    CustomerService::addAddressToCustomerID(customerID, 2, customerFormAddressLine2, customerFormPostalCode2,
                                            customerFormCity2);

    QTableWidget *tableWidget = ui->customerListTable;
    CustomerModel::Customer customer = CustomerService::getCustomerByID(customerID);

    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(tableWidget->rowCount() - 1,
                         0,
                         new QTableWidgetItem(customer.firstname.c_str()));
    tableWidget->setItem(tableWidget->rowCount() - 1,
                         1,
                         new QTableWidgetItem(customer.lastname.c_str()));
    tableWidget->setItem(tableWidget->rowCount() - 1,
                         2,
                         new QTableWidgetItem(customer.birthDate.c_str()));

    tableWidget->setItem(tableWidget->rowCount() - 1,
                         3,
                         new QTableWidgetItem(customerFormAddressLine1.c_str()));
    tableWidget->setItem(tableWidget->rowCount() - 1,
                         4,
                         new QTableWidgetItem(customerFormPostalCode1.c_str()));
    tableWidget->setItem(tableWidget->rowCount() - 1,
                         5,
                         new QTableWidgetItem(customerFormCity1.c_str()));

    showPOPUpMessage(false, "Success !", "Adding the user is in progress!");


}


void MainWindow::showPOPUpMessage(bool error, string title, string message) {
    QMessageBox msgBox;
    if (error) {
        msgBox.setText(title.c_str());
        msgBox.setWindowTitle("Warning !");
        msgBox.setIcon(QMessageBox::Warning);
    } else {
        msgBox.setText(title.c_str());
        msgBox.setWindowTitle("Information !");
        msgBox.setIcon(QMessageBox::Information);
    }
    msgBox.setInformativeText(message.c_str());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setMinimumSize(400, 400);
    msgBox.exec();

}
