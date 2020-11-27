//
// Created by antoine on 27/11/2020.
//

#include "../model/ModelManager.h"
#include "CustomerTest.h"

CustomerTest::CustomerTest(){}

void CustomerTest::exec() {
    bool check[] = {1, 1};
    for (int i = 0; ((i < 5) && check[0] && check[1]); ++i) {
        init();
        check[0] = testAdd();
        check[1] = testUpdate();
        CustomerModel::archivedByID(testCustomer.id);
    }
    cout << "Add " << check[0] << endl;
    cout << "Update " << check[1] << endl;

}

void CustomerTest::init() {
    //generate random identity
    srand((unsigned)time(0));

    testCustomer.firstname ="test";
    testCustomer.lastname = "nom";
    testCustomer.birthDate = SADateTime((rand()%100)+1900, (rand()%12)+1, (rand()%28)+1);
}

bool CustomerTest::testAdd() {
    //add a generated customer and check if it get registered
    testCustomer.id = CustomerModel::insert(testCustomer.firstname, testCustomer.lastname, testCustomer.birthDate);
    returnedCustomer = CustomerModel::getCustomerByID(testCustomer.id);

    return testEquality();
}

bool CustomerTest::testUpdate(){
    //update a generated customer and check if it get registered
    init();
    CustomerModel::updateByID(testCustomer.id, testCustomer.firstname, testCustomer.lastname, testCustomer.birthDate);
    returnedCustomer = CustomerModel::getCustomerByID(testCustomer.id);

    return testEquality();
}
/*
bool CustomerTest::testArchive() {
    //check if customer gets archived
    CustomerModel::archivedByID(testCustomer.id);
    //empty the struct
    testCustomer.firstname = "";
    testCustomer.lastname = "";
    testCustomer.id = 0;
    //try to get it
    testCustomer = CustomerModel::getCustomerByID(testCustomer.id); //can't work
    //check if it's empty
    return testCustomer.firstname == "" &&
           testCustomer.lastname == "" &&
           testCustomer.id == 0;
}*/

bool CustomerTest::testEquality() {
    return testCustomer.firstname == returnedCustomer.firstname &&
           testCustomer.lastname == returnedCustomer.lastname &&
           testCustomer.birthDate-returnedCustomer.birthDate == 0 &&
           testCustomer.id == returnedCustomer.id;
}

