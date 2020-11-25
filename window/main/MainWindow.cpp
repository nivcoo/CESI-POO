#include "MainWindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::mainwindow) {
    ui->setupUi(this);

    initCustomerTab();
    initStaffTab();
}

MainWindow::~MainWindow() {
    delete ui;
    delete _customerBtnBack;
    delete _staffBtnBack;
}


void MainWindow::initCustomerTab() {
    clearCustomerInput();
    auto customers = CustomerService::getAllCustomers();
    for (auto customer : customers) {
        addCustomerToTable(customer);
    }
    connect(ui->pushButtonAddCustomer, SIGNAL(clicked()), this, SLOT(customerTabButtonClicked()));

}

void MainWindow::initStaffTab() {
    clearStaffInput();

    auto staffs = StaffService::getAllStaffs();
    for (auto staff : staffs) {
        addStaffToTable(staff);
    }
    connect(ui->pushButtonAddStaff, SIGNAL(clicked()), this, SLOT(staffTabButtonClicked()));

}

void MainWindow::customerTabOrderButtonOnTableClicked(int customerID, const int i) {
}

void MainWindow::staffTabOrderButtonOnTableClicked(int staffID, const int i) {
}


void MainWindow::customerTabEditButtonOnTableClicked(int customerID, int row) {
    if (ui->customerFormID->value())
        return;
    ui->customerFormID->setValue(customerID);
    _customerBtnBack = new QPushButton("Back To Add new Customer");
    ui->customerFormTitleLayout->addWidget(_customerBtnBack);
    ui->titleCustomer->setText("Edit Customer Form");
    ui->pushButtonAddCustomer->setText("Edit Customer");

    auto customer = CustomerService::getCustomerByID(customerID);

    SADateTime birthDate = customer.birthDate;
    QDate date;

    date.setDate(birthDate.GetYear(), birthDate.GetMonth(), birthDate.GetDay());

    ui->customerFormFirstName->setText(customer.firstname.c_str());
    ui->customerFormLastName->setText(customer.lastname.c_str());
    ui->customerFormBirthDate->setDate(date);

    auto address = CustomerService::getAllActiveAddressOfCustomerID(customer.id);


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

void MainWindow::staffTabEditButtonOnTableClicked(int staffID, int row) {
    if (ui->staffFormID->value())
        return;
    cout << "tyjty" << endl;
    ui->staffFormID->setValue(staffID);
    _staffBtnBack = new QPushButton("Back To Add new Staff");
    ui->staffFormTitleLayout->addWidget(_staffBtnBack);
    ui->titleStaff->setText("Edit Staff Form");
    ui->pushButtonAddStaff->setText("Edit Staff");

    auto staff = StaffService::getStaffByID(staffID);

    SADateTime hireDate = staff.hireDate;
    QDate date;

    date.setDate(hireDate.GetYear(), hireDate.GetMonth(), hireDate.GetDay());
    ui->staffFormFirstName->setText(staff.firstname.c_str());
    ui->staffFormLastName->setText(staff.lastname.c_str());
    ui->staffFormHireDate->setDate(date);

    stringstream postalCodeSS(staff.postalCode.c_str());
    int postalCode = 0;
    postalCodeSS >> postalCode;

    ui->staffFormAddressLine->setText(staff.addressLine.c_str());
    ui->staffFormCity->setText(staff.city.c_str());
    ui->staffFormPostalCode->setValue(postalCode);

    connect(_staffBtnBack, SIGNAL(clicked()), this, SLOT(staffTabCancelEdit()));
}

void MainWindow::customerTabCancelEdit() {
    delete _customerBtnBack;
    ui->titleCustomer->setText("Add Customer Form");
    ui->pushButtonAddCustomer->setText("Add Customer");
    clearCustomerInput();

}

void MainWindow::staffTabCancelEdit() {
    delete _staffBtnBack;
    ui->titleStaff->setText("Add Staff Form");
    ui->pushButtonAddStaff->setText("Add Staff");
    clearStaffInput();

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

void MainWindow::staffTabArchiveButtonOnTableClicked(int staffID, int row) {

    if (!staffID) {
        showPOPUpMessage(true, "Error line !", "The application can't access to the ID");
        return;
    }

    StaffService::deleteStaffByID(staffID);
    ui->staffListTable->removeRow(row);
    showPOPUpMessage(false, "Success !", "The staff was deleted");

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
        empty(customerFormAddressLine2) || empty(customerFormCity2) || empty(customerFormPostalCode2) || stoi(customerFormPostalCode1) < 10000 ||  stoi(customerFormPostalCode2) < 10000) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }


    int customerID = ui->customerFormID->value();

    int editMode = false;


    if (!customerID) {
        clearCustomerInput();
        customerID = CustomerService::addCustomer(customerFormFirstName, customerFormLastName,
                                                  SADateTime(customerFormBirthDate->date().year(),
                                                             customerFormBirthDate->date().month(),
                                                             customerFormBirthDate->date().day()));
    } else {
        editMode = true;
        CustomerService::editCustomerByID(customerID, customerFormFirstName, customerFormLastName,
                                          SADateTime(customerFormBirthDate->date().year(),
                                                     customerFormBirthDate->date().month(),
                                                     customerFormBirthDate->date().day()));
    }
    CustomerService::addAddressToCustomerID(customerID, 1, customerFormAddressLine1, customerFormPostalCode1,
                                            customerFormCity1);
    CustomerService::addAddressToCustomerID(customerID, 2, customerFormAddressLine2, customerFormPostalCode2,
                                            customerFormCity2);


    if (!editMode) {
        auto customer = CustomerService::getCustomerByID(customerID);
        addCustomerToTable(customer);
        showPOPUpMessage(false, "Success !", "Adding the user with success !");
        return;
    }

    showPOPUpMessage(false, "Success !", "Editing the user with success !");


}

