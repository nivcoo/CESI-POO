#include "CustomerTest.h"
#include "../model/ModelManager.h"

int main() {

    ModelManager *modelManager = new ModelManager();

    CustomerTest test = CustomerTest();
    test.exec();

    delete modelManager;

    return EXIT_SUCCESS;
}
