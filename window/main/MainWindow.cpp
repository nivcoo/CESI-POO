#include "MainWindow.h"
#include "./ui_mainwindow.h"


struct MainWindow::OrderItemWidget orderItemWidget;
struct MainWindow::OrderPaymentWidget orderPaymentWidget;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        _modelManager(new ModelManager()),

        ui(new Ui::mainwindow) {
    ui->setupUi(this);

    initCustomerTab();
    initStaffTab();
    initItemTab();
    initOrderTab();
    initStatTab();
}

MainWindow::~MainWindow() {
    delete _modelManager;
    delete ui;
    /**
    error code with this so maybe UI delete that before.

    delete _customerBtnBack;
    delete _staffBtnBack;
    delete _itemBtnBack;**/
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


void MainWindow::initCustomerTab() {
    clearCustomerInput();
    auto customers = CustomerService::getAllCustomers();
    for (auto customer : customers) {
        addCustomerToTable(customer);
    }
    connect(ui->pushButtonAddCustomer, SIGNAL(clicked()), this, SLOT(customerTabButtonClicked()));

}

void MainWindow::customerTabOrderButtonOnTableClicked(int customerID, const int i) {
    auto customer = CustomerService::getCustomerByID(customerID);
    ui->orderFormCustomerID->setValue(customerID);
    string text = "Customer - " + customer.firstname + " " + customer.lastname;
    ui->orderL1->setText(text.c_str());
    showPOPUpMessage(false, "Success !", "The customer was added to the order with success !");
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

    connect(_customerBtnBack, SIGNAL(clicked()), this, SLOT(customerTabCancelEditClicked()));
}

void MainWindow::customerTabCancelEditClicked() {
    delete _customerBtnBack;
    ui->titleCustomer->setText("Add Customer Form");
    ui->pushButtonAddCustomer->setText("Add Customer");
    clearCustomerInput();

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
        empty(customerFormAddressLine2) || empty(customerFormCity2) || empty(customerFormPostalCode2) ||
        stoi(customerFormPostalCode1) < 10000 || stoi(customerFormPostalCode2) < 10000) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }


    int customerID = ui->customerFormID->value();

    int editMode = customerID;


    if (!editMode) {
        clearCustomerInput();
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

    auto allAddress = CustomerService::getAllActiveAddressOfCustomerID(customerID);

    if (allAddress.size() < 2) {
        CustomerService::addAddressToCustomerID(customerID, 1, customerFormAddressLine1,
                                                customerFormPostalCode1,
                                                customerFormCity1);
        CustomerService::addAddressToCustomerID(customerID, 2, customerFormAddressLine2,
                                                customerFormPostalCode2,
                                                customerFormCity2);

    } else
        for (auto address : allAddress) {


            bool edited = false;
            if (address.type == 1) {
                edited = customerFormAddressLine1 != address.addressLine ||
                         customerFormPostalCode1 != address.postalCode ||
                         customerFormCity1 != address.city;
                if (edited)
                    CustomerService::addAddressToCustomerID(customerID, 1, customerFormAddressLine1,
                                                            customerFormPostalCode1,
                                                            customerFormCity1);
            } else if (address.type == 2) {
                edited = customerFormAddressLine2 != address.addressLine ||
                         customerFormPostalCode2 != address.postalCode ||
                         customerFormCity2 != address.city;
                if (edited)
                    CustomerService::addAddressToCustomerID(customerID, 2, customerFormAddressLine2,
                                                            customerFormPostalCode2,
                                                            customerFormCity2);
            }

        }


    if (!editMode) {
        auto customer = CustomerService::getCustomerByID(customerID);
        addCustomerToTable(customer);
        showPOPUpMessage(false, "Success !", "Adding the user with success !");
        return;
    }

    showPOPUpMessage(false, "Success !", "Editing the user with success !");


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


void MainWindow::initStaffTab() {
    clearStaffInput();

    auto staffs = StaffService::getAllStaffs();
    for (auto staff : staffs) {
        addStaffToTable(staff);
    }
    connect(ui->pushButtonAddStaff, SIGNAL(clicked()), this, SLOT(staffTabButtonClicked()));

}

void MainWindow::staffTabOrderButtonOnTableClicked(int staffID, const int i) {
    auto staff = StaffService::getStaffByID(staffID);
    ui->orderFormStaffID->setValue(staffID);
    string text = "Staff - " + staff.firstname + " " + staff.lastname;
    ui->orderL3->setText(text.c_str());
    showPOPUpMessage(false, "Success !", "The Staff was added to the order with success !");

}

void MainWindow::staffTabEditButtonOnTableClicked(int staffID, int row) {
    if (ui->staffFormID->value())
        return;
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

    connect(_staffBtnBack, SIGNAL(clicked()), this, SLOT(staffTabCancelEditClicked()));
}

void MainWindow::staffTabCancelEditClicked() {
    delete _staffBtnBack;
    ui->titleStaff->setText("Add Staff Form");
    ui->pushButtonAddStaff->setText("Add Staff");
    clearStaffInput();

}

void MainWindow::staffTabDeleteButtonOnTableClicked(int staffID, int row) {

    if (!staffID) {
        showPOPUpMessage(true, "Error line !", "The application can't access to the ID");
        return;
    }

    StaffService::deleteStaffByID(staffID);
    ui->staffListTable->removeRow(row);
    showPOPUpMessage(false, "Success !", "The staff was deleted");

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
        empty(staffFormAddressLine) || empty(staffFormCity) || empty(staffFormPostalCode) ||
        stoi(staffFormPostalCode) < 10000) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }


    int staffID = ui->staffFormID->value();
    int editMode = staffID;

    if (!editMode) {
        clearStaffInput();
        staffID = StaffService::addStaff(staffFormFirstName, staffFormLastName,
                                         SADateTime(staffFormHireDate->date().year(),
                                                    staffFormHireDate->date().month(),
                                                    staffFormHireDate->date().day()),
                                         staffFormAddressLine,
                                         staffFormPostalCode, staffFormCity, 1);
    } else {
        StaffService::updateStaffByID(staffID, staffFormFirstName, staffFormLastName,
                                      SADateTime(staffFormHireDate->date().year(),
                                                 staffFormHireDate->date().month(),
                                                 staffFormHireDate->date().day()), 1);
        auto staff = StaffService::getStaffByID(staffID);
        if (staff.addressLine != staffFormAddressLine || staff.postalCode != staffFormPostalCode ||
            staff.city != staffFormCity)
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
            [this, id, row] { staffTabDeleteButtonOnTableClicked(id, row); });

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