void MainWindow::staffTabButtonClicked() {


    string staffFormFirstName = ui->staffFormFirstName->text().toStdString();
    string staffFormLastName = ui->staffFormLastName->text().toStdString();
    QDateEdit *staffFormHireDate = ui->staffFormHireDate;
    string staffFormAddressLine = ui->staffFormAddressLine->text().toStdString();
    string staffFormCity = ui->staffFormCity->text().toStdString();
    string staffFormPostalCode = ui->staffFormPostalCode->text().toStdString();

    if (empty(staffFormFirstName) || empty(staffFormLastName) ||
        empty(staffFormHireDate->text().toStdString()) ||
        empty(staffFormAddressLine) || empty(staffFormCity) || empty(staffFormPostalCode) || stoi(staffFormPostalCode) < 10000) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }


    int staffID = ui->staffFormID->value();
    int editMode = false;

    if (!staffID) {
        clearStaffInput();
        staffID = StaffService::addStaff(staffFormFirstName, staffFormLastName,
                                         SADateTime(staffFormHireDate->date().year(),
                                                    staffFormHireDate->date().month(),
                                                    staffFormHireDate->date().day()),
                                         staffFormAddressLine,
                                         staffFormPostalCode, staffFormCity, 1);
    } else {
        editMode = true;
        StaffService::updateStaffByID(staffID, staffFormFirstName, staffFormLastName,
                                      SADateTime(staffFormHireDate->date().year(),
                                                 staffFormHireDate->date().month(),
                                                 staffFormHireDate->date().day()), 1);

        StaffService::updateStaffAddress(staffID, staffFormAddressLine, staffFormPostalCode, staffFormCity);
    }


    if (!editMode) {
        auto staff = StaffService::getStaffByID(staffID);
        addStaffToTable(staff);
        showPOPUpMessage(false, "Success !", "Adding the staff with success !");
        return;
    }

    showPOPUpMessage(false, "Success !", "Editing the staff with success !");


}


