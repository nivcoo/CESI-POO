//
// Created by antoine on 27/11/2020.
//

#ifndef CESI_POO_CUSTOMERTEST_H
#define CESI_POO_CUSTOMERTEST_H

#include "../model/CustomerModel.h"

class CustomerTest {
private:
    CustomerModel::Customer testCustomer, returnedCustomer;
    bool testEquality();

public:
    CustomerTest();

    void init();

    bool testAdd();
    bool testUpdate();
//    bool testArchive();

    void exec();

};


#endif //CESI_POO_CUSTOMERTEST_H