void MainWindow::clearStaffInput() {

    ui->staffFormID->setValue(0);

    ui->staffFormFirstName->clear();
    ui->staffFormLastName->clear();
    ui->staffFormHireDate->clear();

    ui->staffFormAddressLine->clear();
    ui->staffFormCity->clear();
    ui->staffFormPostalCode->clear();

}


void MainWindow::initItemTab() {
    clearItemInput();

    auto items = ItemService::getAllItems();
    for (auto item : items) {
        addItemToTable(item);
    }
    connect(ui->pushButtonAddItem, SIGNAL(clicked()), this, SLOT(itemTabButtonClicked()));

}

void MainWindow::itemTabEditButtonOnTableClicked(string itemREF, int row) {
    if (ui->itemFormREFSave->text() != "")
        return;
    ui->itemFormREFSave->setText(itemREF.c_str());
    _itemBtnBack = new QPushButton("Back To Add new Item");
    ui->itemFormTitleLayout->addWidget(_itemBtnBack);
    ui->titleItem->setText("Edit Item Form");
    ui->pushButtonAddItem->setText("Edit Item");

    auto item = ItemService::getItemByREF(itemREF);
    ui->itemFormREF->setText(item.reference.c_str());
    ui->itemFormREF->setReadOnly(true);
    ui->itemFormName->setText(item.name.c_str());
    ui->itemFormResuplyThreshold->setValue(item.resuplyThreshold);
    ui->itemFormQuantity->setValue(item.quantity);
    ui->itemFormPriceHT->setValue(item.priceHt);
    ui->itemFormVAT->setValue(item.vat);

    connect(_itemBtnBack, SIGNAL(clicked()), this, SLOT(itemTabCancelEditClicked()));
}

void MainWindow::itemTabCancelEditClicked() {
    delete _itemBtnBack;
    ui->titleItem->setText("Add Item Form");
    ui->pushButtonAddItem->setText("Add Item");
    clearItemInput();

}

void MainWindow::itemTabArchiveButtonOnTableClicked(string itemREF, int row) {

    if (itemREF == "") {
        showPOPUpMessage(true, "Error line !", "The application can't access to the ID");
        return;
    }

    ItemService::archiveItemByREF(itemREF);
    ui->itemListTable->removeRow(row);
    showPOPUpMessage(false, "Success !", "The item was archived");

}

void MainWindow::itemTabButtonClicked() {
    string itemFormREF = ui->itemFormREF->text().toStdString();
    string itemFormName = ui->itemFormName->text().toStdString();
    int itemFormResuplyThreshold = ui->itemFormResuplyThreshold->value();
    int itemFormQuantity = ui->itemFormQuantity->value();
    double itemFormPriceHT = ui->itemFormPriceHT->value();
    double itemFormVAT = ui->itemFormVAT->value();

    if (empty(itemFormREF) || empty(itemFormName) ||
        itemFormResuplyThreshold < 0 || itemFormQuantity < 0 || itemFormPriceHT < 0 || itemFormVAT < 0) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }

    string itemREF = ui->itemFormREFSave->text().toStdString();
    int editMode = itemREF != "";
    if (!editMode) {
        auto item = ItemService::getItemByREF(itemFormREF);
        if (item.reference != itemFormREF) {
            clearItemInput();
            itemREF = ItemService::addItem(itemFormREF, itemFormName, itemFormResuplyThreshold, itemFormQuantity,
                                           itemFormPriceHT, itemFormVAT);
            addItemToTable(ItemService::getItemByREF(itemREF));
            showPOPUpMessage(false, "Success !", "Adding the item with success !");
        } else
            showPOPUpMessage(true, "Error !", "This reference already exist !");


    } else {
        ItemService::updateItemByREF(itemREF, itemFormName, itemFormResuplyThreshold, itemFormQuantity, itemFormPriceHT,
                                     itemFormVAT);
        showPOPUpMessage(false, "Success !", "Editing the item with success !");
    }
}

