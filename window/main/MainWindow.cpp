#include "MainWindow.h"
#include "./ui_mainwindow.h"


struct MainWindow::OrderItemWidget orderItemWidget;
struct MainWindow::OrderPaymentWidget orderPaymentWidget;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::mainwindow) {
    ui->setupUi(this);

    initCustomerTab();
    initStaffTab();
    initItemTab();
    initOrderTab();
}

MainWindow::~MainWindow() {
    delete ui;
    delete _customerBtnBack;
    delete _staffBtnBack;
    delete _itemBtnBack;
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

    connect(_customerBtnBack, SIGNAL(clicked()), this, SLOT(customerTabCancelEdit()));
}

void MainWindow::customerTabCancelEdit() {
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

    connect(_staffBtnBack, SIGNAL(clicked()), this, SLOT(staffTabCancelEdit()));
}

void MainWindow::staffTabCancelEdit() {
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
    ui->itemFormName->setText(item.name.c_str());
    ui->itemFormResuplyThreshold->setValue(item.resuplyThreshold);
    ui->itemFormQuantity->setValue(item.quantity);
    ui->itemFormPriceHT->setValue(item.priceHt);
    ui->itemFormVAT->setValue(item.vat);

    connect(_itemBtnBack, SIGNAL(clicked()), this, SLOT(itemTabCancelEdit()));
}

void MainWindow::itemTabCancelEdit() {
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
        clearItemInput();
        itemREF = ItemService::addItem(itemFormREF, itemFormName, itemFormResuplyThreshold, itemFormQuantity,
                                       itemFormPriceHT, itemFormVAT);
    } else {
        ItemService::updateItemByREF(itemREF, itemFormName, itemFormResuplyThreshold, itemFormQuantity, itemFormPriceHT,
                                     itemFormVAT);
    }


    if (!editMode) {
        auto item = ItemService::getItemByREF(itemREF);
        addItemToTable(item);
        showPOPUpMessage(false, "Success !", "Adding the item with success !");
        return;
    }

    showPOPUpMessage(false, "Success !", "Editing the item with success !");


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
    tableWidget->setItem(row,
                         5,
                         new QTableWidgetItem(to_string(item.priceHt).c_str()));
    tableWidget->setItem(row,
                         6,
                         new QTableWidgetItem(to_string(item.vat).c_str()));


}

void MainWindow::clearItemInput() {
    ui->itemFormREFSave->clear();
    ui->itemFormREF->clear();
    ui->itemFormName->clear();
    ui->itemFormResuplyThreshold->clear();
    ui->itemFormQuantity->clear();
    ui->itemFormPriceHT->clear();
    ui->itemFormVAT->clear();

}


void MainWindow::orderTabButtonClicked() {

    QDateEdit *orderFormEstimatedDeliveryDate = ui->orderFormEstimatedDeliveryDate;
    int customerID = ui->orderFormCustomerID->value();
    int staffID = ui->orderFormStaffID->value();
    bool quantityError = false;
    string itemNameError = "";
    for (auto orderItemWidget : _orderItemWidgets) {
        string ref = orderItemWidget.itemSelect->itemData(
                orderItemWidget.itemSelect->currentIndex()).toString().toStdString();
        int quantity = orderItemWidget.quantity->value();
        double commercialDiscount = orderItemWidget.commercialDiscount->value();
        auto item = ItemService::getItemByREF(ref);
        if (item.quantity < quantity || quantity == 0) {
            quantityError = true;
            itemNameError = item.name;
        }
    }

    if (!customerID || !staffID) {
        showPOPUpMessage(true, "Error with fields !", "Please select Customer and Staff !");
        return;
    }

    if (empty(orderFormEstimatedDeliveryDate->text().toStdString())) {
        showPOPUpMessage(true, "Error with fields !", "Please fill in all fields !");
        return;
    }
    if (quantityError) {
        showPOPUpMessage(true, "Error with Item quantity !", "Please check quantity of item : " + itemNameError);
        return;
    }

    //OrderService::add
    string orderREF = OrderService::addOrder(SADateTime(orderFormEstimatedDeliveryDate->date().year(),
                                                        orderFormEstimatedDeliveryDate->date().month(),
                                                        orderFormEstimatedDeliveryDate->date().day()), customerID,
                                             staffID);
    for (auto orderItemWidget : _orderItemWidgets) {
        string ref = orderItemWidget.itemSelect->itemData(
                orderItemWidget.itemSelect->currentIndex()).toString().toStdString();
        int quantity = orderItemWidget.quantity->value();
        double commercialDiscount = orderItemWidget.commercialDiscount->value();
        OrderService::addItemToOrderREF(orderREF, ref, quantity, commercialDiscount);
    }

    for (auto orderPaymentWidget : _orderPaymentWidgets) {
        int type = orderPaymentWidget.paymentSelect->itemData(orderPaymentWidget.paymentSelect->currentIndex()).toInt();
        double amount = orderPaymentWidget.amount->value();
        OrderService::addPaymentToOrderREF(orderREF, type, amount);
    }

    auto order = OrderService::getOrderByREF(orderREF);
    addOrderToTable(order);
    showPOPUpMessage(false, "Success !", "Adding Order with success !");

}

void MainWindow::orderTabButtonResetOrderClicked() {
    clearOrderInput();
}