void MainWindow::addCustomerToTable(CustomerModel::Customer customer) {

    QTableWidget *tableWidget = ui->customerListTable;
    tableWidget->resizeColumnsToContents();


    tableWidget->insertRow(tableWidget->rowCount());


    auto btnOrder = new QPushButton("Do Order");
    auto btnEdit = new QPushButton("Edit");
    auto btnArchive = new QPushButton("Archive");
    int id = customer.id;

    int row = tableWidget->rowCount() - 1;
    connect(btnOrder, &QPushButton::clicked, [this, id, row] { customerTabOrderButtonOnTableClicked(id, row); });
    connect(btnEdit, &QPushButton::clicked, [this, id, row] { customerTabEditButtonOnTableClicked(id, row); });
    connect(btnArchive, &QPushButton::clicked,
            [this, id, row] { customerTabArchiveButtonOnTableClicked(id, row); });

    auto actionWidget = new QWidget();
    auto pLayout = new QHBoxLayout(actionWidget);
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
    string date = to_string(customer.birthDate.GetDay()) + "-" + to_string(customer.birthDate.GetMonth()) + "-" +
                  to_string(customer.birthDate.GetYear());
    tableWidget->setItem(row,
                         3,
                         new QTableWidgetItem(date.c_str()));

    auto address = CustomerService::getAllActiveAddressOfCustomerID(customer.id);


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

void MainWindow::addStaffToTable(StaffModel::Staff staff) {
    QTableWidget *tableWidget = ui->staffListTable;
    tableWidget->resizeColumnsToContents();
    tableWidget->insertRow(tableWidget->rowCount());
    auto btnOrder = new QPushButton("Do Order");
    auto btnEdit = new QPushButton("Edit");
    auto btnDelete = new QPushButton("Delete");
    int id = staff.id;
    int row = tableWidget->rowCount() - 1;
    connect(btnOrder, &QPushButton::clicked, [this, id, row] { staffTabOrderButtonOnTableClicked(id, row); });
    connect(btnEdit, &QPushButton::clicked, [this, id, row] { staffTabEditButtonOnTableClicked(id, row); });
    connect(btnDelete, &QPushButton::clicked,
            [this, id, row] { staffTabArchiveButtonOnTableClicked(id, row); });

    auto actionWidget = new QWidget();
    auto pLayout = new QHBoxLayout(actionWidget);
    pLayout->addWidget(btnOrder);
    pLayout->addWidget(btnEdit);
    pLayout->addWidget(btnDelete);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 10, 0);
    actionWidget->setLayout(pLayout);

    tableWidget->setCellWidget(row, 0, actionWidget);
    tableWidget->setItem(row,
                         1,
                         new QTableWidgetItem(staff.firstname.c_str()));
    tableWidget->setItem(row,
                         2,
                         new QTableWidgetItem(staff.lastname.c_str()));
    string date = to_string(staff.hireDate.GetDay()) + "-" + to_string(staff.hireDate.GetMonth()) + "-" +
                  to_string(staff.hireDate.GetYear());
    tableWidget->setItem(row,
                         3,
                         new QTableWidgetItem(date.c_str()));


    tableWidget->setItem(row,
                         4,
                         new QTableWidgetItem(staff.addressLine.c_str()));
    tableWidget->setItem(row,
                         5,
                         new QTableWidgetItem(staff.postalCode.c_str()));
    tableWidget->setItem(row,
                         6,
                         new QTableWidgetItem(staff.city.c_str()));


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


void MainWindow::clearCustomerInput() {

    ui->customerFormID->setValue(0);

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

void MainWindow::clearStaffInput() {

    ui->staffFormID->setValue(0);

    ui->staffFormFirstName->clear();
    ui->staffFormLastName->clear();
    ui->staffFormHireDate->clear();

    ui->staffFormAddressLine->clear();
    ui->staffFormCity->clear();
    ui->staffFormPostalCode->clear();

}