void MainWindow::addItemToTable(ItemModel::Item item) {
    QTableWidget *tableWidget = ui->itemListTable;
    tableWidget->resizeColumnsToContents();
    tableWidget->insertRow(tableWidget->rowCount());
    auto btnEdit = new QPushButton("Edit");
    auto btnArchive = new QPushButton("Archive");
    string ref = item.reference;
    int row = tableWidget->rowCount() - 1;
    connect(btnEdit, &QPushButton::clicked, [this, ref, row] { itemTabEditButtonOnTableClicked(ref, row); });
    connect(btnArchive, &QPushButton::clicked,
            [this, ref, row] { itemTabArchiveButtonOnTableClicked(ref, row); });

    auto actionWidget = new QWidget();
    auto pLayout = new QHBoxLayout(actionWidget);
    pLayout->addWidget(btnEdit);
    pLayout->addWidget(btnArchive);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 10, 0);
    actionWidget->setLayout(pLayout);

    tableWidget->setCellWidget(row, 0, actionWidget);
    tableWidget->setItem(row,
                         1,
                         new QTableWidgetItem(item.reference.c_str()));
    tableWidget->setItem(row,
                         2,
                         new QTableWidgetItem(item.name.c_str()));
    tableWidget->setItem(row,
                         3,
                         new QTableWidgetItem(to_string(item.resuplyThreshold).c_str()));


    tableWidget->setItem(row,
                         4,
                         new QTableWidgetItem(to_string(item.quantity).c_str()));

    stringstream tmp;
    tmp << setprecision(2) << fixed << item.priceHt;

    tableWidget->setItem(row,
                         5,
                         new QTableWidgetItem(tmp.str().c_str()));
    tmp.str(string());
    tmp << setprecision(2) << fixed << item.vat;
    tableWidget->setItem(row,
                         6,
                         new QTableWidgetItem(tmp.str().c_str()));
    tmp.str(string());


}

void MainWindow::clearItemInput() {
    ui->itemFormREFSave->clear();
    ui->itemFormREF->clear();
    ui->itemFormREF->setReadOnly(false);
    ui->itemFormName->clear();
    ui->itemFormResuplyThreshold->clear();
    ui->itemFormQuantity->clear();
    ui->itemFormPriceHT->clear();
    ui->itemFormVAT->clear();


}

bool MainWindow::orderCheckItemQuantityError() {

    bool quantityError = false;
    string itemNameError = "";
    int realQuantity = 0;
    for (auto orderItemWidget : _orderItemWidgets) {
        string ref = orderItemWidget.itemSelect->itemData(
                orderItemWidget.itemSelect->currentIndex()).toString().toStdString();
        int quantity = orderItemWidget.quantity->value();
        double commercialDiscount = orderItemWidget.commercialDiscount->value();
        auto item = ItemService::getItemByREF(ref);
        if (item.quantity < quantity) {
            quantityError = true;
            realQuantity = item.quantity;
            itemNameError = item.name;
        }
    }

    if (quantityError) {
        showPOPUpMessage(true, "Error with Item quantity !",
                         "Please check quantity of item : " + itemNameError + ", you can only add " +
                         to_string(realQuantity) + " items");
    }

    return quantityError;
}

void MainWindow::orderTabButtonClicked() {

    string orderREFEdit = ui->orderFormREF->text().toStdString();

    bool editMode = !empty(orderREFEdit);

    QDateEdit *orderFormEstimatedDeliveryDate = ui->orderFormEstimatedDeliveryDate;
    int customerID = ui->orderFormCustomerID->value();
    int staffID = ui->orderFormStaffID->value();
    bool quantityError = false;
    string itemNameError = "";
    int realQuantity = 0;

    if (!customerID || !staffID) {
        showPOPUpMessage(true, "Error with fields !", "Please select Customer and Staff !");
        return;
    }

    if (empty(orderFormEstimatedDeliveryDate->text().toStdString())) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }
    if (!editMode && orderCheckItemQuantityError())
        return;

    SADateTime orderFormEstimatedDeliveryDateTime = SADateTime(orderFormEstimatedDeliveryDate->date().year(),
                                                               orderFormEstimatedDeliveryDate->date().month(),
                                                               orderFormEstimatedDeliveryDate->date().day());

    if (!editMode) {
        //OrderService::add
        string orderREF = OrderService::addOrder(orderFormEstimatedDeliveryDateTime, customerID,
                                                 staffID);
        auto items = OrderService::getAllOrderItemByOrderREF(orderREF);
        for (auto orderItemWidget : _orderItemWidgets) {


            string ref = orderItemWidget.itemSelect->itemData(
                    orderItemWidget.itemSelect->currentIndex()).toString().toStdString();
            bool exist = false;
            for (auto item : items) {
                if (item.referenceItem == ref)
                    exist = true;
            }
            int quantity = orderItemWidget.quantity->value();
            double commercialDiscount = orderItemWidget.commercialDiscount->value();
            if (quantity > 0 && !exist)
                OrderService::addItemToOrderREF(orderREF, ref, quantity, commercialDiscount);
        }

        for (auto orderPaymentWidget : _orderPaymentWidgets) {
            int type = orderPaymentWidget.paymentSelect->itemData(
                    orderPaymentWidget.paymentSelect->currentIndex()).toInt();
            double amount = orderPaymentWidget.amount->value();
            if (amount > 0)
                OrderService::addPaymentToOrderREF(orderREF, type, amount);
        }

        auto order = OrderService::getOrderByREF(orderREF);
        addOrderToTable(order);
        showPOPUpMessage(false, "Success !", "Adding Order with success !");

        clearOrderInput();
    } else {
        OrderService::editEstimatedDeliveryDateByOrderREF(orderREFEdit, orderFormEstimatedDeliveryDateTime);
        auto items = OrderService::getAllOrderItemByOrderREF(orderREFEdit);
        auto payments = OrderService::getAllPaymentByOrderREF(orderREFEdit);


        for (auto orderItemWidget : _orderItemWidgets) {
            string ref = orderItemWidget.itemSelect->itemData(
                    orderItemWidget.itemSelect->currentIndex()).toString().toStdString();
            int quantity = orderItemWidget.quantity->value();
            double commercialDiscount = orderItemWidget.commercialDiscount->value();
            bool exist = false;
            for (auto item : items) {
                if (item.referenceItem == ref)
                    exist = true;
            }

            if (quantity > 0 && !exist) {
                OrderService::addItemToOrderREF(orderREFEdit, ref, quantity, commercialDiscount);
            } else if (quantity == 0 && exist) {
                OrderService::deleteItemFromOrderByREF(orderREFEdit, ref);
            } else if (quantity >= 0 && exist) {
                OrderService::editCommercialDiscountFromOrderByREF(orderREFEdit, ref, commercialDiscount);
            }
        }


        for (auto orderPaymentWidget : _orderPaymentWidgets) {
            int id = orderPaymentWidget.id->value();
            int type = orderPaymentWidget.paymentSelect->itemData(
                    orderPaymentWidget.paymentSelect->currentIndex()).toInt();
            double amount = orderPaymentWidget.amount->value();

            bool exist = false;
            for (auto payment : payments) {
                if (payment.id == id)
                    exist = true;
            }

            if (amount > 0 && !exist)
                OrderService::addPaymentToOrderREF(orderREFEdit, type, amount);
            else if (amount == 0 && exist) {
                OrderService::deletePaymentFromOrderByID(id);
            } else if (amount >= 0 && exist) {
                OrderService::editPaymentAmountByID(id, amount);
            }
        }

        showPOPUpMessage(false, "Success !", "Editing Order with success !");

    }

}