void MainWindow::orderTabEditButtonOnTableClicked(string orderREF, int row) {

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
    _orderItemWidgets.push_back(orderItemWidget);

    orderTabAddPaymentsToComboBox(ui->orderFormPaymentSelect);
    orderPaymentWidget.paymentSelect = ui->orderFormPaymentSelect;
    orderPaymentWidget.amount = ui->orderFormPaymentAmount;
    _orderPaymentWidgets.push_back(orderPaymentWidget);

    connect(ui->pushButtonAddOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonClicked()));
    connect(ui->pushButtonResetOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonResetOrderClicked()));

    connect(ui->pushButtonAddItemToOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonAddItemToOrderClicked()));
    connect(ui->pushButtonAddPaymentToOrder, SIGNAL(clicked()), this, SLOT(orderTabButtonAddPaymentToOrderClicked()));

}


void MainWindow::orderTabButtonAddPaymentToOrderClicked(int type, double amountVal) {
    if (_orderPaymentWidgets.size() >= 4) {
        showPOPUpMessage(true, "You have reached the limit", "You can add only 4 payments to an order !");
        return;
    }
    QHBoxLayout *mainLayout = new QHBoxLayout;
    auto layout1 = new QHBoxLayout;
    layout1->addWidget(new QLabel("Type"));
    auto paymentSelect = new QComboBox;
    orderTabAddPaymentsToComboBox(paymentSelect);
    int index = paymentSelect->findData(type);
    if (!type)
        index = 0;
    paymentSelect->setCurrentIndex(index);
    layout1->addWidget(paymentSelect);

    auto layout2 = new QHBoxLayout;
    layout2->addWidget(new QLabel("Amount"));
    auto amount = new QDoubleSpinBox;
    amount->setMaximum(999999);
    amount->setValue(amountVal);
    layout2->addWidget(amount);

    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);

    ui->orderPaymentsLayout->addLayout(mainLayout);
    ui->orderPaymentFormBox->setMinimumHeight(ui->orderPaymentFormBox->minimumHeight() + 28);

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
    QHBoxLayout *mainLayout = new QHBoxLayout;
    auto layout1 = new QHBoxLayout;
    layout1->addWidget(new QLabel("Item"));
    auto itemSelect = new QComboBox;
    orderTabAddItemsToComboBox(itemSelect);
    int index = itemSelect->findData(ref.c_str());
    if (empty(ref))
        index = 0;

    itemSelect->setCurrentIndex(index);
    layout1->addWidget(itemSelect);
    auto layout2 = new QHBoxLayout;
    layout2->addWidget(new QLabel("Quantity"));
    auto quantity = new QSpinBox;
    quantity->setValue(quantityVal);
    quantity->setMaximum(999999);
    layout2->addWidget(quantity);
    auto layout3 = new QHBoxLayout;
    layout3->addWidget(new QLabel("Commercial Discount"));
    auto commercialDiscount = new QDoubleSpinBox;
    commercialDiscount->setValue(commercialDiscountVal);
    commercialDiscount->setMaximum(1);
    layout3->addWidget(commercialDiscount);
    auto layout4 = new QHBoxLayout;
    layout4->addWidget(new QLabel("Price IT"));
    auto priceIT = new QDoubleSpinBox;
    priceIT->setValue(priceITVal);
    priceIT->setReadOnly(true);
    priceIT->setMaximum(999999);
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
        temp += ((1 + orderItem.vat) * (orderItem.price * orderItem.quantity));
        temp -= temp * orderItem.commercialDiscount;
        total += temp;
    }

    tableWidget->setItem(row, 4, new QTableWidgetItem(to_string(total).c_str()));

    double paid = OrderService::getPaymentAmountForOrderByREF(order.reference);

    total -= paid;

    tableWidget->setItem(row, 5, new QTableWidgetItem(to_string(total < 0 ? 0 : total).c_str()));


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

void MainWindow::orderTabCancelEdit() {

}

void MainWindow::clearOrderInput() {
    ui->orderFormCustomerID->setValue(0);
    ui->orderFormStaffID->setValue(0);
    ui->orderFormEstimatedDeliveryDate->clear();
    ui->orderFormTotalPriceCart->clear();
    ui->orderL1->setText("Please Select Customer from Customer Tab");
    ui->orderL3->setText("Please Select Staff from Staff Tab");
    ui->orderFormItemSelect->setCurrentIndex(0);
    ui->orderFormItemQuantity->setValue(0);
    ui->orderFormCormmercialDiscount->setValue(0);
    ui->orderFormPaymentSelect->setCurrentIndex(0);
    ui->orderFormPaymentAmount->setValue(0);
    int i = 0;
    auto beginI = _orderItemWidgets.begin();
    for (auto orderItemWidget : _orderItemWidgets) {
        if (i > 0) {
            delete orderItemWidget.layout;
            delete orderItemWidget.itemSelect;
            delete orderItemWidget.quantity;
            delete orderItemWidget.commercialDiscount;

            _orderItemWidgets.erase(beginI + i);

            ui->orderItemFormBox->setMinimumHeight(ui->orderItemFormBox->minimumHeight() - 28);
        }
        i++;
    }
    i = 0;
    auto beginP = _orderPaymentWidgets.begin();
    for (auto orderPaymentWidget : _orderPaymentWidgets) {
        if (i > 0) {
            delete orderPaymentWidget.layout;
            delete orderPaymentWidget.paymentSelect;
            delete orderPaymentWidget.amount;
            _orderPaymentWidgets.erase(beginP + i);

            ui->orderPaymentFormBox->setMinimumHeight(ui->orderPaymentFormBox->minimumHeight() - 28);
        }
        i++;
    }
}




