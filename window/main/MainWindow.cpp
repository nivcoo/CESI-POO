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
    delete _customerBtnBack;
}


void MainWindow::initCustomerTab() {
    vector<CustomerModel::Customer> customers = CustomerService::getAllCustomers();
    for (auto customer : customers) {
        addCustomerToTable(customer);
    }
    connect(ui->pushButtonAddCustomer, SIGNAL(clicked()), this, SLOT(customerTabButtonClicked()));

}

void MainWindow::customerTabOrderButtonOnTableClicked(int customerID, const int i) {

    cout << customerID << " " << endl;

}


void MainWindow::customerTabEditButtonOnTableClicked(int customerID, int row) {
    ui->customerFormID->setValue(customerID);
    _customerBtnBack = new QPushButton("Back To Add new Customer");
    ui->customerFormTitleLayout->addWidget(_customerBtnBack);
    ui->titleCustomer->setText("Edit Customer Form");
    ui->pushButtonAddCustomer->setText("Edit Customer");

    CustomerModel::Customer customer = CustomerService::getCustomerByID(customerID);

    string birthDate = customer.birthDate;
    QDate date;
    date.fromString(birthDate.c_str(), "YYYY-MM-dd");

    ui->customerFormFirstName->setText(customer.firstname.c_str());
    ui->customerFormLastName->setText(customer.lastname.c_str());
    ui->customerFormBirthDate->setDate(date);

    vector<AddressModel::Address> address = CustomerService::getAllActiveAddressOfCustomerID(customer.id);


    for (auto ad : address) {
        stringstream postalCodeSS(ad.postalCode.c_str());
        int postalCode = 0;
        postalCodeSS >> postalCode;
        if (ad.type == 1) {
            ui->customerFormAddressLine1->setText(ad.addressLine.c_str());
            ui->customerFormCity1->setText(ad.city.c_str());
            ui->customerFormPostalCode1->setValue(postalCode);

        } else {
            ui->customerFormAddressLine2->setText(ad.addressLine.c_str());
            ui->customerFormCity2->setText(ad.city.c_str());
            ui->customerFormPostalCode2->setValue(postalCode);
        }

    }


    connect(_customerBtnBack, SIGNAL(clicked()), this, SLOT(customerTabCancelEdit()));
}

void MainWindow::customerTabCancelEdit() {
    ui->customerFormID->setValue(0);
    delete _customerBtnBack;
    ui->titleCustomer->setText("Add Customer Form");
    ui->pushButtonAddCustomer->setText("Add Customer");


    ui->customerFormFirstName->clear();
    ui->customerFormLastName->clear();
    ui->customerFormBirthDate->clear();

    ui->customerFormAddressLine1->clear();
    ui->customerFormCity1->clear();
    ui->customerFormPostalCode1->clear();

    ui->customerFormAddressLine2->clear();
    ui->customerFormCity2->clear();
    ui->customerFormPostalCode2->clear();

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

void MainWindow::customerTabButtonClicked() {


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


    int customerID = ui->customerFormID->value();
    cout << customerID << endl;
    if (!customerID) {
        customerID = CustomerService::addCustomer(customerFormFirstName, customerFormLastName,
                                                  SADateTime(customerFormBirthDate->date().year(),
                                                             customerFormBirthDate->date().month(),
                                                             customerFormBirthDate->date().day()));
    } else {
        CustomerService::editCustomerByID(customerID, customerFormFirstName, customerFormLastName,
                                          SADateTime(customerFormBirthDate->date().year(),
                                                     customerFormBirthDate->date().month(),
                                                     customerFormBirthDate->date().day()));
    }
    CustomerService::addAddressToCustomerID(customerID, 1, customerFormAddressLine1, customerFormPostalCode1,
                                            customerFormCity1);
    CustomerService::addAddressToCustomerID(customerID, 2, customerFormAddressLine2, customerFormPostalCode2,
                                            customerFormCity2);

    CustomerModel::Customer customer = CustomerService::getCustomerByID(customerID);
    if (!customerID) {
        addCustomerToTable(customer);
    }

    showPOPUpMessage(false, "Success !", "Adding the user with success !");

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

void MainWindow::addCustomerToTable(CustomerModel::Customer customer) {

    QTableWidget *tableWidget = ui->customerListTable;
    tableWidget->resizeColumnsToContents();


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

    QWidget *actionWidget = new QWidget();
    QHBoxLayout *pLayout = new QHBoxLayout(actionWidget);
    pLayout->addWidget(btnOrder);
    pLayout->addWidget(btnEdit);
    pLayout->addWidget(btnArchive);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 10, 0);
    actionWidget->setLayout(pLayout);

    tableWidget->setCellWidget(row, 0, actionWidget);
    tableWidget->setItem(row,
                         1,
                         new QTableWidgetItem(customer.firstname.c_str()));
    tableWidget->setItem(row,
                         2,
                         new QTableWidgetItem(customer.lastname.c_str()));
    tableWidget->setItem(row,
                         3,
                         new QTableWidgetItem(customer.birthDate.c_str()));

    vector<AddressModel::Address> address = CustomerService::getAllActiveAddressOfCustomerID(customer.id);


    for (auto ad : address) {
        if (ad.type == 2)
            continue;
        tableWidget->setItem(row,
                             4,
                             new QTableWidgetItem(ad.addressLine.c_str()));
        tableWidget->setItem(row,
                             5,
                             new QTableWidgetItem(ad.postalCode.c_str()));
        tableWidget->setItem(row,
                             6,
                             new QTableWidgetItem(ad.city.c_str()));
        break;
    }

}