void MainWindow::orderTabButtonResetOrderClicked() {
    clearOrderInput();
}

void MainWindow::orderTabButtonCalculOrderClicked() {

    string orderREFEdit = ui->orderFormREF->text().toStdString();

    bool editMode = !empty(orderREFEdit);
    double total = 0;
    if (!editMode)
        orderCheckItemQuantityError();
    for (auto orderItemWidget : _orderItemWidgets) {

        auto item = ItemService::getItemByREF(orderItemWidget.itemSelect->itemData(
                orderItemWidget.itemSelect->currentIndex()).toString().toStdString());

        int quantity = orderItemWidget.quantity->value();
        double commercialDiscount = orderItemWidget.commercialDiscount->value();
        double priceIT = ((1 + item.vat) * (item.priceHt * quantity));


        priceIT -= priceIT * commercialDiscount;
        orderItemWidget.priceIT->setValue(priceIT);
        total += priceIT;

    }

    ui->orderFormTotalPriceCart->setValue(total);

    double totalPayment = 0;


    for (auto orderPaymentWidget : _orderPaymentWidgets) {
        totalPayment += orderPaymentWidget.amount->value();
    }

    double leftToPay = total - totalPayment;
    ui->orderFormTotalLeftToPay->setValue((leftToPay < 0) ? 0 : leftToPay);


}

void MainWindow::orderTabEditButtonOnTableClicked(string orderREF, int row) {
    if (ui->orderFormREF->text() != "")
        return;

    clearOrderInput();

    ui->orderFormREF->setText(orderREF.c_str());

    ui->titleOrder->setText("Edit Order Form");
    ui->pushButtonAddOrder->setText("Edit Order");
    ui->titlePaymentOrder->setText("Edit Payments to order");
    ui->titleItemOrder->setText("Edit Items to order");

    auto order = OrderService::getOrderByREF(orderREF);
    auto items = OrderService::getAllOrderItemByOrderREF(orderREF);
    int i = 0;
    double total = 0;
    for (auto item: items) {

        double priceIT = ((1 + item.vat) * (item.price * item.quantity));
        priceIT -= priceIT * item.commercialDiscount;
        total += priceIT;
        if (i == 0) {
            int index = ui->orderFormItemSelect->findData(item.referenceItem.c_str());
            ui->orderFormItemSelect->setCurrentIndex(index);
            ui->orderFormItemSelect->setEnabled(false);
            ui->orderFormItemQuantity->setValue(item.quantity);
            ui->orderFormCormmercialDiscount->setValue(item.commercialDiscount);
            //ui->orderFormCormmercialDiscount->setReadOnly(true);
            ui->orderFormTotalPrice->setValue(priceIT);
            ui->orderFormTotalPrice->setReadOnly(true);
        } else {
            orderTabButtonAddItemToOrderClicked(item.referenceItem, item.quantity, item.commercialDiscount, priceIT);
        }
        i++;

    }
    ui->orderFormTotalPriceCart->setValue(total);
    auto payments = OrderService::getAllPaymentByOrderREF(orderREF);

    i = 0;
    double totalPayment = 0;
    for (auto payment: payments) {
        double amount = payment.amount;
        if (i == 0) {
            ui->orderFormPaymentID->setValue(payment.id);

            int index = ui->orderFormPaymentSelect->findData(payment.paymentMethod);
            ui->orderFormPaymentSelect->setCurrentIndex(index);
            ui->orderFormPaymentSelect->setEnabled(false);
            ui->orderFormPaymentAmount->setValue(amount);


        } else {
            orderTabButtonAddPaymentToOrderClicked(payment.id, payment.paymentMethod, amount);
        }

        totalPayment += amount;
        i++;

    }

    double leftToPay = total - totalPayment;
    ui->orderFormTotalLeftToPay->setValue((leftToPay < 0) ? 0 : leftToPay);
    ui->orderFormCustomerID->setValue(order.customerID);
    ui->orderFormStaffID->setValue(order.staffID);

    auto customer = CustomerService::getCustomerByID(order.customerID);
    string textCustomer = "Customer - " + customer.firstname + " " + customer.lastname;

    auto staff = StaffService::getStaffByID(order.staffID);
    string textStaff = "Staff - " + staff.firstname + " " + staff.lastname;


    ui->orderL1->setText(textCustomer.c_str());
    ui->orderL3->setText(textStaff.c_str());
    QDate date;
    date.setDate(order.estimatedDeliveryDate.GetYear(), order.estimatedDeliveryDate.GetMonth(),
                 order.estimatedDeliveryDate.GetDay());
    ui->orderFormEstimatedDeliveryDate->setDate(date);
}

void MainWindow::orderTabDeleteButtonOnTableClicked(string orderREF, int row) {

    if (orderREF == "") {
        showPOPUpMessage(true, "Error line !", "The application can't access to the ID");
        return;
    }
    OrderService::deleteOrderByREF(orderREF);
    ui->orderListTable->removeRow(row);
    showPOPUpMessage(false, "Success !", "The order was archived");

}

void MainWindow::initOrderTab() {
    clearCustomerInput();
    auto orders = OrderService::getAllOrders();
    for (auto order : orders) {
        addOrderToTable(order);
    }

    orderTabAddItemsToComboBox(ui->orderFormItemSelect);
    orderItemWidget.itemSelect = ui->orderFormItemSelect;
    orderItemWidget.quantity = ui->orderFormItemQuantity;
    orderItemWidget.commercialDiscount = ui->orderFormCormmercialDiscount;
    orderItemWidget.priceIT = ui->orderFormTotalPrice;
    _orderItemWidgets.push_back(orderItemWidget);

    orderTabAddPaymentsToComboBox(ui->orderFormPaymentSelect);
    orderPaymentWidget.id = ui->orderFormPaymentID;
    orderPaymentWidget.paymentSelect = ui->orderFormPaymentSelect;
    orderPaymentWidget.amount = ui->orderFormPaymentAmount;
    _orderPaymentWidgets.push_back(orderPaymentWidget);

    connect(ui->pushButtonAddOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonClicked()));
    connect(ui->pushButtonResetOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonResetOrderClicked()));

    connect(ui->pushButtonAddItemToOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonAddItemToOrderClicked()));
    connect(ui->pushButtonAddPaymentToOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonAddPaymentToOrderClicked()));
    connect(ui->pushButtonCalculOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonCalculOrderClicked()));

}


void MainWindow::orderTabButtonAddPaymentToOrderClicked(int idVal, int type, double amountVal) {
    if (_orderPaymentWidgets.size() >= 4) {
        showPOPUpMessage(true, "You have reached the limit", "You can add only 4 payments to an order !");
        return;
    }
    QHBoxLayout *mainLayout = new QHBoxLayout;

    bool editMode = idVal != 0;
    auto id = new QHBoxLayout;
    auto spinID = new QSpinBox;
    spinID->setValue(idVal);
    spinID->setMaximumWidth(0);
    spinID->setStyleSheet("width:0px;height:0px;border:none;padding:0px;");
    id->addWidget(spinID);
    auto layout1 = new QHBoxLayout;
    layout1->addWidget(new QLabel("Type"));
    auto paymentSelect = new QComboBox;
    orderTabAddPaymentsToComboBox(paymentSelect);
    int index = paymentSelect->findData(type);
    if (!type)
        index = 0;
    paymentSelect->setCurrentIndex(index);
    if (editMode)
        paymentSelect->setEnabled(false);
    layout1->addWidget(paymentSelect);

    auto layout2 = new QHBoxLayout;
    layout2->addWidget(new QLabel("Amount"));
    auto amount = new QDoubleSpinBox;
    amount->setMaximum(999999);
    amount->setValue(amountVal);
    layout2->addWidget(amount);
    mainLayout->addLayout(id);
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    ui->orderPaymentsLayout->addLayout(mainLayout);
    ui->orderPaymentFormBox->setMinimumHeight(ui->orderPaymentFormBox->minimumHeight() + 28);
    orderPaymentWidget.id = spinID;
    orderPaymentWidget.paymentSelect = paymentSelect;
    orderPaymentWidget.amount = amount;
    orderPaymentWidget.layout = mainLayout;
    _orderPaymentWidgets.push_back(orderPaymentWidget);

}

void MainWindow::orderTabButtonAddItemToOrderClicked(string ref, int quantityVal, double commercialDiscountVal,
                                                     double priceITVal) {

    if (_orderItemWidgets.size() >= 10) {
        showPOPUpMessage(true, "You have reached the limit", "You can add only 10 items to an order !");
        return;
    }

    bool editMode = !empty(ref);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    auto layout1 = new QHBoxLayout;
    layout1->addWidget(new QLabel("Item"));
    auto itemSelect = new QComboBox;
    if (editMode)
        itemSelect->setEnabled(false);
    orderTabAddItemsToComboBox(itemSelect);
    int index = itemSelect->findData(ref.c_str());
    if (!editMode)
        index = 0;

    itemSelect->setCurrentIndex(index);
    layout1->addWidget(itemSelect);
    auto layout2 = new QHBoxLayout;
    layout2->addWidget(new QLabel("Quantity"));
    auto quantity = new QSpinBox;
    quantity->setMaximum(999999);
    quantity->setValue(quantityVal);
    layout2->addWidget(quantity);
    auto layout3 = new QHBoxLayout;
    layout3->addWidget(new QLabel("Commercial Discount"));
    auto commercialDiscount = new QDoubleSpinBox;
    commercialDiscount->setMaximum(1);
    commercialDiscount->setValue(commercialDiscountVal);
    if (editMode)
        commercialDiscount->setReadOnly(true);
    layout3->addWidget(commercialDiscount);
    auto layout4 = new QHBoxLayout;
    layout4->addWidget(new QLabel("Price IT"));
    auto priceIT = new QDoubleSpinBox;
    priceIT->setReadOnly(true);
    priceIT->setMaximum(999999);
    priceIT->setValue(priceITVal);
    layout4->addWidget(priceIT);
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addLayout(layout3);
    mainLayout->addLayout(layout4);
    ui->orderItemsLayout->addLayout(mainLayout);
    ui->orderItemFormBox->setMinimumHeight(ui->orderItemFormBox->minimumHeight() + 28);
    orderItemWidget.itemSelect = itemSelect;
    orderItemWidget.quantity = quantity;
    orderItemWidget.commercialDiscount = commercialDiscount;
    orderItemWidget.layout = mainLayout;
    orderItemWidget.priceIT = priceIT;
    _orderItemWidgets.push_back(orderItemWidget);
}

void MainWindow::orderTabAddItemsToComboBox(QComboBox *itemSelect) {
    int index = 0;
    for (auto item : ItemService::getAllItems()) {
        itemSelect->addItem((item.name + " | " + to_string(item.priceHt) + "€").c_str());
        itemSelect->setItemData(index, item.reference.c_str());
        index++;
    }
}


void MainWindow::orderTabAddPaymentsToComboBox(QComboBox *itemSelect) {

    itemSelect->addItem("Bank Card");
    itemSelect->setItemData(0, 0);

    itemSelect->addItem("Coin");
    itemSelect->setItemData(1, 1);

}


void MainWindow::addOrderToTable(OrderHistoryModel::Order order) {
    QTableWidget *tableWidget = ui->orderListTable;
    tableWidget->resizeColumnsToContents();
    tableWidget->insertRow(tableWidget->rowCount());
    auto btnEdit = new QPushButton("Edit");
    auto btnDelete = new QPushButton("Delete");
    string ref = order.reference;
    int row = tableWidget->rowCount() - 1;
    connect(btnEdit, &QPushButton::clicked, [this, ref, row] { orderTabEditButtonOnTableClicked(ref, row); });
    connect(btnDelete, &QPushButton::clicked,
            [this, ref, row] { orderTabDeleteButtonOnTableClicked(ref, row); });

    auto actionWidget = new QWidget();
    auto pLayout = new QHBoxLayout(actionWidget);
    pLayout->addWidget(btnEdit);
    pLayout->addWidget(btnDelete);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 10, 0);
    actionWidget->setLayout(pLayout);

    tableWidget->setCellWidget(row, 0, actionWidget);
    tableWidget->setItem(row, 1, new QTableWidgetItem(order.reference.c_str()));

    auto customer = CustomerService::getCustomerByID(order.customerID);

    tableWidget->setItem(row, 2, new QTableWidgetItem(customer.firstname.c_str()));
    tableWidget->setItem(row, 3, new QTableWidgetItem(customer.lastname.c_str()));

    auto orderItems = OrderService::getAllOrderItemByOrderREF(ref);

    double total = 0;

    double temp = 0;

    for (auto orderItem :orderItems) {
        temp = ((1 + orderItem.vat) * (orderItem.price * orderItem.quantity));
        temp -= temp * orderItem.commercialDiscount;
        total += temp;
    }

    stringstream tmp;
    tmp << setprecision(2) << fixed << total;
    tableWidget->setItem(row, 4, new QTableWidgetItem(tmp.str().c_str()));
    tmp.str(string());

    double paid = OrderService::getPaymentAmountForOrderByREF(order.reference);

    total -= paid;
    tmp << setprecision(2) << fixed << (total < 0 ? 0 : total);
    tableWidget->setItem(row, 5, new QTableWidgetItem(tmp.str().c_str()));
    tmp.str(string());

    string date =
            to_string(order.estimatedDeliveryDate.GetDay()) + "-" +
            to_string(order.estimatedDeliveryDate.GetMonth()) +
            "-" +
            to_string(order.estimatedDeliveryDate.GetYear());
    tableWidget->setItem(row, 6, new QTableWidgetItem(date.c_str()));
    date = to_string(order.createdAt.GetDay()) + "-" + to_string(order.createdAt.GetMonth()) + "-" +
           to_string(order.createdAt.GetYear());
    tableWidget->setItem(row, 7, new QTableWidgetItem(date.c_str()));


}

void MainWindow::clearOrderInput() {
    ui->orderFormCustomerID->setValue(0);
    ui->orderFormStaffID->setValue(0);
    ui->orderFormREF->clear();
    ui->orderFormEstimatedDeliveryDate->clear();
    ui->orderFormTotalPriceCart->clear();
    ui->orderL1->setText("Please Select Customer from Customer Tab");
    ui->orderL3->setText("Please Select Staff from Staff Tab");


    ui->titleOrder->setText("Add Order Form");
    ui->pushButtonAddOrder->setText("Add Order");
    ui->titlePaymentOrder->setText("Add Payment to order");
    ui->titleItemOrder->setText("Add Item to order");
    ui->orderFormItemSelect->clear();
    ui->orderFormItemSelect->setEnabled(true);

    ui->orderFormItemQuantity->setValue(0);
    ui->orderFormItemQuantity->setReadOnly(false);
    ui->orderFormTotalPrice->setValue(0);
    ui->orderFormTotalPrice->setReadOnly(false);
    ui->orderFormCormmercialDiscount->setValue(0);
    ui->orderFormCormmercialDiscount->setReadOnly(false);

    ui->orderFormPaymentSelect->clear();
    ui->orderFormPaymentSelect->setEnabled(true);
    ui->orderFormPaymentAmount->setValue(0);
    ui->orderFormPaymentAmount->setReadOnly(false);
    ui->orderFormPaymentID->setValue(0);
    ui->orderFormPaymentID->setReadOnly(false);

    int i = 0;
    auto beginI = _orderItemWidgets.begin();
    for (auto orderItemWidget : _orderItemWidgets) {
        if (i > 0) {
            delete orderItemWidget.layout;
            delete orderItemWidget.itemSelect;
            delete orderItemWidget.quantity;
            delete orderItemWidget.commercialDiscount;
            delete orderItemWidget.priceIT;
            ui->orderItemFormBox->setMinimumHeight(ui->orderItemFormBox->minimumHeight() - 28);
        }
        i++;
    }
    i = 0;
    auto beginP = _orderPaymentWidgets.begin();
    for (auto orderPaymentWidget : _orderPaymentWidgets) {
        if (i > 0) {
            delete orderPaymentWidget.id;
            delete orderPaymentWidget.layout;
            delete orderPaymentWidget.paymentSelect;
            delete orderPaymentWidget.amount;
            ui->orderPaymentFormBox->setMinimumHeight(ui->orderPaymentFormBox->minimumHeight() - 28);
        }
        i++;
    }

    _orderItemWidgets.clear();
    _orderPaymentWidgets.clear();
    orderTabAddItemsToComboBox(ui->orderFormItemSelect);
    orderItemWidget.itemSelect = ui->orderFormItemSelect;
    orderItemWidget.quantity = ui->orderFormItemQuantity;
    orderItemWidget.commercialDiscount = ui->orderFormCormmercialDiscount;
    orderItemWidget.priceIT = ui->orderFormTotalPrice;
    _orderItemWidgets.push_back(orderItemWidget);
    orderTabAddPaymentsToComboBox(ui->orderFormPaymentSelect);
    orderPaymentWidget.id = ui->orderFormPaymentID;
    orderPaymentWidget.paymentSelect = ui->orderFormPaymentSelect;
    orderPaymentWidget.amount = ui->orderFormPaymentAmount;
    _orderPaymentWidgets.push_back(orderPaymentWidget);
}

void MainWindow::initStatTab() {
    statInitSelectValue();
    auto customers = CustomerService::getAllCustomers();
    int index = 0;
    for (auto customer : customers) {
        ui->statFormCustomerSelect->addItem((customer.firstname + " " + customer.lastname).c_str());
        ui->statFormCustomerSelect->setItemData(index, customer.id);
        index++;
    }
    auto itemsLowStock = StatsService::getLowStockItems();
    for (auto item : itemsLowStock) {
        statAddItemToTable(item, ui->statFormTableLowStock);
    }
    auto itemsBestSelled = StatsService::getItemsBestSold();
    for (auto orderItem : itemsBestSelled) {
        auto item = ItemService::getItemByREF(orderItem.referenceItem);
        statAddItemToTable(item, ui->statFormTableBestSelled);
    }
    auto itemsLeastSelled = StatsService::getItemsLeastSold();
    for (auto orderItem : itemsLeastSelled) {
        auto item = ItemService::getItemByREF(orderItem.referenceItem);
        statAddItemToTable(item, ui->statFormTableLeastSelled);
    }

    connect(ui->statPushButtonAverageCart, SIGNAL(clicked()), this, SLOT(statTabButtonAverageCartClicked()));

    connect(ui->statPushButtonMonthlyEarning, SIGNAL(clicked()), this, SLOT(statTabButtonMonthlyEarningClicked()));
    connect(ui->statPushButtonCustomerTotalPurschases, SIGNAL(clicked()), this,
            SLOT(statTabButtonCustomerTotalPurschasesClicked()));
    connect(ui->statPushButtonCommercialValue, SIGNAL(clicked()), this, SLOT(statTabButtonCommercialValueClicked()));
    connect(ui->statPushButtonPurchaseValue, SIGNAL(clicked()), this, SLOT(statTabButtonPurchaseValueClicked()));
    connect(ui->statPushButtonSimulateVariation, SIGNAL(clicked()), this,
            SLOT(statTabButtonSimulateVariationClicked()));
}

void MainWindow::statTabButtonAverageCartClicked() {
    ui->statFormAverageCart->setValue(StatsService::getAverageCartValue());
    showPOPUpMessage(false, "Success !", "The value has been calculated successfully!");
}

void MainWindow::statTabButtonMonthlyEarningClicked() {

    int month = ui->statFormMonthlyEarningSelect->currentIndex() + 1;
    ui->statFormMonthlyEarning->setValue(
            StatsService::getMonthlyEarning(SADateTime(SADateTime::currentDateTime().GetYear(), month, 0)));
    showPOPUpMessage(false, "Success !", "The value has been calculated successfully!");
}

void MainWindow::statTabButtonCustomerTotalPurschasesClicked() {
    int customerID = ui->statFormCustomerSelect->itemData(ui->statFormCustomerSelect->currentIndex()).toInt();
    ui->statFormCustomerValue->setValue(StatsService::getTotalPurchasesOfCustomerByID(customerID));
    showPOPUpMessage(false, "Success !", "The value has been calculated successfully!");
}

void MainWindow::statTabButtonCommercialValueClicked() {
    ui->statFormCommercialValue->setValue(StatsService::getValueStock(true));
    showPOPUpMessage(false, "Success !", "The value has been calculated successfully!");
}

void MainWindow::statTabButtonPurchaseValueClicked() {
    ui->statFormPurschaseValue->setValue(StatsService::getValueStock());
    showPOPUpMessage(false, "Success !", "The value has been calculated successfully!");
}

void MainWindow::statTabButtonSimulateVariationClicked() {

    double vat = ui->statFormSimulateTVASelect->itemData(ui->statFormSimulateTVASelect->currentIndex()).toDouble();
    double commercialMargin = ui->statFormSimulateCommercialM->itemData(
            ui->statFormSimulateCommercialM->currentIndex()).toDouble();
    double commercialDiscount = ui->statFormSimulateCommercialD->itemData(
            ui->statFormSimulateCommercialD->currentIndex()).toDouble();
    double unknownMargin = ui->statFormSimulateOtherM->itemData(ui->statFormSimulateOtherM->currentIndex()).toDouble();
    ui->statFormSimulateValue->setValue(
            StatsService::getValueStock(false, vat * commercialMargin * commercialDiscount * unknownMargin));
    showPOPUpMessage(false, "Success !", "The value has been calculated successfully!");
}

void MainWindow::statInitSelectValue() {

    ui->statFormMonthlyEarningSelect->addItem("January");
    ui->statFormMonthlyEarningSelect->addItem("February");
    ui->statFormMonthlyEarningSelect->addItem("March");
    ui->statFormMonthlyEarningSelect->addItem("April");
    ui->statFormMonthlyEarningSelect->addItem("May");
    ui->statFormMonthlyEarningSelect->addItem("June");
    ui->statFormMonthlyEarningSelect->addItem("July");
    ui->statFormMonthlyEarningSelect->addItem("August");
    ui->statFormMonthlyEarningSelect->addItem("September");
    ui->statFormMonthlyEarningSelect->addItem("October");
    ui->statFormMonthlyEarningSelect->addItem("November");
    ui->statFormMonthlyEarningSelect->addItem("December");


    double value = 1;
    ui->statFormSimulateTVASelect->addItem("No Vat");
    ui->statFormSimulateTVASelect->setItemData(0, value);
    value = 1.05;
    ui->statFormSimulateTVASelect->addItem("VAT 1 (5%)");
    ui->statFormSimulateTVASelect->setItemData(1, value);
    value = 1.10;
    ui->statFormSimulateTVASelect->addItem("VAT 2 (10%)");
    ui->statFormSimulateTVASelect->setItemData(2, value);
    value = 1.20;
    ui->statFormSimulateTVASelect->addItem("VAT 3 (20%)");
    ui->statFormSimulateTVASelect->setItemData(3, value);

    value = 1;
    ui->statFormSimulateCommercialM->addItem("No Commercial Margin");
    ui->statFormSimulateCommercialM->setItemData(0, value);
    value = 1.05;
    ui->statFormSimulateCommercialM->addItem("Commercial Margin (5%)");
    ui->statFormSimulateCommercialM->setItemData(1, value);
    value = 1.10;
    ui->statFormSimulateCommercialM->addItem("Commercial Margin (10%)");
    ui->statFormSimulateCommercialM->setItemData(2, value);
    value = 1.20;
    ui->statFormSimulateCommercialM->addItem("Commercial Margin (15%)");
    ui->statFormSimulateCommercialM->setItemData(3, value);

    value = 1;
    ui->statFormSimulateCommercialD->addItem("No Commercial Discount");
    ui->statFormSimulateCommercialD->setItemData(0, value);
    value = 0.95;
    ui->statFormSimulateCommercialD->addItem("Commercial Discount (5%)");
    ui->statFormSimulateCommercialD->setItemData(1, value);
    value = 0.96;
    ui->statFormSimulateCommercialD->addItem("Commercial Discount (6%)");
    ui->statFormSimulateCommercialD->setItemData(2, value);

    value = 1;
    ui->statFormSimulateOtherM->addItem("No Other Discount");
    ui->statFormSimulateOtherM->setItemData(0, value);
    value = 0.98;
    ui->statFormSimulateOtherM->addItem("Other Discount (2%)");
    ui->statFormSimulateOtherM->setItemData(1, value);
    value = 0.97;
    ui->statFormSimulateOtherM->addItem("Other Discount (3%)");
    ui->statFormSimulateOtherM->setItemData(2, value);
    value = 0.95;
    ui->statFormSimulateOtherM->addItem("Other Discount (5%)");
    ui->statFormSimulateOtherM->setItemData(3, value);


}


void MainWindow::statAddItemToTable(ItemModel::Item item, QTableWidget *tableWidget) {
    tableWidget->resizeColumnsToContents();
    tableWidget->insertRow(tableWidget->rowCount());
    int row = tableWidget->rowCount() - 1;
    tableWidget->setItem(row,
                         0,
                         new QTableWidgetItem(item.reference.c_str()));
    tableWidget->setItem(row,
                         1,
                         new QTableWidgetItem(item.name.c_str()));
    tableWidget->setItem(row,
                         2,
                         new QTableWidgetItem(to_string(item.resuplyThreshold).c_str()));


    tableWidget->setItem(row,
                         3,
                         new QTableWidgetItem(to_string(item.quantity).c_str()));


    stringstream tmp;
    tmp << setprecision(2) << fixed << item.priceHt;


    tableWidget->setItem(row,
                         4,
                         new QTableWidgetItem(tmp.str().c_str()));
    tmp.str(string());
    tmp << setprecision(2) << fixed << item.vat;
    tableWidget->setItem(row,
                         5,
                         new QTableWidgetItem(tmp.str().c_str()));
    tmp.str(string());


}




